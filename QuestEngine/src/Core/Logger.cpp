#include "Logger.h"

//#include "spdlog/sinks/stdout_color_sinks.h"
//#include "spdlog/sinks/basic_file_sink.h"

#include <filesystem>
#include <vector>

#include "ThirdParty/Tracy.h"

namespace QE
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	void Logger::Init(Logger::CreateInfo ci)
	{
		// Make sure the directory provided by the CI exists, otherwise create
		if (!std::filesystem::exists(ci.logsDirectory))
			std::filesystem::create_directories(ci.logsDirectory);

		// Build the sink directories
		const std::string coreLogFile = ci.logsDirectory + "/" + ci.coreLogFileName;
		const std::string clientLogFile = ci.logsDirectory + "/" + ci.clientLogFileName;

		std::vector<spdlog::sink_ptr> engineSinks =
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(coreLogFile, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		std::vector<spdlog::sink_ptr> clientSinks =
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(clientLogFile, true),
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
		};

		engineSinks[0]->set_pattern("[%T] [%l] %n: %v");
		clientSinks[0]->set_pattern("[%T] [%l] %n: %v");

		engineSinks[1]->set_pattern("%^[%T] %n: %v%$");
		clientSinks[1]->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>(ci.coreLoggerName, engineSinks.begin(), engineSinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>(ci.clientLoggerName, clientSinks.begin(), clientSinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

	void Logger::Shutdown()
	{
		s_ClientLogger.reset();
		s_CoreLogger.reset();
		spdlog::drop_all();
	}

	void TestLoggerMacros()
	{
		ZoneScoped;
		// Core
		QE_CORE_TRACE("{} {}", "Core:", "Trace");
		QE_CORE_DEBUG("{} {}", "Core:", "Debug");
		QE_CORE_INFO("{} {}", "Core:", "Info");
		QE_CORE_WARN("{} {}", "Core:", "Warn");
		QE_CORE_ERROR("{} {}", "Core:", "Error");
		QE_CORE_FATAL("{} {}", "Core:", "Fatal");

		QE_CORE_TRACE_TAG("Test", "{} {}", "Core Tag:", "Trace");
		QE_CORE_DEBUG_TAG("Test", "{} {}", "Core Tag:", "Debug");
		QE_CORE_INFO_TAG("Test", "{} {}", "Core Tag:", "Info");
		QE_CORE_WARN_TAG("Test", "{} {}", "Core Tag:", "Warn");
		QE_CORE_ERROR_TAG("Test", "{} {}", "Core Tag:", "Error");
		QE_CORE_FATAL_TAG("Test", "{} {}", "Core Tag:", "Fatal");

		// Client
		QE_TRACE("{} {}", "Client:", "Trace");
		QE_DEBUG("{} {}", "Client:", "Debug");
		QE_INFO("{} {}", "Client:", "Info");
		QE_WARN("{} {}", "Client:", "Warn");
		QE_ERROR("{} {}", "Client:", "Error");
		QE_FATAL("{} {}", "Client:", "Fatal");

		QE_TRACE_TAG("Test", "{} {}", "Client Tag:", "Trace");
		QE_DEBUG_TAG("Test", "{} {}", "Client Tag:", "Debug");
		QE_INFO_TAG("Test", "{} {}", "Client Tag:", "Info");
		QE_WARN_TAG("Test", "{} {}", "Client Tag:", "Warn");
		QE_ERROR_TAG("Test", "{} {}", "Client Tag:", "Error");
		QE_FATAL_TAG("Test", "{} {}", "Client Tag:", "Fatal");
	}
}
