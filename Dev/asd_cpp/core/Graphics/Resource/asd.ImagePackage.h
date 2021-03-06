﻿
#pragma once

#include <asd.common.Base.h>

#include <Math/asd.RectI.h>

#include "asd.Texture2D.h"
#include "../../asd.ReferenceObject.h"

namespace asd
{
	/**
	@brief	複数の画像が格納されているクラス
	*/
	class ImagePackage
		: public IReference
	{
		friend class Accessor;
	private:

	protected:
		ImagePackage() {}
		virtual ~ImagePackage(){}

		virtual Texture2D* GetImage_(int32_t index) = 0;

	public:
		
		/**
			@brief	格納されている画像の枚数を取得する。
			@return	画像の枚数
		*/
		virtual int32_t GetImageCount() = 0;

		/**
			@brief	格納されている画像の名称を取得する。
			@param	index	インデックス
			@return	名称
		*/
		virtual const achar* GetImageName(int32_t index) = 0;

		/**
		@brief	格納されている画像が配置される領域を取得する。
		@param	index	インデックス
		@return	領域
		*/
		virtual RectI GetImageArea(int32_t index) = 0;

		/**
		@brief	格納されている画像の種類を取得する。
		@param	index	インデックス
		@return	画像の種類
		*/
		virtual ImagePackageElementType GetElementType(int32_t index) = 0;

		/**
		@brief	格納されている画像の追加情報の種類を取得する。
		@param	index	インデックス
		@return	追加情報の種類
		*/
		virtual ImagePackageAdditionalElementType GetAdditionalElementType(int32_t index) = 0;

#if !SWIG
		/**
			@brief	画像を取得する。
			@param	index	インデックス
			@return	画像
		*/
		std::shared_ptr<Texture2D> GetImage(int32_t index)
		{
			auto image = GetImage_(index);
			SafeAddRef(image);
			return CreateSharedPtrWithReleaseDLL(image);
		}
#endif
	};
}