#pragma once

#include "QuestTypes.h"
#include "Utility/QLog/QLogger.h"
#include "Utility/QLog/ColoredConsoleSink.h"
#include "Utility/QLog/FileSink.h"

#include <vector>
#include <unordered_map>
#include <string_view>
#include <format>

namespace QE
{
	class LogManager
	{
	public:
		enum class Level : uint8
		{
			Trace = 0, Debug, Info, Warn, Error, Fatal
		};

		struct LoggerCreateInfo
		{
			std::string loggerName;
			Level logLevel{ Level::Trace };
			std::vector<QLog::SinkCreateInfo> sinks;
		};

		LogManager(LogManager& other) = delete;
		void operator=(const LogManager&) = delete;
		~LogManager();
		static LogManager& Get();
		static LogManager* GetPtr();

		void RegisterLogger(LoggerCreateInfo ci);
		QLog::Logger& GetLogger(std::string name);
		QLog::Logger* GetLoggerPtr(std::string name);

		friend inline QLog::Logger* GetOrCreateLogger(const std::string_view loggerName);

		template<typename... Args>
		constexpr void PrintMessage(const std::string_view loggerName, const LogManager::Level level, std::format_string<Args...> format, Args&&... args);
		template<typename... Args>
		constexpr void PrintMessageTag(const std::string_view loggerName, const LogManager::Level level, std::string_view tag, std::format_string<Args...> format, Args&&... args);
		template<typename... Args>
		constexpr void PrintAssertMessage(const std::string_view loggerName, const std::string_view failurePrefix, std::format_string<Args...> format, Args&&... args);
	private:
		LogManager() {};
		static LogManager* s_Instance;

		std::unordered_map<std::string, QLog::Logger*> m_Loggers;
	};

	void TestLoggerMacros();
}

// ********************************************************************
//
//
//	LOGGING MACROS FOR DEFAULT CREATED LOGGERS
//
// * Note: Prefer to use tagged logs for subsystems
// ********************************************************************

// Core
#define QE_CORE_TRACE_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Trace, tag, __VA_ARGS__)
#define QE_CORE_DEBUG_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Debug, tag, __VA_ARGS__)
#define QE_CORE_INFO_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Info, tag, __VA_ARGS__)
#define QE_CORE_WARN_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Warn, tag, __VA_ARGS__)
#define QE_CORE_ERROR_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Error, tag, __VA_ARGS__)
#define QE_CORE_FATAL_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("QUEST", ::QE::LogManager::Level::Fatal, tag, __VA_ARGS__)

// Game
#define QE_TRACE_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Trace, tag, __VA_ARGS__)
#define QE_DEBUG_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Debug, tag, __VA_ARGS__)
#define QE_INFO_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Info, tag, __VA_ARGS__)
#define QE_WARN_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Warn, tag, __VA_ARGS__)
#define QE_ERROR_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Error, tag, __VA_ARGS__)
#define QE_FATAL_TAG(tag, ...) ::QE::LogManager::Get().PrintMessageTag("GAME", ::QE::LogManager::Level::Fatal, tag, __VA_ARGS__)

// Core
#define QE_CORE_TRACE(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Trace, __VA_ARGS__)
#define QE_CORE_DEBUG(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Debug, __VA_ARGS__)
#define QE_CORE_INFO(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Info,__VA_ARGS__)
#define QE_CORE_WARN(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Warn, __VA_ARGS__)
#define QE_CORE_ERROR(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Error, __VA_ARGS__)
#define QE_CORE_FATAL(...) ::QE::LogManager::Get().PrintMessage("QUEST", ::QE::LogManager::Level::Fatal, __VA_ARGS__)

// Game
#define QE_TRACE(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Trace, __VA_ARGS__)
#define QE_DEBUG(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Debug, __VA_ARGS__)
#define QE_INFO(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Info, __VA_ARGS__)
#define QE_WARN(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Warn, __VA_ARGS__)
#define QE_ERROR(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Error, __VA_ARGS__)
#define QE_FATAL(...) ::QE::LogManager::Get().PrintMessage("GAME", ::QE::LogManager::Level::Fatal, __VA_ARGS__)

namespace QE
{

	inline QLog::Logger* GetOrCreateLogger(const std::string_view loggerName)
	{
		QLog::Logger* logger = nullptr;
		try
		{
			logger = LogManager::Get().m_Loggers.at(loggerName.data());
		}
		catch (std::out_of_range e)
		{
			// Kind of gross, but create the logger if it doesn't exist, then use it
			std::string logFileName = "";
			logFileName.append("logs/").append(loggerName.data()).append(".log");
			LogManager::LoggerCreateInfo newLoggerCI = {
			.loggerName = loggerName.data(),
			.logLevel = LogManager::Level::Trace,
			.sinks = {
				{QLog::SinkType::ColoredConsoleSink, "", true},
				{QLog::SinkType::FileSink, logFileName, false}
			}
			};
			LogManager::Get().RegisterLogger(newLoggerCI);

			logger = LogManager::Get().m_Loggers.at(loggerName.data());
		}

		return logger;
	}

	template<typename ...Args>
	inline constexpr void LogManager::PrintMessage(const std::string_view loggerName, const LogManager::Level level, std::format_string<Args...> format, Args&&... args)
	{
		QLog::Logger* logger = GetOrCreateLogger(loggerName);
		const std::string formatted = std::format(format, std::forward<Args>(args)...);
		switch (level)
		{
		case Level::Trace:
			logger->Trace(formatted);
			break;
		case Level::Debug:
			logger->Debug(formatted);
			break;
		case Level::Info:
			logger->Info(formatted);
			break;
		case Level::Warn:
			logger->Warn(formatted);
			break;
		case Level::Error:
			logger->Error(formatted);
			break;
		case Level::Fatal:
			logger->Fatal(formatted);
			break;
		}
	}

	template<typename ...Args>
	inline constexpr void LogManager::PrintMessageTag(const std::string_view loggerName, const LogManager::Level level, std::string_view tag, std::format_string<Args...> format, Args&&... args)
	{
		QLog::Logger* logger = GetOrCreateLogger(loggerName);
		const std::string formatted = std::format(format, std::forward<Args>(args)...);
		switch (level)
		{
		case Level::Trace:
			logger->Trace("[{0}] - {1}", tag, formatted);
			break;
		case Level::Debug:
			logger->Debug("[{0}] - {1}", tag, formatted);
			break;
		case Level::Info:
			logger->Info("[{0}] - {1}", tag, formatted);
			break;
		case Level::Warn:
			logger->Warn("[{0}] - {1}", tag, formatted);
			break;
		case Level::Error:
			logger->Error("[{0}] - {1}", tag, formatted);
			break;
		case Level::Fatal:
			logger->Fatal("[{0}] - {1}", tag, formatted);
			break;
		}
	}

	template<typename... Args>
	inline constexpr void LogManager::PrintAssertMessage(const std::string_view loggerName, const std::string_view failurePrefix, std::format_string<Args...> format, Args&&... args)
	{
		QLog::Logger* logger = GetOrCreateLogger(loggerName);
		const std::string formatted = std::format(format, std::forward<Args>(args)...);
		logger->Error("{0}: {1}", failurePrefix, formatted);
	}
}