﻿#pragma once
#include <memory>
#include "asd.Object2D.h"
#include "asd.DrawnObject2D.h"

namespace asd
{
	/**
	@brief	テクスチャを描画するクラス。
	*/
	class TextureObject2D : public DrawnObject2D
	{
	private:
		std::shared_ptr<CoreTextureObject2D> m_coreObject;
		std::shared_ptr<Texture2D> m_texturePtr;

		CoreObject2D* GetCoreObject() const;
		CoreDrawnObject2D* GetCoreDrawnObject() const override;

	public:
		typedef std::shared_ptr<TextureObject2D> Ptr;

		/**
			@brief	コンストラクタ
		*/
		TextureObject2D();
		/**
			@brief	デストラクタ
		*/
		virtual ~TextureObject2D();


		/**
			@brief	描画するテクスチャを取得する。
		*/
		std::shared_ptr<Texture2D> GetTexture() const;
		/**
			@brief	描画するテクスチャを設定する。
		*/
		void SetTexture(std::shared_ptr<Texture2D> texture);

		/**
		@brief	テクスチャ上の描画範囲を取得する。
		*/
		RectF GetSrc() const;

		/**
		@brief	テクスチャ上の描画範囲を設定する。
		@param value 描画するテクスチャ上の範囲。(フィールドのいずれかが0より小さかったらテクスチャ全体を描画する。)
		*/
		void SetSrc(RectF value);

		/**
			@brief	描画する際の中心座標を取得する。
		*/
		Vector2DF GetCenterPosition() const;
		/**
			@brief	描画する際の中心座標を設定する。
		*/
		void SetCenterPosition(Vector2DF position);

		/**
			@brief	左右反転して描画するかどうかを取得する。
		*/
		bool GetTurnLR() const;
		/**
			@brief	左右反転して描画するかどうかを設定する。
		*/
		void SetTurnLR(bool turnLR);

		/**
			@brief	上下反転して描画するかどうかを取得する。
		*/
		bool GetTurnUL() const;
		/**
			@brief	上下反転して描画するかどうかを設定する。
		*/
		void SetTurnUL(bool turnUL);

		/**
			@brief	このオブジェクトのブレンディング モードを取得する。
		*/
		AlphaBlendMode GetAlphaBlendMode() const;
		/**
			@brief	このオブジェクトのブレンディング モードを設定する。
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