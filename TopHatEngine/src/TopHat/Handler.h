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

#define BIT(x)(1 << x)
