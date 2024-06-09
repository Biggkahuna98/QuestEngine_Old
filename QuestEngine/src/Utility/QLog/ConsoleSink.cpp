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

	void ConsoleSink::Log(const std::string_view msg)
	{
		std::cout << msg << "\n";
	}
}