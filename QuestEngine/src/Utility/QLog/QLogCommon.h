#pragma once
#include <cstdint>
#include <format>

namespace QLog
{
	enum class Level : uint8_t
	{
		Off = 0, Trace, Debug, Info, Warn, Error, Fatal
	};

	struct LogPayload
	{
		std::string_view format_str;
		std::format_args format_args;
		Level log_level;
	};
}