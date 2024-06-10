#include "ConsoleSink.h"
#include <iostream>

namespace QLog
{

	ConsoleSink::ConsoleSink()
	{
	}

	ConsoleSink::~ConsoleSink()
	{
	}

	void ConsoleSink::Log(SinkLogPayload payload)
	{
		std::cout << payload.msg << "\n";
	}
}