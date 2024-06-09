#pragma once

#include "ISink.h"

namespace QLog
{
	
	class ConsoleSink : public ISink
	{
	public:
		ConsoleSink();
		~ConsoleSink();

		void Log(const std::string_view msg);
	};
}