#include "pch.h"
#include "Epoch/Engine.h"

#include "Epoch/Core.h"

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