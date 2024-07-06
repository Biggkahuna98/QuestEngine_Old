#pragma once

#ifdef TEMPLATELIBTEST_BUILD
	#ifdef _WIN32
		#define TEMPLATELIBTEST_API __declspec(dllexport)
	#elif __GNUC__ >= 4
		#define TEMPLATELIBTEST_API __attribute__((visibility("default")))
	#else
		#define TEMPLATELIBTEST_API
	#endif
#else
	#ifdef _WIN32
		#define TEMPLATELIBTEST_API __declspec(dllimport)
	#else
		#define TEMPLATELIBTEST_API
	#endif
#endif

#include <iostream>

namespace TLib
{
	TEMPLATELIBTEST_API void PrintLibTest();

	TEMPLATELIBTEST_API void VisTest();

	template<typename T>
	void PrintTypeTemplate(T val);
	
}

#include "TemplateLibTest.inl"