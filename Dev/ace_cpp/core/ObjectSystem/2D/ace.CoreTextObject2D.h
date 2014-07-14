﻿
#pragma once
#include "../common/Math/ace.Vector2DF.h"
#include "../common/Graphics/ace.Color.h"
#include "../../Graphics/Resource/ace.Font.h"
#include "ace.CoreObject2D.h"

namespace ace
{

	class CoreTextObject2D
		: public CoreObject2D
	{
	public:
		CoreTextObject2D() {}
		virtual ~CoreTextObject2D() {}

		/**
		@brief	このオブジェクトを描画する際の描画方向を取得する。
		*/
		virtual const WritingDirection GetWritingDirection() const = 0;

		/**
		@brief	このオブジェクトを描画する際のフォントハンドルを取得する。
		*/
		virtual const Font* GetFont() const = 0;

		/**
		@brief 描画するテキストを取得する。
		*/
		virtual const astring GetText() const = 0;

		/**
		@brief	このオブジェクトの原点位置を取得する。この位置が、描画する際の描画・拡縮・回転の中心となる。
		*/
		virtual const Vector2DF GetCenterPosition() const = 0;

		/**
		@brief	このオブジェクトを描画する際に文字画像に合成する色を取得する。
		*/
		virtual const Color GetColor() const = 0;

		/**
		@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を取得する。
		*/
		virtual const bool GetTurnLR() const = 0;

		/**
		@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を取得する。
		*/
		virtual const bool GetTurnUL() const = 0;

		/**
		@brief	このオブジェクトの描画優先度を取得します。
		*/
		virtual const int GetDrawingPriority() const = 0;

		/**
		@brief	このオブジェクトを描画する際のブレンドモードを取得します。
		*/
		virtual const AlphaBlend GetAlphaBlendMode() const = 0;

		/**
		@brief	このオブジェクトを描画する際の描画方向を設定します。
		*/
		virtual void SetWritingDirection(WritingDirection writingDirection) = 0;

		/**
		@brief	このオブジェクトを描画する際のフォントハンドルを設定する。
		*/
		virtual void SetFont(Font* font) = 0;

		/**
		@brief 描画するテキストを設定する。
		*/
		virtual void SetText(const achar* text) = 0;

		/**
		@brief	このオブジェクトの原点位置を設定する。この位置が、描画する際の描画・拡縮・回転の中心となる。
		*/
		virtual void SetCenterPosition(Vector2DF position) = 0;

		/**
		@brief	このオブジェクトを描画する際にテクスチャに合成する色を設定する。
		*/
		virtual void SetColor(Color color) = 0;

		/**
		@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を設定する。
		*/
		virtual void SetTurnLR(bool turnLR) = 0;

		/**
		@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を設定する。
		*/
		virtual void SetTurnUL(bool turnUL) = 0;

		/**
		@brief	このオブジェクトの描画優先度を設定する。
		*/
		virtual void SetDrawingPriority(int priority) = 0;

		/**
		@brief	このオブジェクトを描画する際のブレンドモードを設定する。
		*/
		virtual void SetAlphaBlendMode(AlphaBlend alphaBlend) = 0;
	};
}