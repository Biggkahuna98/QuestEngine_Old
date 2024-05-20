#ifndef QUEST_CORE_APPLICATION_H_INCLUDED
#define QUEST_CORE_APPLICATION_H_INCLUDED

#include "Core/QuestCommon.h"

#include <memory>

namespace Quest
{
	/*
	* This is the main class that clients will subclass
	* Setup game specific services in the Init() function
	* Put your update code in the OnTick() function
	* Any ImGui code should go in the OnImGuiRender() function
	**/
	class Application
	{
	public:
		Application();
		virtual ~Application() noexcept;

		//virtual void Init() = 0;
		//virtual void Shutdown() = 0;
		virtual void OnTick() = 0;
		//virtual void OnImGuiRender() = 0;
	};
}

extern std::unique_ptr<Quest::Application> CreateApplication();

#endif // QUEST_CORE_APPLICATION_H_INCLUDED
