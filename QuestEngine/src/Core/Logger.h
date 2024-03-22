#pragma once // NOLINT

#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
#include "spdlog/spdlog.h"
#undef _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS

#include <string>
#include <string_view>
#include <memory>

namespace Quest
{
	class Logger
	{
	public:
		enum class Type : uint8_t
		{
			Core = 0, Client
		};

		enum class Level : uint8_t
		{
			Trace = 0, Info, Warn, Error, Fatal
		};

		struct LoggerCreateInfo
		{
			std::string coreLoggerName = "QUEST";
			std::string clientLoggerName = "CLIENT";
			std::string coreLogFileName = "Quest.log";
			std::string clientLogFileName = "Client.log";
			std::string logDirectory = "logs";
			Level coreLevel = Level::Trace;
			Level clientLevel = Level::Trace;
		};

	public:
		Logger(LoggerCreateInfo createInfo);
		~Logger();

		inline std::shared_ptr<spdlog::logger>& GetCoreLogger();
		inline std::shared_ptr<spdlog::logger>& GetClientLogger();

		void SetCoreLevel(Level level);
		void SetClientLevel(Level level);

		//template<typename... Args>
		//void PrintMessage(Type type, Level level, std::string_view tag, std::string_view msg);

		template<typename... Args>
		void PrintMessage(Type type, Level level, std::string_view tag, Args&&... args);
		//void PrintMessage(Type type, std::string_view msg, Args&&... args);
	private:
		std::shared_ptr<spdlog::logger> m_CoreLogger;
		std::shared_ptr<spdlog::logger> m_ClientLogger;
	};

	// TEMPLATE IMPLEMENTATIONS
	template<typename ...Args>
	inline void Logger::PrintMessage(Type type, Level level, std::string_view tag, Args&&... args)
	{
		// Select which logger based on tag
		std::shared_ptr<spdlog::logger> logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		// Set the fmt string to be logged
		std::string logString = tag.empty() ? "{0}{1}" : "[{0}] {1}";
		switch (level)
		{
		case Level::Trace:
			logger->trace(logString, tag, fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Info:
			logger->info(logString, tag, fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Warn:
			logger->warn(logString, tag, fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Error:
			logger->error(logString, tag, fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Fatal:
			logger->critical(logString, tag, fmt::format(std::forward<Args>(args)...));
			break;
		}
	}

	/*template<typename ...Args>
	inline void Logger::PrintAssertMessage(Type type, std::string_view msg, Args&&... args)
	{
	}*/
}