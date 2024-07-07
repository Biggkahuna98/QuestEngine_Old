#pragma once

#include "Subsystem.h"

namespace QE
{
	class TickableSubsystem : public Subsystem
	{
	public:
		TickableSubsystem() = default;
		virtual ~TickableSubsystem() = 0;

		virtual void OnTick() = 0;
		virtual void OnImGuiRender() = 0;
	};
}