#include "QuestEngine.h"
#include "Core/Application.h"

Quest::QuestEngine* Quest::QuestEngine::s_Instance = nullptr;

namespace Quest
{
	void QuestEngine::Init()
	{
		// Explicitely create the static instance
		s_Instance = new QuestEngine();

		// Create the application by user-provided function
		s_Instance->m_Application = CreateApplication();
	}

	void QuestEngine::Shutdown()
	{
		// Delete the instance
		delete s_Instance;
	}

	QuestEngine& QuestEngine::Get()
	{
		return *s_Instance;
	}

	QuestEngine* QuestEngine::GetPtr()
	{
		return s_Instance;
	}

	Application& QuestEngine::GetApplication()
	{
		return *m_Application;
	}
}