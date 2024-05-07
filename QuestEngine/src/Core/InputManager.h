#pragma once

#include "QuestTypes.h"
#include "InputCodes.h"

#include "Math/QuestMath.h"

struct GLFWwindow;

namespace Quest
{

	class InputManager
	{
	public:
		InputManager(GLFWwindow* window);
		~InputManager() {}

		bool IsKeyPressed(KeyCode key);
		bool IsMouseButtonPressed(MouseCode button);
		QMath::Vec2 GetMousePosition();
		f32 GetMouseX();
		f32 GetMouseY();
	private:
		GLFWwindow* m_Window;
	};
}