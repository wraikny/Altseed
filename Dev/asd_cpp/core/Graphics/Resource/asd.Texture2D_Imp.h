﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Math/asd.Vector2DI.h>

#include "asd.Texture2D.h"
#include "../asd.DeviceObject.h"
#include "../../Utils/IAsyncResource.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace asd {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	class Texture2D_Imp
		: public Texture2D
		, public DeviceObject
		, public IAsyncResource
	{
	protected:
		/**
			@brief	内部のバッファに画像ファイルから画像を展開する。
			@param	data	ファイルデータのポインタ
			@param	size	ファイルのデータサイズ
			@param	rev	上限反転で読み込む
		*/
		bool InternalLoad(void* data, int32_t size, bool rev);
		
		/**
			@brief	内部に展開された画像を解放する。
		*/
		void InternalUnload();

		std::vector<uint8_t>	m_internalTextureData;
		int32_t		m_internalTextureWidth;
		int32_t		m_internalTextureHeight;

		Vector2DI	m_size;

		TextureFormat		m_format;
		LoadState			m_loadState;

		Texture2D_Imp(Graphics* graphics);
		virtual ~Texture2D_Imp();

	public:

		Vector2DI GetSize() const { return m_size; }
		TextureFormat GetFormat() const override { return m_format; }
		LoadState GetLoadStateInternal() const override { return m_loadState; }

	// リロード
#if !SWIG
	public:
		virtual void Reload(void* data, int32_t size) = 0;
#endif

	// IReferenceを継承したデバイスオブジェクト向け定義
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}