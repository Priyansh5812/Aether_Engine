#pragma once

#ifdef AE_WINDOWS
	#if AE_BUILD_DLL
		#define AE_API __declspec(dllexport)
	#else
		#define AE_API __declspec(dllimport)
	#endif
#else
	#error AETHER ONLY SUPPORTS WINDOWS !!!
#endif
