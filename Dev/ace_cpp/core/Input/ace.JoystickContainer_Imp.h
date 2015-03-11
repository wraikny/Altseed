﻿#pragma once

#include "ace.JoystickContainer.h"

namespace ace{
	class JoystickContainer_Imp:public JoystickContainer
	{
		static const int MAX_CONTAINER_SIZE = 16;

		Joystick_Imp *m_joystickContainer[MAX_CONTAINER_SIZE];
		JoystickContainer_Imp();
	public:
		virtual ~JoystickContainer_Imp();
		void RefreshJoysticks();
		static JoystickContainer_Imp* Create();
		bool GetIsPresentAt(int at) override;
		Joystick* GetJoystickAt(int at) override;
	};
};
