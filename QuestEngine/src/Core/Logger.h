#ifndef QE_CORE_LOGGER_H_INCLUDED
#define QE_CORE_LOGGER_H_INCLUDED

#include "ThirdParty/spdlog.h"

#include <memory>
#include <string>
#include <string_view>
#include <format>

namespace QE
{
	class Logger
	{
	public:
		enum class Type : uint8_t
		{
			Core = 0, Client = 1
		};

		enum class Level : uint8_t
		{
			Trace = 0, Debug, Info, Warn, Error, Fatal
		};

		struct CreateInfo
		{
			std::string coreLoggerName { "QUEST" };
			std::string clientLoggerName { "APP" };
			std::string coreLogFileName { "Quest.log" };
			std::string clientLogFileName { "App.log" };
			std::string logsDirectory { "logs" };
			Level coreLevel { Level::Trace };
			Level clientLevel { Level::Trace };
		};

		static void Init(Logger::CreateInfo ci);
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		template<typename... Args>
		static void PrintMessage(Logger::Type type, Logger::Level level, std::format_string<Args...> format, Args&&... args);

		template<typename... Args>
		static void PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::format_string<Args...> format, Args&&... args);

		template<typename... Args>
		static void PrintAssertMessage(Logger::Type type, std::string_view failurePrefix, std::format_string<Args...> format, Args&&... args);

		//static void PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::string_view message);

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	void TestLoggerMacros();
}

//  PREFER TAGGED LOGS OVER NONTAGGED
// Core logging
#define QE_CORE_TRACE_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Trace, tag, __VA_ARGS__)
#define QE_CORE_DEBUG_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Debug, tag, __VA_ARGS__)
#define QE_CORE_INFO_TAG(tag, ...)  ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Info, tag, __VA_ARGS__)
#define QE_CORE_WARN_TAG(tag, ...)  ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Warn, tag, __VA_ARGS__)
#define QE_CORE_ERROR_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Error, tag, __VA_ARGS__)
#define QE_CORE_FATAL_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Core, ::QE::Logger::Level::Fatal, tag, __VA_ARGS__)

// Client logging
#define QE_TRACE_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Trace, tag, __VA_ARGS__)
#define QE_DEBUG_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Debug, tag, __VA_ARGS__)
#define QE_INFO_TAG(tag, ...)  ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Info, tag, __VA_ARGS__)
#define QE_WARN_TAG(tag, ...)  ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Warn, tag, __VA_ARGS__)
#define QE_ERROR_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Error, tag, __VA_ARGS__)
#define QE_FATAL_TAG(tag, ...) ::QE::Logger::PrintMessageTag(::QE::Logger::Type::Client, ::QE::Logger::Level::Fatal, tag, __VA_ARGS__)

// Core Logging
#define QE_CORE_TRACE(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Trace, __VA_ARGS__)
#define QE_CORE_DEBUG(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Debug, __VA_ARGS__)
#define QE_CORE_INFO(...)   ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Info, __VA_ARGS__)
#define QE_CORE_WARN(...)   ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Warn, __VA_ARGS__)
#define QE_CORE_ERROR(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Error, __VA_ARGS__)
#define QE_CORE_FATAL(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Core, ::QE::Logger::Level::Fatal, __VA_ARGS__)

// Client logging
#define QE_TRACE(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Trace, __VA_ARGS__)
#define QE_DEBUG(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Debug, __VA_ARGS__)
#define QE_INFO(...)   ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Info, __VA_ARGS__)
#define QE_WARN(...)   ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Warn, __VA_ARGS__)
#define QE_ERROR(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Error, __VA_ARGS__)
#define QE_FATAL(...)  ::QE::Logger::PrintMessage(::QE::Logger::Type::Client, ::QE::Logger::Level::Fatal, __VA_ARGS__)

namespace QE
{
	template<typename... Args>
	void Logger::PrintMessage(Logger::Type type, Logger::Level level, const std::format_string<Args...> format, Args&&... args)
	{
		auto logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		std::string formatted = std::format(format, std::forward<Args>(args)...);
		switch (level)
		{
		case Level::Trace:
			logger->trace(formatted);
			break;
		case Level::Debug:
			logger->debug(formatted);
			break;
		case Level::Info:
			logger->info(formatted);
			break;
		case Level::Warn:
			logger->warn(formatted);
			break;
		case Level::Error:
			logger->error(formatted);
			break;
		case Level::Fatal:
			logger->critical(formatted);
			break;
		}
	}

	template<typename... Args>
	void Logger::PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, const std::format_string<Args...> format, Args&&... args)
	{
		auto logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		std::string formatted = std::format(format, std::forward<Args>(args)...);
		switch (level)
		{
		case Level::Trace:
			logger->trace("[{0}] {1}", tag, formatted);
			break;
		case Level::Debug:
			logger->debug("[{0}] {1}", tag, formatted);
			break;
		case Level::Info:
			logger->info("[{0}] {1}", tag, formatted);
			break;
		case Level::Warn:
			logger->warn("[{0}] {1}", tag, formatted);
			break;
		case Level::Error:
			logger->error("[{0}] {1}", tag, formatted);
			break;
		case Level::Fatal:
			logger->critical("[{0}] {1}", tag, formatted);
			break;
		}
	}

	/*inline void Logger::PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::string_view message)
	{
		auto logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		switch (level)
		{
		case Level::Trace:
			logger->trace("[{0}] {1}", tag, message);
			break;
		case Level::Debug:
			logger->debug("[{0}] {1}", tag, message);
			break;
		case Level::Info:
			logger->info("[{0}] {1}", tag, message);
			break;
		case Level::Warn:
			logger->warn("[{0}] {1}", tag, message);
			break;
		case Level::Error:
			logger->error("[{0}] {1}", tag, message);
			break;
		case Level::Fatal:
			logger->critical("[{0}] {1}", tag, message);
			break;
		}
	}*/

	template<typename... Args>
	void Logger::PrintAssertMessage(Logger::Type type, std::string_view failurePrefix, std::format_string<Args...> format, Args&&... args)
	{
		auto logger = (type == Type::Core) ? GetCoreLogger() : GetClientLogger();
		std::string formatted = std::format(format, std::forward<Args>(args)...);
		logger->error("{0}: {1}", failurePrefix, formatted);
	}
}

#endif // QE_CORE_LOGGER_H_INCLUDED
