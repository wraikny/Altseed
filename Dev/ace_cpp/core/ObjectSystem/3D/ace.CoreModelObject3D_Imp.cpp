﻿
#include "ace.CoreModelObject3D_Imp.h"
#include "ace.CoreLayer3D_Imp.h"

#include "../../Graphics/3D/Object/ace.RenderedModelObject3D.h"

namespace ace
{
	CoreModelObject3D_Imp::CoreModelObject3D_Imp(Graphics* graphics)
		: m_object(nullptr)
	{
		m_object = new RenderedModelObject3D(graphics);
		m_commonObject = m_object;
	}

	CoreModelObject3D_Imp::~CoreModelObject3D_Imp()
	{
		SafeRelease(m_object);
	}

	void CoreModelObject3D_Imp::SetModel(Model* model)
	{
		m_object->SetModel(model);
	}

	void CoreModelObject3D_Imp::AddMesh(Mesh* mesh)
	{
		m_object->AddMesh(mesh);
	}

	void CoreModelObject3D_Imp::SetDeformer(Deformer* deformer)
	{
		m_object->SetDeformer(deformer);
	}

	void CoreModelObject3D_Imp::PlayAnimation(const achar* name)
	{
		m_object->PlayAnimation(name);
	}
}
