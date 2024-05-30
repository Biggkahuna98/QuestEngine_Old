#pragma once
#include <cstdint>
#include "ThirdParty/fmt.h"

namespace QLog
{
	enum class Level : uint8_t
	{
		Off = 0, Trace, Debug, Info, Warn, Error, Fatal
	};

	struct LogPayload
	{
		fmt::string_view format_str;
		fmt::format_args format_args;
		Level log_level;
	};
}