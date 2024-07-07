#pragma once

#include "QuestTypes.h"
#include "InputCodes.h"

#include "Math/QuestMath.h"

#include <map>

struct GLFWwindow;

namespace QE
{
	struct KeyData
	{
		KeyCode Key;
		KeyState State = KeyState::None;
		KeyState OldState = KeyState::None;
	};

	struct MouseButtonData
	{
		MouseCode Button;
		KeyState State = KeyState::None;
		KeyState OldState = KeyState::None;
	};


	class InputManager
	{
	public:
		InputManager(GLFWwindow* window);
		~InputManager() {}

		bool IsKeyPressed(KeyCode key);
		bool IsKeyHeld(KeyCode key);
		bool IsKeyDown(KeyCode key);
		bool IsKeyReleased(KeyCode key);

		//bool IsKeyPressed(KeyCode key);
		bool IsMouseButtonPressed(MouseCode button);
		bool IsMouseButtonHeld(MouseCode button);
		bool IsMouseButtonDown(MouseCode button);
		QMath::Vec2 GetMousePosition();
		f32 GetMouseX();
		f32 GetMouseY();

		void ProcessTransitions();
		void UpdateKeyState(KeyCode key, KeyState newState);
		void UpdateButtonState(MouseCode mouse, KeyState newState);
		void UpdatePressedKeysToHeld();
		void UpdatePressedButtonsToHeld();
		void ClearReleasedKeys();
	private:
		GLFWwindow* m_Window;

		std::map<KeyCode, KeyData> m_KeyData;
		std::map<MouseCode, MouseButtonData> m_MouseData;
	};
}
