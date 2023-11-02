#pragma once

#include <memory>

#ifdef TH_PLATFORM_WINDOWS
	 
	
	 
#elif TH_PLATFORM_MULTI

#else

#error TopHatEngine does not support current os!

#endif // TH_PLATFORM_WINDOWS

#ifdef TH_DEBUG

#define TH_ENABLE_ASSERTS

#endif 


#ifdef TH_ENABLE_ASSERTS
	#define TH_ASSERTS(x,...) {if(!(x)){APPLICATION_ERROR("ASSERTION FAILED! EXIT CODE: {0}", __VA_ARGS__); __debugbreak();}}
	#define TH_FRAMEWORK_ASSERTS(x,...){if(!(x)){TH_ENGINE_ERROR("ASSERTION FAILED! EXIT CODE: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define TH_ASSERTS(x,...);
	#define TH_FRAMEWORK_ASSERTS(x,...)
#endif

#define BIT(x)(1 << x)

namespace TopHat
{
	template<typename  T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}
