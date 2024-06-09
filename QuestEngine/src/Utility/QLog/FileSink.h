#pragma once

#include "ISink.h"

#include <string>
#include <fstream>

namespace QLog
{

	class FileSink : public ISink
	{
	public:
		FileSink(const std::string_view fileName, const bool truncate);
		~FileSink();

		void Log(const std::string_view msg);

		void Flush();
	private:
		std::string m_Filename;
		std::ofstream m_File;
	};
}