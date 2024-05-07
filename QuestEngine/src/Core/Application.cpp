#include "Application.h"
#include "QuestCommon.h"
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

	void Application::Update()
	{
	}
}
