#include "Logger.h"

#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#undef _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS

#include <filesystem>
#include <vector>

namespace Quest
{
	// Helper to convert Logger::Level -> spdlog::level
	spdlog::level::level_enum InternalLevelToSPDLogLevel(Logger::Level level)
	{
		switch (level)
		{
		case Logger::Level::Trace:
			return spdlog::level::trace;
		case Logger::Level::Info:
			return spdlog::level::info;
		case Logger::Level::Warn:
			return spdlog::level::warn;
		case Logger::Level::Error:
			return spdlog::level::err;
		case Logger::Level::Fatal:
			return spdlog::level::critical;
		}
	}

	Logger::Logger(LoggerCreateInfo createInfo)
	{
		// Create the provided log directory if it does not exist
		if (!std::filesystem::exists(createInfo.logDirectory))
			std::filesystem::create_directories(createInfo.logDirectory);

		// Setup the sinks for spdlog
		std::vector<spdlog::sink_ptr> coreSinks =
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(createInfo.logDirectory + "/" + createInfo.coreLoggerName, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		std::vector<spdlog::sink_ptr> clientSinks =
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(createInfo.logDirectory + "/" + createInfo.clientLoggerName, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		// Set the patterns
		coreSinks[0]->set_pattern("[%T] [%l] %n: %v");
		clientSinks[0]->set_pattern("[%T] [%l] %n: %v");

		coreSinks[1]->set_pattern("%^[%T] %n: %v%$");
		clientSinks[1]->set_pattern("%^[%T] %n: %v%$");

		// Create the loggers
		m_CoreLogger = std::make_shared<spdlog::logger>(createInfo.coreLoggerName, coreSinks.begin(), coreSinks.end());
		m_CoreLogger->set_level(InternalLevelToSPDLogLevel(createInfo.coreLevel));

		m_ClientLogger = std::make_shared<spdlog::logger>(createInfo.clientLoggerName, clientSinks.begin(), clientSinks.end());
		m_ClientLogger->set_level(InternalLevelToSPDLogLevel(createInfo.clientLevel));
	}

	Logger::~Logger()
	{
		// Close down the spdlog loggers
		m_CoreLogger.reset();
		m_ClientLogger.reset();
		spdlog::drop_all();
	}

	inline std::shared_ptr<spdlog::logger>& Logger::GetCoreLogger()
	{
		return m_CoreLogger;
	}

	inline std::shared_ptr<spdlog::logger>& Logger::GetClientLogger()
	{
		return m_ClientLogger;
	}

	void Logger::SetCoreLevel(Level level)
	{
		m_CoreLogger->set_level(InternalLevelToSPDLogLevel(level));
	}

	void Logger::SetClientLevel(Level level)
	{
		m_ClientLogger->set_level(InternalLevelToSPDLogLevel(level));
	}
}