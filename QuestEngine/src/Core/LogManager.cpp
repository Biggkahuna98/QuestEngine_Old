#include "LogManager.h"
#include <iostream>

namespace QE
{
	LogManager* LogManager::s_Instance = nullptr;

	// Helper to convert LogManager::Level to QLog::Level
	QLog::Level ConvertToInternalLevel(LogManager::Level lvl)
	{
		switch (lvl)
		{
		case LogManager::Level::Trace: return QLog::Level::Trace;
		case LogManager::Level::Debug: return QLog::Level::Debug;
		case LogManager::Level::Info: return QLog::Level::Info;
		case LogManager::Level::Warning: return QLog::Level::Warn;
		case LogManager::Level::Error: return QLog::Level::Error;
		case LogManager::Level::Fatal: return QLog::Level::Fatal;
		}
	}

	LogManager::~LogManager()
	{
		for (auto element : m_Loggers)
		{
			m_Loggers.erase(element.first);
			delete element.second;
		}
	}

	LogManager& LogManager::Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new LogManager();
		return *s_Instance;
	}

	LogManager* LogManager::GetPtr()
	{
		if (s_Instance == nullptr)
			s_Instance = new LogManager();
		return s_Instance;
	}

	void LogManager::RegisterLogger(LoggerCreateInfo ci)
	{
		m_Loggers.try_emplace(ci.loggerName, new QLog::Logger(ci.loggerName, ci.sinks));
		m_Loggers.at(ci.loggerName)->SetLogLevel(ConvertToInternalLevel(ci.logLevel));
	}

	QLog::Logger& LogManager::GetLogger(std::string name)
	{
		return *m_Loggers.at(name);
	}

	QLog::Logger* LogManager::GetLoggerPtr(std::string name)
	{
		return m_Loggers.at(name);
	}


	void TestLoggerMacros()
	{
		//ZoneScoped;
		// Core
		QE_CORE_TRACE("{} {}", "Core:", "Trace");
		QE_CORE_DEBUG("{} {}", "Core:", "Debug");
		QE_CORE_INFO("{} {}", "Core:", "Info");
		QE_CORE_WARNING("{} {}", "Core:", "Warning");
		QE_CORE_ERROR("{} {}", "Core:", "Error");
		QE_CORE_FATAL("{} {}", "Core:", "Fatal");

		QE_CORE_TRACE_TAG("Test", "{} {}", "Core Tag:", "Trace");
		QE_CORE_DEBUG_TAG("Test", "{} {}", "Core Tag:", "Debug");
		QE_CORE_INFO_TAG("Test", "{} {}", "Core Tag:", "Info");
		QE_CORE_WARNING_TAG("Test", "{} {}", "Core Tag:", "Warning");
		QE_CORE_ERROR_TAG("Test", "{} {}", "Core Tag:", "Error");
		QE_CORE_FATAL_TAG("Test", "{} {}", "Core Tag:", "Fatal");

		// Client
		QE_TRACE("{} {}", "Client:", "Trace");
		QE_DEBUG("{} {}", "Client:", "Debug");
		QE_INFO("{} {}", "Client:", "Info");
		QE_WARNING("{} {}", "Client:", "Warning");
		QE_ERROR("{} {}", "Client:", "Error");
		QE_FATAL("{} {}", "Client:", "Fatal");

		QE_TRACE_TAG("Test", "{} {}", "Client Tag:", "Trace");
		QE_DEBUG_TAG("Test", "{} {}", "Client Tag:", "Debug");
		QE_INFO_TAG("Test", "{} {}", "Client Tag:", "Info");
		QE_WARNING_TAG("Test", "{} {}", "Client Tag:", "Warning");
		QE_ERROR_TAG("Test", "{} {}", "Client Tag:", "Error");
		QE_FATAL_TAG("Test", "{} {}", "Client Tag:", "Fatal");
	}
}

