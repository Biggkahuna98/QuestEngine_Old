#pragma once

#include <memory>

namespace Quest
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Test();
	private:
	};
}

extern std::unique_ptr<Quest::Application> CreateApplication();