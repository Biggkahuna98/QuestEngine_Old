#pragma once

#include "spdlog/spdlog.h"

#include <memory>
#include <string>
#include <string_view>
#include <format>

namespace Quest
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

		static void Init();
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		template<typename... Args>
		static void PrintMessage(Logger::Type type, Logger::Level level, std::format_string<Args...> format, Args&&... args);

		template<typename... Args>
		static void PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::format_string<Args...> format, Args&&... args);

		static void PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::string_view message);

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	void TestLoggerMacros();
}

//  PREFER TAGGED LOGS OVER NONTAGGED
// Core logging
#define QE_CORE_TRACE_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Trace, tag, __VA_ARGS__)
#define QE_CORE_DEBUG_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Debug, tag, __VA_ARGS__)
#define QE_CORE_INFO_TAG(tag, ...)  ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Info, tag, __VA_ARGS__)
#define QE_CORE_WARN_TAG(tag, ...)  ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Warn, tag, __VA_ARGS__)
#define QE_CORE_ERROR_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Error, tag, __VA_ARGS__)
#define QE_CORE_FATAL_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Fatal, tag, __VA_ARGS__)

// Client logging
#define QE_TRACE_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Trace, tag, __VA_ARGS__)
#define QE_DEBUG_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Debug, tag, __VA_ARGS__)
#define QE_INFO_TAG(tag, ...)  ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Info, tag, __VA_ARGS__)
#define QE_WARN_TAG(tag, ...)  ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Warn, tag, __VA_ARGS__)
#define QE_ERROR_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Error, tag, __VA_ARGS__)
#define QE_FATAL_TAG(tag, ...) ::Quest::Logger::PrintMessageTag(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Fatal, tag, __VA_ARGS__)

// Core Logging
#define QE_CORE_TRACE(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Trace, __VA_ARGS__)
#define QE_CORE_DEBUG(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Debug, __VA_ARGS__)
#define QE_CORE_INFO(...)   ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Info, __VA_ARGS__)
#define QE_CORE_WARN(...)   ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Warn, __VA_ARGS__)
#define QE_CORE_ERROR(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Error, __VA_ARGS__)
#define QE_CORE_FATAL(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Core, ::Quest::Logger::Level::Fatal, __VA_ARGS__)

// Client logging
#define QE_TRACE(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Trace, __VA_ARGS__)
#define QE_DEBUG(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Debug, __VA_ARGS__)
#define QE_INFO(...)   ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Info, __VA_ARGS__)
#define QE_WARN(...)   ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Warn, __VA_ARGS__)
#define QE_ERROR(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Error, __VA_ARGS__)
#define QE_FATAL(...)  ::Quest::Logger::PrintMessage(::Quest::Logger::Type::Client, ::Quest::Logger::Level::Fatal, __VA_ARGS__)

namespace Quest
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

	inline void Logger::PrintMessageTag(Logger::Type type, Logger::Level level, std::string_view tag, std::string_view message)
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
	}
}