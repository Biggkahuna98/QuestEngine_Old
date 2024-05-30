#pragma once

#include <string_view>
#include "QLogCommon.h"

namespace QLog
{
	class ISink
	{
	public:
		virtual ~ISink() = default;
		
		virtual void Log(const std::string msg) = 0;

		void SetLevel(Level newLevel) { m_LogLevel = newLevel; }
		Level GetLevel() const { return m_LogLevel; }
		bool ShouldMessageBeLogged(Level msgLevel) const { return msgLevel >= m_LogLevel; }
	protected:
		Level m_LogLevel{ Level::Trace };

		virtual void Trace(const std::string msg) = 0;
		//virtual void Debug(const std::string msg) = 0;
		//virtual void Info(const std::string msg) = 0;
		//virtual void Warn(const std::string msg) = 0;
		//virtual void Error(const std::string msg) = 0;
		//virtual void Fatal(const std::string msg) = 0;
	};
}