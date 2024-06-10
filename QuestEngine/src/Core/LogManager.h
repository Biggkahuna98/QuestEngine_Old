#pragma once

#include "QuestTypes.h"
#include "Utility/QLog/QLogger.h"
#include "Utility/QLog/ColoredConsoleSink.h"
#include "Utility/QLog/FileSink.h"

#include <vector>
#include <unordered_map>

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
	private:
		LogManager() {};
		static LogManager* s_Instance;

		std::unordered_map<std::string, QLog::Logger*> m_Loggers;
	};
}