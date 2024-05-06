#pragma once
#include "Core/QuestCommon.h"


namespace Quest
{
	class Application;


	// The context of the engine, manager of managers and everything else
	// And yes, it is a global singleton.
	class QuestEngine
	{
	public:
		// Initialized and shut down explicitely
		~QuestEngine() {}
		static void Init();
		static void Shutdown();
		static QuestEngine& Get();
		static QuestEngine* GetPtr();

		Application& GetApplication();
	private:
		QuestEngine() {} // private to make singleton
		static QuestEngine* s_Instance;

		// Baseline engine systems
		ScopedPtr<Application> m_Application;
	};
}