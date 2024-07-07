#pragma once

#include <string>

namespace QE
{
	class Subsystem
	{
	public:
		Subsystem(const std::string& name = "QuestSubsystem") :
			m_DebugName(name)
		{
		}
		virtual ~Subsystem() = 0;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void OnTick() = 0;
		virtual void OnImGuiRender() = 0;

		const std::string GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};
}
