#include "QLogger.h"

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

	void Logger::Log(const std::string_view msg)
	{
		for (auto sink : m_Sinks)
			sink->Log(msg);
	}
}