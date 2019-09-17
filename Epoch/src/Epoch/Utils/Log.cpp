#include "pch.h"
#include "Epoch/Utils/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Epoch {

	std::shared_ptr<spdlog::logger> Log::cm_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::cm_ClientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		Log::cm_CoreLogger = spdlog::stdout_color_mt("EPOCH");
		Log::cm_CoreLogger->set_level(spdlog::level::trace);


		Log::cm_ClientLogger = spdlog::stdout_color_mt("APP");
		Log::cm_ClientLogger->set_level(spdlog::level::trace);
	}

}