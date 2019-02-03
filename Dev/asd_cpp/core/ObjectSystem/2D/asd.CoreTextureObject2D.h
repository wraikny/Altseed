﻿#pragma once
#include "../common/Math/asd.Vector2DF.h"
#include "../common/Graphics/asd.Color.h"
#include "../../Graphics/Resource/asd.Texture2D.h"
#include "asd.CoreObject2D.h"
#include "asd.CoreDrawnObject2D.h"

namespace asd
{
	class CoreTextureObject2D 
		: public CoreDrawnObject2D
	{
	public:
		virtual ~CoreTextureObject2D()
		{
		}

		virtual Material2D* GetMaterial() const = 0;

		virtual void SetMaterial(Material2D* material) = 0;

		/**
			@brief	このオブジェクトを描画する際に使用されるテクスチャを取得します。
		*/
		virtual Texture2D* GetTexture() const = 0;

		virtual RectF GetSrc() const = 0;

		/**
			@brief	このオブジェクトを描画する際のテクスチャの向きを取得します。
		*/
		virtual float GetAngle() const = 0;

		/**
			@brief	このオブジェクトを描画する際のテクスチャの拡大率を取得します。
		*/
		virtual Vector2DF GetScale() const = 0;

		/**
			@brief	このオブジェクトの原点位置を取得します。この位置が、描画する際の描画・拡縮・回転の中心となります。
		*/
		virtual Vector2DF GetCenterPosition() const = 0;

		/**
			@brief	このオブジェクトを描画する際にテクスチャに合成する色を取得します。
		*/
		virtual Color GetColor() const = 0;

		/**
			@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を取得します。
		*/
		virtual bool GetTurnLR() const = 0;

		/**
			@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を取得します。
		*/
		virtual bool GetTurnUL() const = 0;

		/**
			@brief	このオブジェクトの描画優先度を取得します。
		*/
		virtual int GetDrawingPriority() const = 0;

		/**
			@brief	このオブジェクトを描画する際のブレンドモードを取得します。
		*/
		virtual AlphaBlendMode GetAlphaBlendMode() const = 0;


		/**
			@brief	このオブジェクトを描画する際に使用されるテクスチャを設定します。
		*/
		virtual void SetTexture(Texture2D* texture) = 0;

		virtual void SetSrc(RectF value) = 0;

		/**
			@brief	このオブジェクトを描画する際のテクスチャの向きを設定します。
		*/
		virtual void SetAngle(float degree) = 0;

		/**
			@brief	このオブジェクトを描画する際のテクスチャの拡大率を設定します。
		*/
		virtual void SetScale(Vector2DF scale) = 0;

		/**
			@brief	このオブジェクトの原点位置を設定します。この位置が、描画する際の描画・拡縮・回転の中心となります。
		*/
		virtual void SetCenterPosition(Vector2DF position) = 0;

		/**
			@brief	このオブジェクトを描画する際にテクスチャに合成する色を設定します。
		*/
		virtual void SetColor(Color color) = 0;

		/**
			@brief	このオブジェクトを描画する際に左右反転するかどうかの真偽値を設定します。
		*/
		virtual void SetTurnLR(bool turnLR) = 0;

		/**
			@brief	このオブジェクトを描画する際に上下反転するかどうかの真偽値を設定します。
		*/
		virtual void SetTurnUL(bool turnUL) = 0;

		/**
			@brief	このオブジェクトの描画優先度を設定します。
		*/
		virtual void SetDrawingPriority(int priority) = 0;

		/**
			@brief	このオブジェクトを描画する際のブレンドモードを設定します。
		*/
		virtual void SetAlphaBlendMode(AlphaBlendMode alphaBlend) = 0;

		/**
		@brief　このオブジェクトを描画する際のテクスチャフィルタの種類を設定する。
		*/
		virtual void SetTextureFilterType(TextureFilterType textureFilterType) = 0;

		/**
		@brief　このオブジェクトを描画する際のテクスチャフィルタの種類を取得する。
		*/
		virtual TextureFilterType GetTextureFilterType() const = 0;
	};
}
