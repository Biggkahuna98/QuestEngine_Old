#ifndef QUEST_CORE_APPLICATION_H_INCLUDED
#define QUEST_CORE_APPLICATION_H_INCLUDED

#include <memory>

namespace Quest
{
	class Application
	{
	public:
		Application();
		virtual ~Application() noexcept;
		Application(const Application& other) = delete; // copy constructor
		Application& operator=(const Application& other) = delete; // copy assignment
		Application(Application&& other) noexcept = delete; // move constructor
		Application& operator=(const Application&& other) noexcept = delete; // move assignment
	private:
	};
}

extern std::unique_ptr<Quest::Application> CreateApplication();

#endif // QUEST_CORE_APPLICATION_H_INCLUDED