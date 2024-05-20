#include "Application.h"
#include "Core/QuestCommon.h"
#include "Engine/Engine.h"

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
