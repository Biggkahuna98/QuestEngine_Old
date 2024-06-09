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

		void Log(const std::string_view msg);

		template<typename... Args>
		void Log(std::string_view fmtStr, Args&&... args);
	private:
		std::string m_LogName;
		Level m_LogLevel{ Level::Trace };
		std::vector<ISink*> m_Sinks;
	};


	template<typename ...Args>
	inline void Logger::Log(const std::string_view fmtStr, Args && ...args)
	{
		for (auto sink : m_Sinks)
		{
			if (sink->ShouldMessageBeLogged(m_LogLevel))
			{
				sink->Log(std::vformat(fmtStr, std::make_format_args(args...)));
			}
		}
	}
}