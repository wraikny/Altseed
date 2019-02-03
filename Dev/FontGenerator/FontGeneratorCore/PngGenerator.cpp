﻿
#include <iostream>
#include <sstream>
#include <fstream>
#include "PngGenerator.h"
#include "Rendering/ImageBuffer.h"
#include "Utility.h"
#include <AltseedRHI.h>

#ifdef _v120
#ifdef _WIN64

#if _DEBUG
#pragma comment(lib,"x64/Debug/VS2013/libpng16.lib")
#pragma comment(lib,"x64/Debug/VS2013/zlib.lib")
#else
#pragma comment(lib,"x64/Release/VS2013/libpng16.lib")
#pragma comment(lib,"x64/Release/VS2013/zlib.lib")
#endif

#else

#if _DEBUG
#pragma comment(lib,"x86/Debug/VS2013/libpng16.lib")
#pragma comment(lib,"x86/Debug/VS2013/zlib.lib")
#else
#pragma comment(lib,"x86/Release/VS2013/libpng16.lib")
#pragma comment(lib,"x86/Release/VS2013/zlib.lib")
#endif

#endif
#endif

#ifdef _v140
#ifdef _WIN64

#if _DEBUG
#pragma comment(lib,"x64/Debug/VS2015/libpng16.lib")
#pragma comment(lib,"x64/Debug/VS2015/zlib.lib")
#else
#pragma comment(lib,"x64/Release/VS2015/libpng16.lib")
#pragma comment(lib,"x64/Release/VS2015/zlib.lib")
#endif

#else

#if _DEBUG
#pragma comment(lib,"x86/Debug/VS2015/libpng16.lib")
#pragma comment(lib,"x86/Debug/VS2015/zlib.lib")
#else
#pragma comment(lib,"x86/Release/VS2015/libpng16.lib")
#pragma comment(lib,"x86/Release/VS2015/zlib.lib")
#endif

#endif
#endif

#if _DEBUG
#pragma comment(lib,"x86/Debug/freetype.lib")
#pragma comment(lib,"x86/Debug/asd_common.lib")
#pragma comment(lib,"x86/Debug/asd_tool.lib")
#pragma comment(lib, "GdiPlus.lib")
#pragma comment(lib, "x86/Debug/AltseedRHI.lib")
#else
#pragma comment(lib,"x86/Release/freetype.lib")
#pragma comment(lib,"x86/Release/asd_common.lib")
#pragma comment(lib,"x86/Release/asd_tool.lib")
#pragma comment(lib, "GdiPlus.lib")
#pragma comment(lib, "x86/Release/AltseedRHI.lib")
#endif


using namespace std;
using namespace asd;

namespace FontGenerator
{
	PngGenerator::PngGenerator()
		: m_sheetName(asd::ToAString("font.png"))
		, m_fonts(vector<FontData>())
		, m_setting(SettingForRendering())
	{
	}

	ResultOfGeneratingPng PngGenerator::Generate(astring fontPath, vector<achar>& charactors)
	{
		Font font(fontPath);
		font.SetFontSize(m_setting.GetFontSize());

		ImageBuffer buffer(font, m_sheetSize);
		vector<GlyphData> fontData;

		for (auto& glyph : font.GetGlyphs(charactors))
		{
			auto result = buffer.Draw(glyph, m_setting.GetFontColor(), m_setting.GetBorder());
			fontData.push_back(result);
		}

		auto buffers = buffer.GetBuffers();

		// Be careful. (two image helper exists (asd_core and font generator))
		ar::ImageHelper::Initizlize();

		for (size_t i = 0; i < buffers.size(); i++)
		{
			std::ostringstream os;
			os << "_" << i << ".png";
			auto pngPath = GetSheetName() + ToAString(os.str().c_str());
			ar::ImageHelper::SavePNG(pngPath.c_str(), m_sheetSize, m_sheetSize, buffers[i]->data());
		}

		ar::ImageHelper::Terminate();

		ResultOfGeneratingPng result;
		result.sheetCount = buffers.size();
		result.fonts = fontData;
		return result;
	}

	void PngGenerator::GeneratePreview(astring fontPath, astring path)
	{
		const int IMAGE_SIZE = 256;

#ifdef _WIN32
		vector<achar> previewChars{ L'e', L'E', L'1', L'あ', L'永' };
#else
		vector<achar> previewChars{ u'e', u'E', u'1', u'あ', u'永' };
#endif

		Font font(fontPath);
		font.SetFontSize(m_setting.GetFontSize());

		ImageBuffer buffer(font, IMAGE_SIZE);

		for (auto& glyph : font.GetGlyphs(previewChars))
		{
			buffer.Draw(glyph, m_setting.GetFontColor(), m_setting.GetBorder());
		}

		auto buffers = buffer.GetBuffers();

		// Be careful. (two image helper exists (asd_core and font generator))
		ar::ImageHelper::Initizlize();
		ar::ImageHelper::SavePNG((path).c_str(), IMAGE_SIZE, IMAGE_SIZE, buffers[0]->data());
		ar::ImageHelper::Terminate();
	}

#pragma region GetSet
	astring PngGenerator::GetSheetName() const
	{
		return m_sheetName;
	}

	void PngGenerator::SetSheetName(astring value)
	{
		m_sheetName = value;
	}

	int PngGenerator::GetSheetSize() const
	{
		return m_sheetSize;
	}

	void PngGenerator::SetSheetSize(int value)
	{
		m_sheetSize = value;
	}

	SettingForRendering PngGenerator::GetSetting() const
	{
		return m_setting;
	}

	void PngGenerator::SetSetting(SettingForRendering value)
	{
		m_setting = value;
	}

#pragma endregion
}