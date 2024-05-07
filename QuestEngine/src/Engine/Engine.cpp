#include "Engine.h"
#include "Core/Application.h"
#include "Core/InputManager.h"

Quest::Engine* Quest::Engine::s_Instance = nullptr;

namespace Quest
{
	void Engine::Init()
	{
		// Explicitely create the static instance
		s_Instance = new Engine();

		// Create the application by user-provided function
		s_Instance->m_Application = CreateApplication();
		// Initialize other managers
		s_Instance->m_InputManager = CreateScopedPtr<InputManager>(s_Instance->m_Application->GetWindow().GetNativeWindow());
	}

	void Engine::Shutdown()
	{
		// Delete the instance
		delete s_Instance;
	}

	Engine& Engine::Get()
	{
		return *s_Instance;
	}

	Engine* Engine::GetPtr()
	{
		return s_Instance;
	}

	Application& Engine::GetApplication()
	{
		return *m_Application;
	}

	Application* Engine::GetApplicationPtr()
	{
		return m_Application.get();
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