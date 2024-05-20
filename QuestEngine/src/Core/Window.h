#ifndef QUEST_CORE_WINDOW_H_INCLUDED
#define QUEST_CORE_WINDOW_H_INCLUDED

#include "QuestCommon.h"

struct GLFWwindow;

namespace Quest
{
	class Window
	{
	public:
		struct CreateInfo
		{
			std::string Title{ "Quest Engine" };
			uint32 Width{ 1920 };
			uint32 Height{ 1080 };
		};

		Window(Window::CreateInfo ci);
		~Window();

		const std::string GetTitle() const;
		uint32 GetWidth() const;
		uint32 GetHeight() const;
		GLFWwindow* GetNativeWindow();

		void ProcessEvents();
		void SwapBuffers();
		void PauseWindow();
	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string m_Title;
			uint32 m_Width;
			uint32 m_Height;
			bool m_VSync;
		};

		WindowData m_WindowData;
	};
}

#endif // QUEST_CORE_WINDOW_H_INCLUDED
