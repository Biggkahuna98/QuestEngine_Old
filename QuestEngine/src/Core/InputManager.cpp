#include "QuestCommon.h"

#include "Engine/Engine.h"

// For getting the input state from the glfw window
#include "ThirdParty/GLFW.h"

namespace Quest
{
	InputManager::InputManager(GLFWwindow* window) :
		m_Window(window)
	{
	}

	bool InputManager::IsKeyPressed(KeyCode key)
	{
		auto keyState = glfwGetKey(m_Window, static_cast<uint32>(key));
		return keyState == GLFW_PRESS;
	}

	bool InputManager::IsMouseButtonPressed(MouseCode button)
	{
		auto mouseState = glfwGetMouseButton(m_Window, static_cast<uint32>(button));
		return mouseState == GLFW_PRESS;
	}

	QMath::Vec2 InputManager::GetMousePosition()
	{
		f64 xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);

		return { (f32)xpos, (f32)ypos };
	}

	f32 InputManager::GetMouseX()
	{
		return GetMousePosition().x;
	}

	f32 InputManager::GetMouseY()
	{
		return GetMousePosition().y;
	}
}
