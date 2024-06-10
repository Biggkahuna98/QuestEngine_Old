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
		m_File.close();
	}

	void FileSink::Log(SinkLogPayload payload)
	{
		m_File << payload.msg << "\n";
	}

	void FileSink::Flush()
	{
		m_File.flush();
	}
}