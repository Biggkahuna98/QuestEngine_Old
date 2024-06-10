#include "ISink.h"

#include "ConsoleSink.h"
#include "ColoredConsoleSink.h"
#include "FileSink.h"

namespace QLog
{
	namespace ISinkFactory
	{
		ISink* CreateConsoleSink();
		ISink* CreateColoredConsoleSink();
		ISink* CreateFileSink(const SinkCreateInfo& ci);

		ISink* CreateSink(SinkCreateInfo ci)
		{
			switch (ci.Type)
			{
			case SinkType::ConsoleSink: return CreateConsoleSink();
			case SinkType::ColoredConsoleSink: return CreateColoredConsoleSink();
			case SinkType::FileSink: return CreateFileSink(ci);
			}
			
			return nullptr;
		}

		ISink* CreateConsoleSink()
		{
			return new ConsoleSink();
		}

		ISink* CreateColoredConsoleSink()
		{
			return new ColoredConsoleSink();
		}

		ISink* CreateFileSink(const SinkCreateInfo& ci)
		{
			return new FileSink(ci.Filename, ci.Truncate);
		}
	}
}