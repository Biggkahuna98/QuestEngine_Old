#ifndef QE_CORE_ASSERT_H_INCLUDED
#define QE_CORE_ASSERT_H_INCLUDED

#include "LogManager.h"

#ifdef QE_PLATFORM_WINDOWS
	#define QE_DEBUG_BREAK __debugbreak()
#else
	#define QE_DEBUG_BREAK
#endif

#ifdef QE_DEBUG_MODE
	#define QE_ENABLE_ASSERTS
#endif

// Verifies are asserts that are enforced even for release mode(s)
#define QE_ENABLE_VERIFY

#ifdef QE_ENABLE_ASSERTS
	#define QE_CORE_ASSERT_MSG_INTERNAL(...) ::QE::LogManager::Get().PrintAssertMessage("QUEST", "Assertion Failed", ##__VA_ARGS__)
	#define QE_ASSERT_MSG_INTERNAL(...) ::QE::LogManager::Get().PrintAssertMessage("GAME", "Assertion Failed", ##__VA_ARGS__)

	#define QE_CORE_ASSERT(condition, ...) { if (!(condition)) { QE_CORE_ASSERT_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
	#define QE_ASSERT(condition, ...) { if (!(condition)) { QE_ASSERT_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
#else
	#define QE_CORE_ASSERT(condition, ...)
	#define QE_ASSERT(condition, ...)
#endif

#ifdef QE_ENABLE_VERIFY
	#define QE_CORE_VERIFY_MSG_INTERNAL(...) ::QE::LogManager::Get().PrintAssertMessage("QUEST", "Verify Failed", ##__VA_ARGS__)
	#define QE_VERIFY_MSG_INTERNAL(...) ::QE::LogManager::Get().PrintAssertMessage("GAME", "Verify Failed", ##__VA_ARGS__)

	#define QE_CORE_VERIFY(condition, ...) { if (!(condition)) { QE_CORE_VERIFY_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
	#define QE_VERIFY(condition, ...) { if (!(condition)) { QE_VERIFY_MSG_INTERNAL(__VA_ARGS__); QE_DEBUG_BREAK; } }
#else
	#define QE_CORE_VERIFY(condition, ...)
	#define QE_VERIFY(condition, ...)
#endif

#endif // QE_CORE_ASSERT_H_INCLUDED
