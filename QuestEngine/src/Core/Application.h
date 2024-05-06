#ifndef QUEST_CORE_APPLICATION_H_INCLUDED
#define QUEST_CORE_APPLICATION_H_INCLUDED

#include "QuestCommon.h"

#include <memory>

#include "Window.h"

namespace Quest
{
	class Application
	{
	public:
		Application();
		virtual ~Application() noexcept;

		void Run();
	private:
		ScopedPtr<Window> m_Window;
	};
}

extern std::unique_ptr<Quest::Application> CreateApplication();

#endif // QUEST_CORE_APPLICATION_H_INCLUDED