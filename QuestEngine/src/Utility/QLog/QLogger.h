#pragma once

#include <string>
#include <vector>

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

		void Log(const std::string_view msg);
	private:
		std::string m_LogName;

		std::vector<ISink*> m_Sinks;
	};
}