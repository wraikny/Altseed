﻿using FontGenerator.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reactive;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FontGenerator.Altseed
{
	class ToolRenderer
	{
		private ConfigViewModel viewModel;
		private ConfigConverter converter;
		private StringConverter strConverter;

		int selectedFont = 0;
		string fontListStr = string.Empty;
		List<Model.FontPair> fontPairs = new List<Model.FontPair>();
		asd.Texture2D preview = null;
		bool isGenerating = false;

		bool isReloadRequired = true;
		string previewPath = string.Empty;

		string statusText = "";

		public ToolRenderer()
		{
			TryLoadFont(
				new[] {
					"C:\\Windows\\Fonts\\meiryo.ttc",
					"/Library/Fonts/ヒラギノ丸ゴ Pro W4.otf",
					"/Library/Fonts/ヒラギノ丸ゴ ProN W4.ttc",
					"/System/Library/Fonts/ヒラギノ丸ゴ ProN W4.ttc",
				}
				);

			var name2path = Model.Helper.GetFontPairs();

			foreach (var np in name2path)
			{
				fontPairs.Add(np);
			}

			fontListStr = string.Join(";", fontPairs.Select(_ => _.Name));

			viewModel = new ConfigViewModel();
			strConverter = new StringConverter();
			converter = new ConfigConverter(strConverter);

			viewModel.FontName.Value = fontPairs[selectedFont].Name;

			viewModel.OnNeedToUpdatePreview
				.Throttle(TimeSpan.FromSeconds(1))
				.Subscribe(x =>
				{
					Generator.GeneratePreviewAsync(converter.ConvertToModel(viewModel))
						.ContinueWith(p => {
							previewPath = p.Result;
							isReloadRequired = true;
						});
				});
		}

		public void Render()
		{
			var tool = asd.Engine.Tool;

			if (asd.Engine.Tool.BeginFullscreen("FontGenerator", 0))
			{
				var fontType = new[] { selectedFont };

				if (tool.BeginCombo("フォントの種類", fontPairs[selectedFont].Name))
				{
					for (int i = 0; i < fontPairs.Count; i++)
					{
						if (tool.Selectable(fontPairs[i].Name, i == selectedFont))
						{
							selectedFont = i;
							viewModel.FontName.Value = fontPairs[i].Name;
							viewModel.FontIndex.Value = i;
							tool.SetItemDefaultFocus();
							break;
						}
					}
					tool.EndCombo();
				}

				tool.InputText("文字一覧ファイル", viewModel.TextPath);
				if (tool.Button("ファイルを開く..."))
				{
					var defaultPath = File.Exists(viewModel.TextPath.String)
						? Path.GetDirectoryName(viewModel.TextPath.String)
						: Directory.GetCurrentDirectory();
					viewModel.TextPath.String = tool.OpenDialog("txt", defaultPath);
				}

				tool.InputText("出力先ディレクトリ", viewModel.ExportPath);
				if (tool.Button("ディレクトリを開く..."))
				{
					var defaultPath = Directory.Exists(viewModel.ExportPath.String)
						? viewModel.ExportPath.String
						: Directory.GetCurrentDirectory();
					viewModel.ExportPath.String = tool.PickFolder(defaultPath);
				}

				tool.InputText("シート名", viewModel.SheetName);
				tool.InputInt("フォントサイズ", viewModel.FontSize);
				tool.InputInt("テクスチャサイズ", viewModel.TextureSize);
				tool.InputInt("輪郭線の太さ", viewModel.OutlineSize);
				tool.InputColor("フォント色", viewModel.FontColor);
				tool.InputColor("輪郭線の色", viewModel.OutlineColor);

				if (preview != null)
				{
					tool.Image(preview, preview.Size.To2DF());
				}

				if (tool.Button("設定ロード..."))
				{
					var path = tool.OpenDialog("afcfg", Directory.GetCurrentDirectory());

					if(!string.IsNullOrWhiteSpace(path))
					{
						converter.LoadFromModel(ConfigurationFile.Load(path), viewModel);
						selectedFont = fontPairs.IndexOf(fontPairs.Find(x => x.Name == viewModel.FontName.Value));
					}
				}
				if (tool.Button("設定セーブ..."))
				{
					var path = tool.SaveDialog("afcfg", Directory.GetCurrentDirectory());

					if (!string.IsNullOrWhiteSpace(path))
					{
						if(path.EndsWith(".afcfg"))
						{
							path += ".afcfg";
						}

						ConfigurationFile.Save(converter.ConvertToModel(viewModel), path);
					}
				}
				if (!isGenerating && tool.Button("aff生成"))
				{
					isGenerating = true;
					statusText = "生成中...";
					var task = Generator.GenerateAsync(converter.ConvertToModel(viewModel));
					task.ContinueWith(x =>
					{
						isGenerating = false;
						statusText = "生成完了";
					}, TaskContinuationOptions.OnlyOnRanToCompletion);
					task.ContinueWith(x =>
					{
						isGenerating = false;
						if (x.Exception is AggregateException)
						{
							statusText = "生成失敗：" + x.Exception.InnerException.Message;
						}
						else
						{
							statusText = "生成失敗：" + x.Exception.Message;
						}
						Console.WriteLine(x.Exception);
					}, TaskContinuationOptions.OnlyOnFaulted);
				}

				tool.Text(statusText);

				tool.End();

				if(isReloadRequired)
				{
					var src = asd.Engine.Graphics.CreateEditableTexture2D(previewPath);
					if (src != null)
					{
						var canvas = asd.Engine.Graphics.CreateEmptyTexture2D(320, 100, asd.TextureFormat.R8G8B8A8_UNORM_SRGB);
						Render(canvas, src);
						preview = canvas;
					}
					else
					{
						preview = null;
					}
					asd.Engine.Reload();
					isReloadRequired = false;
				}
			}
		}

		private unsafe void Render(asd.Texture2D destination, asd.Texture2D source)
		{
			var dstWidth = destination.Size.X;
			var dstHeight = destination.Size.Y;
			var srcWidth = source.Size.X;
			var srcHeight = source.Size.Y;

			var dstLock = new asd.TextureLockInfomation();
			var srcLock = new asd.TextureLockInfomation();
			destination.Lock(dstLock);
			source.Lock(srcLock);

			asd.Color* p = (asd.Color*)srcLock.Pixels.ToPointer();

			for (int y = 0; y < dstHeight && y < srcHeight; y++)
			{
				for (int x = 0; x < dstWidth && x < srcWidth; x++)
				{
					var src = *(p + x + y * srcWidth);
					var dst = (asd.Color*)dstLock.Pixels + x + y * dstWidth;

					*dst = src;
				}
			}

			source.Unlock();
			destination.Unlock();
		}

		static void TryLoadFont(string[] fonts)
		{
			foreach (var font in fonts)
			{
				if (!System.IO.File.Exists(font)) continue;
				asd.Engine.Tool.AddFontFromFileTTF(font, 16);
				break;
			}
		}

	}
}
