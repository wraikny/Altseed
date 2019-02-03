﻿#pragma once

#include "asd.Object2D.h"
#include "asd.DrawnObject2D.h"

namespace asd
{
	/**
	@brief	文字列の描画を扱うクラス。
	*/
	class TextObject2D : public DrawnObject2D
	{
	private:
		std::shared_ptr<CoreTextObject2D> m_coreObject;
		std::shared_ptr<Font> m_font;

		CoreObject2D* GetCoreObject() const;
		CoreDrawnObject2D* GetCoreDrawnObject() const override;

	public:
		typedef std::shared_ptr<TextObject2D> Ptr;

		TextObject2D();
		virtual ~TextObject2D();

		/**
		@brief	このオブジェクトを描画する際の描画方向を取得する。
		*/
		WritingDirection GetWritingDirection() const;

		/**
		@brief	このオブジェクトを描画する際のフォントを取得する。
		*/
		std::shared_ptr<Font> GetFont() const;

		/**
		@brief 描画するテキストを取得する。
		*/
		const achar* GetText();

		/**
		@brief	このオブジェクトの原点位置を取得する。この位置が、描画する際の描画・拡縮・回転の中心となる。
		*/
		Vector2DF GetCenterPosition() const;

		/**
		@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を取得する。
		*/
		bool GetTurnLR() const;

		/**
		@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を取得する。
		*/
		bool GetTurnUL() const;

		/**
		@brief	このオブジェクトを描画する際のブレンドモードを取得します。
		*/
		AlphaBlendMode GetAlphaBlendMode() const;

		/**
		@brief	このオブジェクトを描画する際の描画方向を設定します。
		*/
		void SetWritingDirection(WritingDirection writingDirection);

		/**
		@brief	このオブジェクトを描画する際のフォントを設定する。
		*/
		void SetFont(std::shared_ptr<Font> font);

		/**
		@brief 描画するテキストを設定する。
		*/
		void SetText(const achar* text);

		/**
		@brief	このオブジェクトの原点位置を設定する。この位置が、描画する際の描画・拡縮・回転の中心となる。
		*/
		void SetCenterPosition(Vector2DF position);

		/**
		@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を設定する。
		*/
		void SetTurnLR(bool turnLR);

		/**
		@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を設定する。
		*/
		void SetTurnUL(bool turnUL);

		/**
		@brief	このオブジェクトを描画する際のブレンドモードを設定する。
		*/
		void SetAlphaBlendMode(AlphaBlendMode alphaBlend);

		/**
		@brief　このオブジェクトを描画する際のテクスチャフィルタの種類を設定する。
		*/
		void SetTextureFilterType(TextureFilterType textureFilterType);

		/**
		@brief　このオブジェクトを描画する際のテクスチャフィルタの種類を取得する。
		*/
		TextureFilterType GetTextureFilterType() const;

		/**
		@brief テキストを描画する際の文字間値を設定する。
		*/
		void SetLetterSpacing(float letterSpacing);

		/**
		@brief テキストを描画する際の文字間値を取得する。
		*/
		float GetLetterSpacing() const;

		/**
		@brief テキストを描画する際の行間値を設定する。
		*/
		void SetLineSpacing(float lineSpacing);

		/**
		@brief テキストを描画する際の行間値を取得する。
		*/
		float GetLineSpacing() const;

		/**
		@brief	文字の色等を変更できるモードか、取得する。
		*/
		bool GetIsRichTextMode() const;

		/**
		@brief	文字の色等を変更できるモードか、設定する。
		*/
		void SetIsRichTextMode(bool value);

		/**
			@brief このオブジェクトを描画する際に使用されるマテリアルを取得する。
		*/
		std::shared_ptr<Material2D> GetMaterial();

		/**
			@brief このオブジェクトを描画する際に使用されるマテリアルを設定する。
			@param	material	マテリアル
		*/
		void SetMaterial(const std::shared_ptr<Material2D>& material);
	};
}