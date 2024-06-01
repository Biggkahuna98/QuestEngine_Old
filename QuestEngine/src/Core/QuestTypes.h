#ifndef QUEST_CORE_QUESTTYPES_H_INCLUDED
#define QUEST_CORE_QUESTTYPES_H_INCLUDED

#include <cstdint>

namespace QE
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
static_assert(sizeof(QE::int8) == 1, "int8 should be 1 byte");
static_assert(sizeof(QE::int16) == 2, "int16 should be 2 bytes");
static_assert(sizeof(QE::int32) == 4, "int32 should be 4 bytes");
static_assert(sizeof(QE::int64) == 8, "int64 should be 8 bytes");

static_assert(sizeof(QE::uint8) == 1, "uint8 should be 1 byte");
static_assert(sizeof(QE::uint16) == 2, "uint16 should be 2 bytes");
static_assert(sizeof(QE::uint32) == 4, "uint32 should be 4 bytes");
static_assert(sizeof(QE::uint64) == 8, "uint64 should be 8 bytes");

static_assert(sizeof(QE::f32) == 4, "f32 should be 4 bytes");
static_assert(sizeof(QE::f64) == 8, "f64 should be 8 bytes");

#endif // QUEST_CORE_QUESTTYPES_H_INCLUDED
