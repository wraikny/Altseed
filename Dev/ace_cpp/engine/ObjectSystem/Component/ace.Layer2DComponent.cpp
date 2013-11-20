﻿#include "ace.Layer2DComponent.h"
#include "../2D/ace.Layer2D.h"
#include "../ace.Layer.h"

namespace ace
{
	Layer2DComponent::Layer2DComponent()
		: m_layer(nullptr)
	{
	}

	void Layer2DComponent::Update()
	{
		OnUpdate();
	}

	Layer2D* Layer2DComponent::GetOwner() const
	{
		return m_layer;
	}

	void Layer2DComponent::SetOwner(Layer2D* value)
	{
		m_layer = value;
	}
}