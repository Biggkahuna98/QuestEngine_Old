#pragma once // NOLINT

#include <iostream>

#ifdef QE_PLATFORM_WINDOWS
	#define QE_DEBUG_BREAK __debugbreak()
#else
	#define QE_DEBUG_BREAK
#endif

#ifdef QE_DEBUG
	#define QE_ENABLE_ASSERTS
#endif

#define QE_ENABLE_VERIFY

#ifdef QE_ENABLE_ASSERTS
	#define QE_CORE_ASSERT_MSG_INTERNAL(...) std::cout << "CORE_ASSERT_INTERNAL\n"
	#define QE_ASSERT_MSG_INTERNAL(...) std::cout << "ASSERT_INTERNAL\n"

	#define QE_CORE_ASSERT(condition, ...) { if (!(condition)) { QE_CORE_ASSERT_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
	#define QE_ASSERT(condition, ...) { if (!(condition)) { QE_ASSERT_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
#else
	#define QE_CORE_ASSERT(condition, ...)
	#define QE_ASSERT(condition, ...)
#endif
