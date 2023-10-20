#pragma once

#ifdef TH_PLATFORM_WINDOWS
	#ifdef TH_BUILD_DLL
		#define TOP_HAT_API _declspec(dllexport)
	#else
		#define TOP_HAT_API _declspec(dllimport)
	
	#endif // DEBUG
#else
#error TopHatEngine does not support current os!

#endif // TH_PLATFORM_WINDOWS

#ifdef TH_DEBUG

#define TH_ENABLE_ASSERTS

#endif 


#ifdef TH_ENABLE_ASSERTS
	#define TH_ASSERTS(x,...) {if(!(x)){APPLICATION_ERROR("ASSERTION FAILED! EXIT CODE: {0}", __VA_ARGS__); __debugbreak();}}
	#define TH_FRAMEWORK_ASSERTS(x,...){if((!x)){TH_ENGINE_ERROR("ASSERTION FAILED! EXIT CODE: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define TH_ASSERTS(x,...);
	#define TH_FRAMEWORK_ASSERTS(x,...)
#endif

#define BIT(x)(1 << x)
