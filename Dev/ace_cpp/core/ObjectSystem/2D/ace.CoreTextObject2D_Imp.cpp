﻿#include "../common/ace.common.Base.h"
#include "ace.CoreTextObject2D_Imp.h"
#include "../../Graphics/Resource/ace.Font_Imp.h"
#include "../../Graphics/Resource/ace.Texture2D_Imp.h"

namespace ace
{
	CoreTextObject2D_Imp::CoreTextObject2D_Imp(Graphics_Imp* graphics)
		: CoreObject2D_Imp(graphics)
		, m_font(nullptr)
		, m_centerPosition(Vector2DF())
		, m_color(Color())
		, m_turnLR(false)
		, m_turnUL(false)
		, m_text(ace::ToAString(""))
		, m_alphablend(eAlphaBlend::ALPHA_BLEND_BLEND)
		, m_drawingPtiority(0)
		, m_writingDirection(WritingDirection::Horizontal)
	{

	}

	CoreTextObject2D_Imp::~CoreTextObject2D_Imp()
	{
		SafeRelease(m_font);
	}


#pragma region Parameter
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	Font* CoreTextObject2D_Imp::GetFont() const
	{
		return m_font;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetFont(Font* font)
	{
		SafeSubstitute(m_font, font);
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const WritingDirection CoreTextObject2D_Imp::GetWritingDirection() const
	{
		return m_writingDirection;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetWritingDirection(WritingDirection writingDirection)
	{
		m_writingDirection = writingDirection;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const astring CoreTextObject2D_Imp::GetText() const
	{
		return m_text;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetText(const achar* text)
	{
		m_text = ToAString(text);
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const Vector2DF CoreTextObject2D_Imp::GetCenterPosition() const
	{
		return m_centerPosition;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetCenterPosition(Vector2DF position)
	{
		m_centerPosition = position;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const Color CoreTextObject2D_Imp::GetColor() const
	{
		return m_color;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetColor(Color color)
	{
		m_color = color;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const bool CoreTextObject2D_Imp::GetTurnLR() const
	{
		return m_turnLR;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetTurnLR(bool turnLR)
	{
		m_turnLR = turnLR;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const bool CoreTextObject2D_Imp::GetTurnUL() const
	{
		return m_turnUL;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetTurnUL(bool turnUL)
	{
		m_turnUL = turnUL;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const int CoreTextObject2D_Imp::GetDrawingPriority() const
	{
		return m_drawingPtiority;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetDrawingPriority(int priority)
	{
		m_drawingPtiority = priority;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	const eAlphaBlend CoreTextObject2D_Imp::GetAlphaBlendMode() const
	{
		return m_alphablend;
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::SetAlphaBlendMode(eAlphaBlend alphablend)
	{
		m_alphablend = alphablend;
	}
#pragma endregion

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void CoreTextObject2D_Imp::Draw(Renderer2D* renderer, Matrix33 cameraMatrix)
	{
		if (!m_objectInfo.GetIsDrawn())
		{
			return;
		}

		Vector2DF drawPosition = Vector2DF(0, 0);

		auto parentMatrix = m_transform.GetParentsMatrix();
		auto matrix = m_transform.GetMatrixToTransform();

		std::array<Color, 4> color;
		color.at(0) = m_color;
		color.at(1) = m_color;
		color.at(2) = m_color;
		color.at(3) = m_color;

		Font_Imp *font_Imp = (Font_Imp*)m_font;

		for (int textIndex = 0; textIndex < m_text.length(); ++textIndex)
		{
			if (!font_Imp->HasGlyphData(m_text[textIndex]))
			{
				continue;
			}

			GlyphData glyphData = font_Imp->GetGlyphData(m_text[textIndex]);

			auto glyphSrc = glyphData.GetSrc();

			std::array<Vector2DF, 4> position;

			{
				position.at(0) = Vector2DF(0, 0);
				position.at(1) = Vector2DF(glyphSrc.Width, 0);
				position.at(2) = Vector2DF(glyphSrc.Width, glyphSrc.Height);
				position.at(3) = Vector2DF(0, glyphSrc.Height);

				for (auto& pos : position)
				{
					pos += drawPosition;
					pos -= m_centerPosition;
					auto v3 = Vector3DF(pos.X, pos.Y, 1);
					auto result = cameraMatrix * parentMatrix * matrix * v3;
					pos = Vector2DF(result.X, result.Y);
				}

			}

			auto texture = font_Imp->GetTexture(glyphData.GetSheetNum());

			std::array<Vector2DF, 4> uvs;
			{
				auto textureSize = Vector2DF(texture->GetSize().X,texture->GetSize().Y);

				uvs.at(0) = Vector2DF(glyphSrc.X, glyphSrc.Y);
				uvs.at(1) = Vector2DF(glyphSrc.X + glyphSrc.Width, glyphSrc.Y);
				uvs.at(2) = Vector2DF(glyphSrc.X + glyphSrc.Width, glyphSrc.Y + glyphSrc.Height);
				uvs.at(3) = Vector2DF(glyphSrc.X, glyphSrc.Y + glyphSrc.Height);

				for (auto& uv : uvs)
				{
					uv /= textureSize;
				}

				if (m_turnLR)
				{
					std::swap(uvs.at(0), uvs.at(1));
					std::swap(uvs.at(2), uvs.at(3));
				}

				if (m_turnUL)
				{
					std::swap(uvs.at(0), uvs.at(3));
					std::swap(uvs.at(1), uvs.at(2));
				}
			}

			renderer->AddSprite(position.data(), &color[0], uvs.data(), texture.get(), m_alphablend, m_drawingPtiority);

			if (m_writingDirection == WritingDirection::Horizontal)
			{
				drawPosition += ace::Vector2DF(glyphSrc.Width, 0);
			}
			else
			{
				drawPosition += ace::Vector2DF(0, glyphSrc.Height);
			}
		}

	}
}