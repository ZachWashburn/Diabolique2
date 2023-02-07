#ifndef _H_CDIAFILETRANSPORT
#define _H_CDIAFILETRANSPORT

#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <fstream>

class CDiaFile
{
public:
	CDiaFile(std::string file_path, size_t nFileSize);
	~CDiaFile()
	{
		if (m_pFile)
			m_pFile->close();
		delete m_pFile;
	}
	void WriteFile(std::string data, size_t nDataOffset = 0xFFFFFFFF);
	std::string ReadFile(size_t nDataSize, size_t* pnDataRead = nullptr, size_t nDataOffset = 0xFFFFFFFF);

	int TotalBytesWrote()
	{
		return nTotalBytesWrote;
	}

	int TotalBytesRead()
	{
		return nTotalBytesRead;
	}

	bool DoneRead()
	{
		return m_pFile->peek() == EOF;
	}

	bool IsOpen()
	{
		// nasty code for debugging
		if (m_pFile->is_open())
			return true;

		return false;
	}
	size_t GetFileSize()
	{
		return m_nFileSize;
	}

	std::string GetFileName()
	{
		return m_filename;
	}
private:
	std::fstream* m_pFile;
	std::mutex m_mtxFileLock;
	size_t m_nFileSize = 0;
	size_t nTotalBytesWrote = 0;
	size_t nTotalBytesRead = 0;
	std::string m_filename;
};

class CDiaFileTransport
{
public:
	void HandleFileMessage(file_transfer_segment seg, std::string path);
private:
	std::map<std::string, CDiaFile*> m_Files;
};





#endif
