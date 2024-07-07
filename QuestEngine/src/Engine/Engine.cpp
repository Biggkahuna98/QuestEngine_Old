#include "Engine.h"

#include "Core/LogManager.h"
#include "Core/Profiler.h"
#include "Core/Globals.h"

//QE::Engine* QE::Engine::s_Instance = nullptr;

namespace QE
{
	Engine::Engine()
	{
		// Explicitely create the static instance
		//s_Instance = new Engine();

		// Create the application by user-provided function
		m_Application = CreateApplication();
		m_Window = CreateScopedPtr<Window>(Window::CreateInfo());
		// Initialize other managers
		m_InputManager = CreateScopedPtr<InputManager>(m_Window->GetNativeWindow());
		gCounterTest++;
		QE_CORE_DEBUG_TAG("GLOBAL", "Counter: {}", QE::gCounterTest);
	}

	Engine::~Engine()
	{

	}

	/*Engine& Engine::Get()
	{
		return *s_Instance;
	}

	Engine* Engine::GetPtr()
	{
		return s_Instance;
	}*/

	void Engine::Run()
	{
		while (m_Running)
		{
			gCounterTest++;

			m_Window->ProcessEvents();
			//QE_CORE_DEBUG_TAG("GLOBAL", "Counter: {}", Quest::gCounterTest);
			// Check if we should close
			if (m_InputManager->IsKeyPressed(Key::Escape))
				m_Running = false;
			if (m_InputManager->IsKeyPressed(Key::A))
				QE_CORE_DEBUG_TAG("INPUT", "{}", "A was pressed");

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
