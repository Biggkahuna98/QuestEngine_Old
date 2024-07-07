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

		const std::string GetName() const { return m_DebugName; }
		const bool IsEnabled() const { return m_Enabled; }

		void SetEnabled(bool enabled) { m_Enabled = enabled; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};
}
