#pragma once

#include <memory>

// Platform Detection

#ifdef _WIN32
	#ifdef _WIN64
		#define EGE_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error IOS Simulator is not supported
	#elif TARGET_OS_IPHONE == 1
		#define EGE_PLATFORM_IOS
		#error "IOS is not supported"
	#elif TARGET_OS_MAC == 1
		#define EGE_PLATFORM_MAC
		#error "Mac OS is not supported"
	#else
		#error "Unknown Apple OS"
	#endif
#elif defined(__ANDROID__)
		#define EGE_PLATFORM_ANDROID
		#error "Android is not supported"
#elif defined(__linux__)
	#define EGE_PLATFORM_LINUX
	#error "Linux is not supported"
#else
		#error "Unknown Platform"
#endif

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
	template<typename T, typename... Args>
	constexpr Ref<T> create_ref(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> create_scope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}