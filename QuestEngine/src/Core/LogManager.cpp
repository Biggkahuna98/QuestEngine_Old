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
		case LogManager::Level::Warn: return QLog::Level::Warn;
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
}