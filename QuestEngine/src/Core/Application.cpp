#include "Application.h"

#include "Logger.h"
#include "Assert.h"
#include <iostream>

namespace Quest
{
	Application::Application()
	{
		TestLoggerMacros();
	}

	Application::~Application() noexcept
	{
	}
}
