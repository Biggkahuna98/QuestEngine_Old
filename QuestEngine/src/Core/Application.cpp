#include "Application.h"
#include "QuestCommon.h"

#include <iostream>

namespace Quest
{
	Application::Application()
	{
		TestLoggerMacros();
		Window::CreateInfo windowCI =
		{
			.Title = "Quest Engine",
			.Width = 1920,
			.Height = 1080
		};
		m_Window = CreateScopedPtr<Window>(windowCI);
		
	}

	Application::~Application() noexcept
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_Window->ProcessEvents();
			m_Window->SwapBuffers();
		}
	}
}
