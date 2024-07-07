#include "Engine.h"

#include "Core/LogManager.h"
#include "Core/Profiler.h"


namespace QE
{
	Engine& Engine::Get()
	{
		static Engine instance;
		return instance;
	}

	Engine* Engine::GetPtr()
	{
		static Engine instance;
		return &instance;
	}

	void Engine::Initialize()
	{
		// Create the application by user-provided function
		m_Application = CreateApplication();
		m_Window = CreateScopedPtr<Window>(Window::CreateInfo());
		// Initialize other managers
		m_InputManager = CreateScopedPtr<InputManager>(m_Window->GetNativeWindow());
	}

	void Engine::Shutdown()
	{

	}

	void Engine::Run()
	{
		while (m_Running)
		{
			m_InputManager->ProcessTransitions(); // Must be called before window process events
			m_Window->ProcessEvents();
			// Check if we should close
			if (m_InputManager->IsKeyPressed(Key::Escape))
				m_Running = false;

			m_Window->SwapBuffers();
			//QE_PROFILE_FRAME;
		}
	}

	Application& Engine::GetApplication()
	{
		return *m_Application;
	}

	Application* Engine::GetApplicationPtr()
	{
		return m_Application.get();
	}

	Window& Engine::GetWindow()
	{
		return *m_Window;
	}

	Window* Engine::GetWindowPtr()
	{
		return m_Window.get();
	}

	InputManager& Engine::GetInputManager()
	{
		return *m_InputManager;
	}

	InputManager* Engine::GetInputManagerPtr()
	{
		return m_InputManager.get();
	}
}
