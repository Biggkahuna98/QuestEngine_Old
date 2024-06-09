#pragma once

#include "ISink.h"

namespace QLog
{
	
	class ConsoleSink
	{
	public:
		ConsoleSink();
		~ConsoleSink();

		void Log(const LogPayload payload);
	private:
		//void __Trace(fmt::string_view format, fmt::format_args args);
		void Trace(const std::string msg);
		//void Debug(const std::string msg) override;
		//void Info(const std::string msg) override;
		//void Warn(const std::string msg) override;
		//void Error(const std::string msg) override;
		//void Fatal(const std::string msg) override;
	};
}