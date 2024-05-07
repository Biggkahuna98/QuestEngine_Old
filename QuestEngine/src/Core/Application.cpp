#include "Application.h"
#include "QuestCommon.h"
#include "Engine/Engine.h"

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
		while (m_Running)
		{
			m_Window->ProcessEvents();
			// Check input for closing
			if (Engine::Get().GetInputManager().IsKeyPressed(Key::Escape))
				m_Running = false;

			m_Window->SwapBuffers();
		}
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}
}
