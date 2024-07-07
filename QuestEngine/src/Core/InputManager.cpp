#include "Common.h"

//#include "Engine/Engine.h"
#include "InputManager.h"

// For getting the input state from the glfw window
#include "ThirdParty/GLFW.h"

namespace QE
{
	InputManager::InputManager(GLFWwindow* window) :
		m_Window(window)
	{
	}

	bool InputManager::IsKeyPressed(KeyCode key)
	{
		return m_KeyData.find(key) != m_KeyData.end() && m_KeyData[key].State == KeyState::Pressed;
	}

	bool InputManager::IsKeyHeld(KeyCode key)
	{
		return m_KeyData.find(key) != m_KeyData.end() && m_KeyData[key].State == KeyState::Held;
	}

	bool InputManager::IsKeyDown(KeyCode key)
	{
		auto keyState = glfwGetKey(m_Window, static_cast<uint32>(key));
		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	bool InputManager::IsKeyReleased(KeyCode key)
	{
		return m_KeyData.find(key) != m_KeyData.end() && m_KeyData[key].State == KeyState::Released;
	}

	bool InputManager::IsMouseButtonPressed(MouseCode button)
	{
		return m_MouseData.find(button) != m_MouseData.end() && m_MouseData[button].State == KeyState::Pressed;
	}

	bool InputManager::IsMouseButtonHeld(MouseCode button)
	{
		return m_MouseData.find(button) != m_MouseData.end() && m_MouseData[button].State == KeyState::Held;
	}

	bool InputManager::IsMouseButtonDown(MouseCode button)
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

	void InputManager::ProcessTransitions()
	{
		UpdatePressedKeysToHeld();
		UpdatePressedButtonsToHeld();
	}

	void InputManager::UpdateKeyState(KeyCode key, KeyState newState)
	{
		auto& keyData = m_KeyData[key];
		keyData.OldState = keyData.State;
		keyData.State = newState;
		QE_LOG_TAG(Quest, Debug, Input, "{} is {}", static_cast<char>(key), GetKeyStateString(newState));
	}

	void InputManager::UpdateButtonState(MouseCode mouse, KeyState newState)
	{
		auto& mouseData = m_MouseData[mouse];
		mouseData.OldState = mouseData.State;
		mouseData.State = newState;
		QE_LOG_TAG(Quest, Debug, Input, "{} is {}", static_cast<char>(mouse), GetKeyStateString(newState));
	}

	void InputManager::UpdatePressedKeysToHeld()
	{
		for (const auto& [key, keyData] : m_KeyData)
		{
			if (keyData.State == KeyState::Pressed)
				UpdateKeyState(key, KeyState::Held);
		}
	}

	void InputManager::UpdatePressedButtonsToHeld()
	{
		for (const auto& [button, buttonData] : m_MouseData)
		{
			if (buttonData.State == KeyState::Pressed)
				UpdateButtonState(button, KeyState::Held);
		}
	}

	void InputManager::ClearReleasedKeys()
	{
		for (const auto& [key, keyData] : m_KeyData)
		{
			if (keyData.State == KeyState::Released)
				UpdateKeyState(key, KeyState::None);
		}

		for (const auto& [button, buttonData] : m_MouseData)
		{
			if (buttonData.State == KeyState::Released)
				UpdateButtonState(button, KeyState::None);
		}
	}
}
