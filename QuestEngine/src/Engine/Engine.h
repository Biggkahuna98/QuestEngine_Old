#pragma once
#include "Core/QuestCommon.h"

#include "Core/Application.h"
#include "Core/InputManager.h"

namespace Quest
{

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

		Application& GetApplication();
		Application* GetApplicationPtr();
		InputManager& GetInputManager();
		InputManager* GetInputManagerPtr();
	private:
		Engine() {} // private to make singleton
		static Engine* s_Instance;

		// Baseline engine systems
		ScopedPtr<Application> m_Application;
		ScopedPtr<InputManager> m_InputManager;
	};
}