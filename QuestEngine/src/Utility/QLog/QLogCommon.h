#pragma once
#include <cstdint>
#include <format>

namespace QLog
{
	enum class Level : uint8_t
	{
		Off = 0, Trace, Debug, Info, Warn, Error, Fatal
	};

	constexpr std::string LevelToString(Level lvl)
	{
		switch (lvl)
		{
		case Level::Trace: return "Trace";
		case Level::Debug: return "Debug";
		case Level::Info: return "Info";
		case Level::Warn: return "Warn";
		case Level::Error: return "Error";
		case Level::Fatal: return "Fatal";
		default:
			return "Off";
		}
	}

	struct SinkLogPayload
	{
		const Level level;
		const std::string_view msg;
	};
}