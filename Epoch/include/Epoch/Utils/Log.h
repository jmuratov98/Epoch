#pragma once

#include "Epoch/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Epoch {

	class EGE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return cm_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return cm_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> cm_CoreLogger;
		static std::shared_ptr<spdlog::logger> cm_ClientLogger;
	};

}

// Core Logger
#define EGE_CORE_TRACE(...)			::Epoch::Log::getCoreLogger()->trace(__VA_ARGS__)
#define EGE_CORE_INFO(...)			::Epoch::Log::getCoreLogger()->info(__VA_ARGS__)
#define EGE_CORE_WARN(...)			::Epoch::Log::getCoreLogger()->warn(__VA_ARGS__)
#define EGE_CORE_ERROR(...)			::Epoch::Log::getCoreLogger()->error(__VA_ARGS__)
#define EGE_CORE_CRIT(...)			::Epoch::Log::getCoreLogger()->critical(__VA_ARGS__)
#ifdef EGE_DEBUG
	#define EGE_CORE_DEBUG(...)		::Epoch::Log::getCoreLogger()->debug(__VA_ARGS__)
#endif // EGE_DEBUG

// Client Logger
#define EGE_CLIENT_TRACE(...)		::Epoch::Log::getClientLogger()->trace(__VA_ARGS__)
#define EGE_CLIENT_INFO(...)		::Epoch::Log::getClientLogger()->info(__VA_ARGS__)
#define EGE_CLIENT_WARN(...)		::Epoch::Log::getClientLogger()->warn(__VA_ARGS__)
#define EGE_CLIENT_ERROR(...)		::Epoch::Log::getClientLogger()->error(__VA_ARGS__)
#define EGE_CLIENT_CRIT(...)		::Epoch::Log::getClientLogger()->critical(__VA_ARGS__)
#ifdef EGE_DEBUG
	#define EGE_CLIENT_DEBUG(...)		::Epoch::Log::getClientLogger()->debug(__VA_ARGS__)
#endif // EGE_DEBUG