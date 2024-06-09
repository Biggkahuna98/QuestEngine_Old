#include "FileSink.h"

namespace QLog
{
	FileSink::FileSink(const std::string_view fileName, const bool truncate)
		: m_Filename(fileName)
	{
		if (truncate)
			m_File = std::ofstream(fileName.data(), std::ios::out, std::ios::trunc);
		else
			m_File = std::ofstream(fileName.data(), std::ios::out);

		if (!m_File)
		{
			std::throw_with_nested(std::runtime_error("File could not be opened"));
		}
	}

	FileSink::~FileSink()
	{
	}

	void FileSink::Log(const std::string_view msg)
	{
		m_File << msg << "\n";
	}

	void FileSink::Flush()
	{
		m_File.flush();
	}
}