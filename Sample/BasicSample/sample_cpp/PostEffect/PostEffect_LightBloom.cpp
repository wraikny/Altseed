﻿#include <Base.h>

/**
@brief	レイヤーにライトブルームのポストエフェクトを適用する。
*/
void PostEffect_LightBloom()
{
	// Altseedを初期化する
	asd::Engine::Initialize(asd::ToAString("PostEffect_LightBloom").c_str(), 640, 480, asd::EngineOption());

	auto texture = asd::Engine::GetGraphics()->CreateTexture2D(asd::ToAString("Data/Texture/Object.png").c_str());

	// シーンのコンストラクタを呼び出す。
	auto scene = std::make_shared<asd::Scene>();

	// レイヤーのコンストラクタを呼び出す。
	auto layer = std::make_shared<asd::Layer2D>();

	// オブジェクトのコンストラクタを呼び出す。
	auto obj = std::make_shared<asd::TextureObject2D>();

	// オブジェクトの位置とテクスチャを設定。
	obj->SetPosition(asd::Vector2DF(100, 100));
	obj->SetTexture(texture);

	// シーンを変更し、そのシーンにレイヤーを追加し、そのレイヤーにオブジェクトを追加する。
	asd::Engine::ChangeScene(scene);
	scene->AddLayer(layer);
	layer->AddObject(obj);

	// ライトブルームのコンストラクタを呼び出す。
	auto posteffect = std::make_shared<asd::PostEffectLightBloom>();

	// ライトブルームのぼかしの強さを設定する。
	posteffect->SetIntensity(10.0f);

	// ライトブルームの露光の強さを設定する。
	posteffect->SetExposure(1.0f);

	// ライトブルームで光らせる明るさのしきい値を設定する。
	posteffect->SetThreshold(0.3f);

	// レイヤーにライトブルームのポストエフェクトを適用。
	layer->AddPostEffect(posteffect);

	// HDRモードをONにする（ライトブルームの効果が見えるようにするため）
	scene->SetHDRMode(true);

	while (asd::Engine::DoEvents())
	{
		asd::Engine::Update();
	}

	asd::Engine::Terminate();
}