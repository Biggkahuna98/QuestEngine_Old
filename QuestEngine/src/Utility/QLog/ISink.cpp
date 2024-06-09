#include "ISink.h"

#include "ConsoleSink.h"
#include "FileSink.h"

namespace QLog
{
	namespace ISinkFactory
	{
		ISink* CreateConsoleSink(const SinkCreateInfo& ci);
		ISink* CreateFileSink(const SinkCreateInfo& ci);

		ISink* CreateSink(SinkCreateInfo ci)
		{
			switch (ci.Type)
			{
			case SinkType::ConsoleSink: return CreateConsoleSink(ci);
			case SinkType::FileSink: return CreateFileSink(ci);
			}
			
			return nullptr;
		}

		ISink* CreateConsoleSink(const SinkCreateInfo& ci)
		{
			return new ConsoleSink();
		}

		ISink* CreateFileSink(const SinkCreateInfo& ci)
		{
			return nullptr;
		}
	}
}