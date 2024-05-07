#pragma once

#include <string>

namespace Quest
{
	class Layer
	{
	public:
		Layer(const std::string& name = "QuestLayer") :
			m_DebugName(name)
		{
		}
		virtual ~Layer() = 0;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnTick() = 0;
		virtual void OnImGuiRender() = 0;

		const std::string GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};
}