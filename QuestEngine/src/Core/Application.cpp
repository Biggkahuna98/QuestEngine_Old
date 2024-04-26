#include "Application.h"

#include "Logger.h"
#include "Assert.h"
#include <iostream>
#include <tracy/Tracy.hpp>

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
