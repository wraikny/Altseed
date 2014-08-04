﻿
#pragma once

#include <ace.common.Base.h>
#include "../../ace.Core.Base.h"
#include "../../ace.Core.Base_Imp.h"

namespace ace
{
	class RenderingCommandExecutor
	{
	private:

	public:
		void Execute(Graphics* graphics, 
			Effekseer::Manager* effectManager,
			EffekseerRenderer::Renderer* effectRenderer,
			std::vector<RenderingCommand*>& commands);
	};
}