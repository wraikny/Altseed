﻿#include "asd.TextureObject2D.h"
using namespace std;

namespace asd
{
	extern ObjectSystemFactory* g_objectSystemFactory;

	TextureObject2D::TextureObject2D()
		: m_coreObject(nullptr)
		, m_texturePtr(nullptr)
	{
		m_coreObject = CreateSharedPtrWithReleaseDLL(g_objectSystemFactory->CreateTextureObject2D());
	}

	TextureObject2D::~TextureObject2D()
	{
	}

	CoreObject2D* TextureObject2D::GetCoreObject() const
	{
		return m_coreObject.get();
	}

	CoreDrawnObject2D* TextureObject2D::GetCoreDrawnObject() const
	{
		return m_coreObject.get();
	}


	shared_ptr<Texture2D> TextureObject2D::GetTexture() const
	{
		return m_texturePtr;
	}

	void TextureObject2D::SetTexture(shared_ptr<Texture2D> texture)
	{
		m_coreObject->SetTexture(texture.get());
		m_texturePtr = texture;
	}

	RectF TextureObject2D::GetSrc() const
	{
		return m_coreObject->GetSrc();
	}

	void TextureObject2D::SetSrc(RectF value)
	{
		m_coreObject->SetSrc(value);
	}

	Vector2DF TextureObject2D::GetCenterPosition() const
	{
		return m_coreObject->GetCenterPosition();
	}

	void TextureObject2D::SetCenterPosition(Vector2DF position)
	{
		m_coreObject->SetCenterPosition(position);
	}

	bool TextureObject2D::GetTurnLR() const
	{
		return m_coreObject->GetTurnLR();
	}

	void TextureObject2D::SetTurnLR(bool turnLR)
	{
		m_coreObject->SetTurnLR(turnLR);
	}

	bool TextureObject2D::GetTurnUL() const
	{
		return m_coreObject->GetTurnUL();
	}

	void TextureObject2D::SetTurnUL(bool turnUL)
	{
		m_coreObject->SetTurnUL(turnUL);
	}

	AlphaBlendMode TextureObject2D::GetAlphaBlendMode() const
	{
		return m_coreObject->GetAlphaBlendMode();
	}

	void TextureObject2D::SetAlphaBlendMode(AlphaBlendMode alphaBlend)
	{
		m_coreObject->SetAlphaBlendMode(alphaBlend);
	}

	void TextureObject2D::SetTextureFilterType(TextureFilterType textureFilterType)
	{
		m_coreObject->SetTextureFilterType(textureFilterType);
	}

	TextureFilterType TextureObject2D::GetTextureFilterType() const
	{
		return m_coreObject->GetTextureFilterType();
	}

	std::shared_ptr<Material2D> TextureObject2D::GetMaterial()
	{
		auto mat = m_coreObject->GetMaterial();
		SafeAddRef(mat);
		return CreateSharedPtrWithReleaseDLL(mat);
	}

	void TextureObject2D::SetMaterial(const std::shared_ptr<Material2D>& material)
	{
		m_coreObject->SetMaterial(material.get());
	}
}