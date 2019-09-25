#pragma once

#include <memory>

#if defined(EGE_PLATFORM_WINDOWS) && defined(EGE_DYNAMIC_LINKING)
	#ifdef EGE_DLL
		#define EGE_API __declspec(dllexport)
	#else
		#define EGE_API __declspec(dllimport)
	#endif // EGE_DLL
#else
	#define EGE_API
#endif // EGE_PLATFORM_WINDOWS

#define BIT(x) (1 << x)

#ifdef EGE_DEBUG
	#define EGE_ENABLE_ASSRETS
#endif // EGE_DEBUG

#ifdef EGE_ENABLE_ASSRETS
	#define EGE_CORE_ASSERT(x, ...) { if(!(x)) { EGE_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define EGE_CLIENT_ASSERT(x, ...) { if(!(x)) { EGE_CLIENT_ERROR(__VA_ARGS__); __debugbreak(); } }
#endif // EGE_ENABLE_ASSRETS

#define EGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Version
#define VERSION_MAJOR		"0"
#define VERSION_MINOR		"0"
#define VERSION_REVISION	"0"
#define VERSION_BUILD		"1"
#define VERSION				(VERSION_MAJOR "." VERSION_MINOR "." VERSION_REVISION "." VERSION_BUILD)

namespace Epoch {

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

}