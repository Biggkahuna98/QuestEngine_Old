#ifndef QUEST_CORE_QUESTTYPES_H_INCLUDED
#define QUEST_CORE_QUESTTYPES_H_INCLUDED

#include <cstdint>

namespace Quest
{
	// Signed integers
	using int8 = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	// Unsigned integers
	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;

	// Floats
	using f32 = float;
	using f64 = double;
}

// Confirm sizes
static_assert(sizeof(Quest::int8) == 1, "int8 should be 1 byte");
static_assert(sizeof(Quest::int16) == 2, "int16 should be 2 bytes");
static_assert(sizeof(Quest::int32) == 4, "int32 should be 4 bytes");
static_assert(sizeof(Quest::int64) == 8, "int64 should be 8 bytes");

static_assert(sizeof(Quest::uint8) == 1, "uint8 should be 1 byte");
static_assert(sizeof(Quest::uint16) == 2, "uint16 should be 2 bytes");
static_assert(sizeof(Quest::uint32) == 4, "uint32 should be 4 bytes");
static_assert(sizeof(Quest::uint64) == 8, "uint64 should be 8 bytes");

static_assert(sizeof(Quest::f32) == 4, "f32 should be 4 bytes");
static_assert(sizeof(Quest::f64) == 8, "f64 should be 8 bytes");

#endif // QUEST_CORE_QUESTTYPES_H_INCLUDED
