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

		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wunused-parameter"
		ISink* CreateConsoleSink(const SinkCreateInfo& ci)
		{
			return new ConsoleSink();
		}
		#pragma clang diagnostic pop

		ISink* CreateFileSink(const SinkCreateInfo& ci)
		{
			return new FileSink(ci.Filename, ci.Truncate);
		}
	}
}