#include "pch.h"
#include "Epoch/Core/Engine.h"

#include "Epoch/Core/Core.h"

namespace Epoch {

	void Engine::init()
	{
		Log::init();
		EGE_CORE_TRACE("Welcome to Epoch Graphics Engine {0}", VERSION);
	}

	void Engine::shutdown()
	{
	}

}