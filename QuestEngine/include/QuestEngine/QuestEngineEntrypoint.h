#pragma once

#include "Engine/Engine.h"
#include "Core/LogManager.h"
#include "Core/Globals.h"

void InitializeMainLoggers()
{
	using namespace QE;
	// Engine logger
	LogManager::LoggerCreateInfo engineLoggerCI = {
	.loggerName = "Quest",
	.logLevel = LogManager::Level::Trace,
	.sinks = {
		{QLog::SinkType::ColoredConsoleSink, "", true},
		{QLog::SinkType::FileSink, "logs/Quest.log", true}
	}
	};
	LogManager::Get().RegisterLogger(engineLoggerCI);

	// Application logger
	LogManager::LoggerCreateInfo gameLoggerCI = {
	.loggerName = "Game",
	.logLevel = LogManager::Level::Trace,
	.sinks = {
		{QLog::SinkType::ColoredConsoleSink, "", true},
		{QLog::SinkType::FileSink, "logs/Game.log", true}
	}
	};
	LogManager::Get().RegisterLogger(gameLoggerCI);
}

// THE ENTRYPOINT FOR THE ENGINE
// Initialize the engine systems and then create the user-defined application
int QE::gCounterTest = 0;

int main(int argc, char** argv)
{
	QE::gCounterTest = 1;
	// Initialize logger system before anything else
	InitializeMainLoggers();

	// Initialize the engine context global
	QE::Engine g_Engine;

	// Run the main loop
	g_Engine.Run();

	// Shutdown the engine
	//QE::g_Engine.Shutdown();

	return 0;
}
