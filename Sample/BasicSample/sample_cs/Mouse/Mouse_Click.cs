﻿/// <summary>
/// マウスによる入力を取得を取得するサンプル。
/// </summary>
public class Mouse_Click :ISample
{
    public string Description
    {
        get { return "マウスの左クリックを検知するサンプルです。"; }
    }
	public string Title
	{
		get { return "マウスのクリック検知"; }
	}
	public string ClassName
	{
		get { return "Mouse_Click"; }
	}

    public void Run()
    {
        //Altseedを初期化する。
        asd.Engine.Initialize("Mouse_Click", 640, 480, new asd.EngineOption());

        // マウスの状態を表示するテキストを生成する。
        var font = asd.Engine.Graphics.CreateDynamicFont("", 40, new asd.Color(255, 255, 255, 255), 1, new asd.Color(0, 0, 0, 255));

        // マウスの左ボタンをクリックしたか否かを表示する文字描画オブジェクトを設定して、エンジンに追加する。
        var stateText = new asd.TextObject2D();
        stateText.Position = new asd.Vector2DF(10, 10);
        stateText.Font = font;
        asd.Engine.AddObject2D(stateText);

        // Altseedのウインドウが閉じられていないか確認する。
        while (asd.Engine.DoEvents())
        {
            // 左ボタンが押されているかを表示する。
            if (asd.Engine.Mouse.LeftButton.ButtonState == asd.ButtonState.Hold)
            {
                stateText.Text = "左ボタンが押されています。";
            }
            else
            {
                stateText.Text = "左ボタンが押されていません。";
            }

            // Altseedを更新する。
            asd.Engine.Update();

            Recorder.CaptureScreen("Mouse_Click", 30, 30, 0.5f, 0.5f);
			Recorder.TakeScreenShot("Mouse_Click", 30);
        }

        //Altseedの終了処理をする。
        asd.Engine.Terminate();
    }
}
