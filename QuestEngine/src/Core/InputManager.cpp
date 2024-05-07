#include "QuestCommon.h"
#include "InputManager.h"

#include "Engine/QuestEngine.h"

// For getting the input state from the glfw window
#include <GLFW/glfw3.h>

namespace Quest
{
	bool InputManager::IsKeyPressed(KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(QuestEngine::Get().GetApplication().GetWindow().GetNativeWindow());
		auto keyState = glfwGetKey(window, static_cast<uint32>(key));
		return keyState == GLFW_PRESS;
	}

	bool InputManager::IsMouseButtonPressed(MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(QuestEngine::Get().GetApplication().GetWindow().GetNativeWindow());
		auto mouseState = glfwGetMouseButton(window, static_cast<uint32>(button));
		return mouseState == GLFW_PRESS;
	}

	QMath::Vec2 InputManager::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(QuestEngine::Get().GetApplication().GetWindow().GetNativeWindow());
		f64 xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

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