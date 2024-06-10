#include "ColoredConsoleSink.h"
#include <iostream>

namespace QLog
{

	ColoredConsoleSink::ColoredConsoleSink()
	{
	}

	ColoredConsoleSink::~ColoredConsoleSink()
	{
	}

	void ColoredConsoleSink::Log(SinkLogPayload payload)
	{
		// Coloring
		switch (payload.level)
		{
		case Level::Trace:	std::cout << ""; break;
		case Level::Debug:	std::cout << "\033[36m"; break;
		case Level::Info:	std::cout << "\033[32m"; break;
		case Level::Warn:	std::cout << "\033[93m"; break;
		case Level::Error:	std::cout << "\033[31m"; break;
		case Level::Fatal:	std::cout << "\033[41;97m"; break;
		default:
			std::cout << "";
		}

		// Print the payload
		std::cout << payload.msg;
		
		// Reset color
		std::cout << "\033[0m\n";
	}
}