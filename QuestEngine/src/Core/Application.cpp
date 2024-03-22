#include "Application.h"

#include "Logger.h"
#include <iostream>

namespace Quest
{
	Application::Application()
	{
		std::cout << "Application::Application\n";
		Logger::LoggerCreateInfo ci;
		Logger mylogger(ci);

		mylogger.PrintMessage(Logger::Type::Core, Logger::Level::Trace, "[Application]", "Test");
	}

	Application::~Application() noexcept
	{
		std::cout << "Application::~Application\n";
	}

	void Application::Test()
	{
		std::cout << "Application::Test is successful\n";
	}
}
