#pragma once

#include <string>
#include <vector>
#include <format>

#include "QLogCommon.h"
#include "ISink.h"

namespace QLog
{
	class Logger
	{
	public:
		Logger(const std::string loggerName, SinkCreateInfo sinkCI);
		Logger(const std::string loggerName, const std::vector<SinkCreateInfo> sinkCIs);
		~Logger();

		Level GetLogLevel();
		void SetLogLevel(Level lvl);

		template<typename... Args>
		constexpr void Trace(const std::string_view fmtStr, Args&&... args);
		template<typename... Args>
		constexpr void Debug(const std::string_view fmtStr, Args&&... args);
		template<typename... Args>
		constexpr void Info(const std::string_view fmtStr, Args&&... args);
		template<typename... Args>
		constexpr void Warn(const std::string_view fmtStr, Args&&... args);
		template<typename... Args>
		constexpr void Error(const std::string_view fmtStr, Args&&... args);
		template<typename... Args>
		constexpr void Fatal(const std::string_view fmtStr, Args&&... args);
	private:
		void Log(SinkLogPayload payload);
		void Format(Level msgLevel, const std::string_view msg);
	private:
		std::string m_LogName;
		Level m_LogLevel{ Level::Trace };
		std::vector<ISink*> m_Sinks;
	};

	template<typename ...Args>
	inline constexpr void Logger::Trace(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Trace, std::vformat(fmtStr, std::make_format_args(args...)));
	}

	template<typename ...Args>
	inline constexpr void Logger::Debug(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Debug, std::vformat(fmtStr, std::make_format_args(args...)));
	}

	template<typename ...Args>
	inline constexpr void Logger::Info(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Info, std::vformat(fmtStr, std::make_format_args(args...)));
	}

	template<typename ...Args>
	inline constexpr void Logger::Warn(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Warn, std::vformat(fmtStr, std::make_format_args(args...)));
	}

	template<typename ...Args>
	inline constexpr void Logger::Error(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Error, std::vformat(fmtStr, std::make_format_args(args...)));
	}

	template<typename ...Args>
	inline constexpr void Logger::Fatal(const std::string_view fmtStr, Args && ...args)
	{
		Format(Level::Fatal, std::vformat(fmtStr, std::make_format_args(args...)));
	}
}