#pragma once
#include "Core/Common.h"

#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/InputManager.h"

namespace QE
{
	// The context of the engine, manager of managers and everything else, the Root object
	// And yes, it is a singleton.
	class Engine
	{
	public:
		~Engine() = default;
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;

		static Engine& Get();
		static Engine* GetPtr();

		void Initialize();
		void Shutdown();

		// This is the game loop
		void Run();

		// These pointers/references are guaranteed to exist for the entire lifetime of the program
		// So if you choose you can grab a pointer to one of  these and just store it
		Application& GetApplication();
		Application* GetApplicationPtr();
		Window& GetWindow();
		Window* GetWindowPtr();
		InputManager& GetInputManager();
		InputManager* GetInputManagerPtr();
	private:
		Engine() {}

		bool m_Running = true;

		// Baseline engine systems
		ScopedPtr<Application> m_Application;
		ScopedPtr<Window> m_Window;
		ScopedPtr<InputManager> m_InputManager;
	};
}
