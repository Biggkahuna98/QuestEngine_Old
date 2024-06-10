#include "QLogger.h"

#include <chrono>

namespace QLog
{
	Logger::Logger(const std::string loggerName, SinkCreateInfo sinkCI)
		: m_LogName(loggerName)
	{
		m_Sinks.push_back(ISinkFactory::CreateSink(sinkCI));
	}

	Logger::Logger(const std::string loggerName, const std::vector<SinkCreateInfo> sinkCIs)
		: m_LogName(loggerName)
	{
		for (SinkCreateInfo sinkCI : sinkCIs)
			m_Sinks.push_back(ISinkFactory::CreateSink(sinkCI));
	}

	Logger::~Logger()
	{
		for (auto sink : m_Sinks)
			delete sink;
	}

	Level Logger::GetLogLevel()
	{
		return m_LogLevel;
	}

	void Logger::SetLogLevel(Level lvl)
	{
		m_LogLevel = lvl;
	}

	void Logger::Log(SinkLogPayload payload)
	{
		for (auto sink : m_Sinks)
		{
			if (sink->ShouldMessageBeLogged(m_LogLevel))
				sink->Log(payload);
		}
	}
	void Logger::Format(Level msgLevel, const std::string_view msg)
	{
		// Get the log level
		const std::string lvlAsString = LevelToString(msgLevel);
		// Get the current time
		auto systemTime = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() }.get_local_time();
		auto timePoint = floor<std::chrono::days>(systemTime);
		std::chrono::year_month_day ymd{ timePoint };
		std::chrono::hh_mm_ss time{ floor<std::chrono::seconds>(systemTime - timePoint) };

		const std::string completedFormat = std::format("[{0}] [{1}] [{2}]: {3}", time, m_LogName, lvlAsString, msg);

		// Log it to the sinks
		Log(
			{	
				.level = msgLevel,
				.msg = completedFormat
			}
		);
	}
}