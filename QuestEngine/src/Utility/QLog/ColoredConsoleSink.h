#pragma once

#include "ISink.h"

namespace QLog
{

	class ColoredConsoleSink : public ISink
	{
	public:
		ColoredConsoleSink();
		~ColoredConsoleSink();

		void Log(SinkLogPayload payload);
	};
}