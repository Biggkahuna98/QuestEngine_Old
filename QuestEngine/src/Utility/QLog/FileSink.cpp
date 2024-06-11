#include "FileSink.h"

#include <filesystem>

namespace QLog
{
	void CreateLogsDirectory()
	{
		if (!std::filesystem::exists("logs"))
			std::filesystem::create_directory("logs");
	}

	FileSink::FileSink(const std::string_view fileName, const bool truncate)
	{
		CreateLogsDirectory();

		m_Filename = fileName;
		//m_File.open(m_Filename);
		if (truncate)
			m_File.open(m_Filename, std::ofstream::trunc);
		else
			m_File.open(m_Filename, std::ofstream::app);

		if (!m_File.is_open())
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
		Flush();
	}

	void FileSink::Flush()
	{
		m_File.flush();
	}
}