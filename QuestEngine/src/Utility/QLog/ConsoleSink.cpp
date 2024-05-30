#include "ConsoleSink.h"
#include "ThirdParty/fmt.h"

namespace QLog
{

	ConsoleSink::ConsoleSink()
	{
	}

	ConsoleSink::~ConsoleSink()
	{
	}

	void ConsoleSink::Log(const LogPayload payload)
	{
		switch (payload.log_level)
		{
		case Level::Off: break;
		case Level::Trace: __Trace(payload.format_str, payload.format_args); break;
		//case Level::Debug: Debug(msg); break;
		//case Level::Info: Info(msg); break;
		//case Level::Warn: Warn(msg); break;
		//case Level::Error: Error(msg); break;
		//case Level::Fatal: Fatal(msg); break;
		}
	}

	void ConsoleSink::__Trace(fmt::string_view format, fmt::format_args args)
	{
		fmt::vprint(format, args);
	}
	void ConsoleSink::Trace(const std::string msg)
	{
		
	}
	/*
	void ConsoleSink::Debug(const std::string msg)
	{
		fmt::print("{}", fmt::format("[TRACE]: {0}\n", msg));
	}

	void ConsoleSink::Info(const std::string msg)
	{
		fmt::print("{}", fmt::format("[TRACE]: {0}\n", msg));
	}

	void ConsoleSink::Warn(const std::string msg)
	{
		fmt::print("{}", fmt::format("[TRACE]: {0}\n", msg));
	}

	void ConsoleSink::Error(const std::string msg)
	{
		fmt::print("{}", fmt::format("[TRACE]: {0}\n", msg));
	}

	void ConsoleSink::Fatal(const std::string msg)
	{
		fmt::print("{}", fmt::format("[TRACE]: {0}\n", msg));
	}*/
}