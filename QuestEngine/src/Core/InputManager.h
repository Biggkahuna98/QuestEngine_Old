#pragma once

#include "QuestTypes.h"
#include "InputCodes.h"

#include "Math/QuestMath.h"

namespace Quest
{
	class InputManager
	{
	public:
		bool IsKeyPressed(KeyCode key);
		bool IsMouseButtonPressed(MouseCode button);
		QMath::Vec2 GetMousePosition();
		f32 GetMouseX();
		f32 GetMouseY();
	};
}