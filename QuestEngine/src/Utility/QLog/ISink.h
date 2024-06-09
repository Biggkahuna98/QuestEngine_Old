#pragma once

#include <string_view>
#include "QLogCommon.h"

namespace QLog
{
	enum class SinkType : uint8_t
	{
		ConsoleSink = 0,
		FileSink,
	};

	struct SinkCreateInfo
	{
		SinkType Type;
		std::string Filename;
		bool Truncate;
	};

	class ISink
	{
	public:
		virtual ~ISink() = default;
		
		virtual void Log(const std::string_view msg) = 0;

		void SetLevel(Level newLevel) { m_LogLevel = newLevel; }
		Level GetLevel() const { return m_LogLevel; }
		bool ShouldMessageBeLogged(Level msgLevel) const { return msgLevel >= m_LogLevel; }
	protected:
		Level m_LogLevel{ Level::Trace };
	};

	namespace ISinkFactory
	{
		ISink* CreateSink(SinkCreateInfo ci);
	}
}