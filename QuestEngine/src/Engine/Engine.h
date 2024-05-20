#pragma once
#include "Core/QuestCommon.h"

#include "Engine/Application.h"
#include "Core/Window.h"
#include "Core/InputManager.h"

namespace Quest
{
	extern int gCounterTest;
	// The context of the engine, manager of managers and everything else
	// And yes, it is a global singleton.
	class Engine
	{
	public:
		// Initialized and shut down explicitely
		~Engine() {}
		static void Init();
		static void Shutdown();
		static Engine& Get();
		static Engine* GetPtr();

		// This is the game loop
		void Run();

		Application& GetApplication();
		Application* GetApplicationPtr();
		Window& GetWindow();
		Window* GetWindowPtr();
		InputManager& GetInputManager();
		InputManager* GetInputManagerPtr();
	private:
		Engine() {} // private to make singleton
		static Engine* s_Instance;
		bool m_Running = true;

		// Baseline engine systems
		ScopedPtr<Application> m_Application;
		ScopedPtr<Window> m_Window;
		ScopedPtr<InputManager> m_InputManager;
	};
}
