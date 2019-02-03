﻿
#include "EngineTest.h"

/**
	@brief	3D描画テスト用フレームワーク
	@note
	初期オブジェクトとして、
	カメラ1つ
	が与えられている。
*/
class EngineGraphics3DTest : public EngineTest
{
private:
	std::shared_ptr<asd::Scene> m_scene;
	std::shared_ptr<asd::Layer3D> m_layer3d;
	std::vector<std::shared_ptr<asd::CameraObject3D>> m_cameras;

	bool m_isFreeView;

	float m_cameraDistance = 10.0f;
	float m_cameraRotX = 15.0f;
	float m_cameraRotY = 15.0f;
	asd::Vector3DF m_cameraFocus = asd::Vector3DF(0, 0, 0);

	asd::Vector2DF m_mousePos;

	asd::RenderSettings m_settings;

	const float PI = 3.14159265358979f;

public:
	std::shared_ptr<asd::Scene> GetScene();
	std::shared_ptr<asd::Layer3D> GetLayer3D();

	void AddCamera();
	std::shared_ptr<asd::CameraObject3D> GetCamera(int32_t index);
	void SetCameraParameter(float distance, float rotX, float rotY, float zn, float zf, float fov);

	void SetRenderSettings(asd::RenderSettings settings);

	/**
	@brief
	オーバーライドして、メインループより前のアサーションや初期化を記述できる。
	*/
	virtual void OnStart() override;

	/**
	@brief	オーバーライドして、メインループ内のアサーションなどを記述できる。
	*/
	virtual void OnUpdating() override;

	EngineGraphics3DTest(asd::astring title, bool isOpenGLMode, int exitTime, bool isFreeView);
};