﻿#pragma once
#include <memory>
#include "asd.CoreLayer.h"
#include "../asd.ReferenceObject.h"

namespace asd
{
	class CoreScene : public IReference
	{
	protected:
		CoreScene() {}
		virtual ~CoreScene() {}

	public:
		typedef CoreLayer* LayerPtr;

		virtual void SetSize(Vector2DI size) = 0;

		virtual bool GetHDRMode() const = 0;
		virtual void SetHDRMode(bool value) = 0;

		virtual void AddLayer(LayerPtr layer) = 0;
		virtual void RemoveLayer(LayerPtr layer) = 0;

		virtual void SetRenderTargetForDrawingLayer() = 0;

		/**
			@brief	ポストエフェクトをかけた結果の画像を取得する。
			@return	ポストエフェクト後の画像
		*/
		virtual RenderTexture2D* GetBaseTarget() = 0;
		
		virtual void BeginPostEffect(CorePostEffect* postEffect) = 0;
		virtual void EndPostEffect(CorePostEffect* postEffect) = 0;
		virtual RenderTexture2D* GetSrcTarget() = 0;
		virtual RenderTexture2D* GetDstTarget() = 0;

		virtual void BeginDrawing() = 0;
		virtual void EndDrawing() = 0;
	};
}