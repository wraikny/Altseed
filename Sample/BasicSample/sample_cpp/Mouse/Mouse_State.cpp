﻿#include <Altseed.h>

/**
@brief	マウスの様々な状態を取得するサンプル。
*/
void Mouse_State()
{
	// Altseedを初期化する。
	asd::Engine::Initialize(asd::ToAString("Mouse_State").c_str(), 640, 480, asd::EngineOption());

	// マウスの状態を表示するテキストを生成する。
	auto font = asd::Engine::GetGraphics()->CreateDynamicFont(asd::ToAString("").c_str(), 40, asd::Color(255, 255, 255, 255), 1, asd::Color(0, 0, 0, 255));

	// マウスの中ボタンの入力状態を表示する文字描画オブジェクトを設定して、エンジンに追加する。
	auto buttonStateText = std::make_shared<asd::TextObject2D>();
	buttonStateText->SetPosition(asd::Vector2DF(10, 10));
	buttonStateText->SetFont(font);
	asd::Engine::AddObject2D(buttonStateText);

	// Altseedのウインドウが閉じられていないか確認する。
	while (asd::Engine::DoEvents())
	{
		// マウスの中央クリック状態を取得して表示する。
		auto middlestate = asd::Engine::GetMouse()->GetMiddleButton()->GetButtonState();

		if (middlestate == asd::ButtonState::Free) //前フレームと本フレームで非押下
		{
			buttonStateText->SetText(asd::ToAString("中ボタンを離しています。").c_str());
		}
		else if (middlestate == asd::ButtonState::Hold) //前フレームと本フレームで押下
		{
			buttonStateText->SetText(asd::ToAString("中ボタンを押しています。").c_str());
		}
		else if (middlestate == asd::ButtonState::Release) //前フレームで押下、本フレームで非押下
		{
			buttonStateText->SetText(asd::ToAString("中ボタンを離しました!").c_str());
		}
		else if (middlestate == asd::ButtonState::Push) //前フレームで非押下、本フレームで押下
		{
			buttonStateText->SetText(asd::ToAString("中ボタンを押しました!").c_str());
		}

		// Altseedを更新する。
		asd::Engine::Update();
	}

	//Altseedの終了処理をする。
	asd::Engine::Terminate();

	return;
}
