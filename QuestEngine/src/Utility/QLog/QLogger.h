#pragma once

#include <string>
#include <vector>

#include "QLogCommon.h"
#include "ISink.h"

namespace QLog
{
	class Logger
	{
	public:
		Logger();
		~Logger();
	private:
		std::string m_LogName;

		std::vector<ISink> m_Sinks;
	};
}