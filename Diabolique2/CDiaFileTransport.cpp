#include <BaseIncludes.h>
#include <CDiaFileTransport.h>
#include <filesystem>

CDiaFile::CDiaFile(std::string file_path, size_t nFileSize)
{
	m_filename = file_path;
	m_pFile = new std::fstream(file_path.c_str(), std::ios::out | std::ios::in | std::ios::binary);

	if (!m_pFile->is_open())
	{
		delete m_pFile;
		std::ofstream outfile(file_path);
		outfile.close();

		m_pFile = new std::fstream(file_path.c_str(), std::ios::out | std::ios::in | std::ios::binary);

		if (!m_pFile->is_open())
		{
			m_nFileSize = 0;
			return;
		}
	}

	// shitty fucking way to do this but std:: doesn't provide a good method
	m_pFile->seekg(0, std::ios::end);
	size_t nCurFileSize = m_pFile->tellg();
	m_pFile->seekg(0, std::ios::beg);

	if (nCurFileSize >= nFileSize)
	{
		m_pFile->close();
		std::filesystem::remove(file_path);

		delete m_pFile;
		std::ofstream outfile(file_path);
		outfile.close();
		m_pFile = new std::fstream(file_path.c_str(), std::ios::out | std::ios::in | std::ios::binary);
		nCurFileSize = 0;
		if (!m_pFile->is_open())
		{
			m_nFileSize = 0;
			return;
		}
	}

	if (nFileSize != 0xFFFFFFFF)
	{
		__int64 data = 0;
		for (size_t i = nCurFileSize; i < nFileSize;)
		{
			int nBytesToWrite = min(nFileSize - i, sizeof(__int64));
			m_pFile->write((const char*)&data, nBytesToWrite);
			i += nBytesToWrite;
		}
	}
	// now we have a huge 0 file


	m_pFile->seekg(0, std::ios::end);
	m_nFileSize = m_pFile->tellg();
	m_pFile->seekg(0, std::ios::beg);

	m_pFile->seekg(0, std::ios::beg);
	m_pFile->seekp(0, std::ios::beg);
}


void CDiaFile::WriteFile(std::string data, size_t nDataOffset)
{
	std::lock_guard<std::mutex> _(m_mtxFileLock);

	if(!(nDataOffset == 0xFFFFFFFF))
		m_pFile->seekp(nDataOffset, std::ios::beg);

	m_pFile->write(data.data(), data.size());

	size_t nDataPos = m_pFile->tellg();
	m_pFile->seekp(0, std::ios::end);
	int nPLoc = m_pFile->tellp();

	if(nPLoc > m_nFileSize)
		m_nFileSize = m_pFile->tellp();

	m_pFile->seekp(0, std::ios::beg);

	m_pFile->seekp(nDataPos, std::ios::beg);

	m_pFile->flush();

	nTotalBytesWrote += data.size();
}

std::string CDiaFile::ReadFile(size_t nDataSize, size_t* pnDataRead, size_t nDataOffset )
{
	std::lock_guard<std::mutex> _(m_mtxFileLock);

	if (!(nDataOffset == 0xFFFFFFFF))
		m_pFile->seekg(nDataOffset, std::ios::beg);

	size_t nReadSize = min(min(m_nFileSize - m_pFile->tellg(), nDataSize), m_nFileSize);

	if(pnDataRead)
		*pnDataRead = nReadSize;

	std::string data(nReadSize, ' ');
	nTotalBytesRead += nReadSize;

	m_pFile->read(data.data(),
		nReadSize
	);

	return data;
}




void CDiaFileTransport::HandleFileMessage(file_transfer_segment seg, std::string path)
{
	if (m_Files.find(seg.name()) == m_Files.end())
	{
		try {
			std::filesystem::create_directories(path);
		}
		catch (std::exception& e)
		{

		}

		// just make sure no one can path traverse on us...
		std::string file_name = std::filesystem::path::path(seg.name()).filename().string();
#if defined(SERVER) || defined(SERVER_CLIENT) || defined(_DEBUG)		
		printf("Recieving File %s (%d Bytes)\n", file_name.c_str(), seg.file_size());
#endif
		
		m_Files[seg.name()] = new CDiaFile(path + file_name, seg.file_size());
	}


	CDiaFile* pFile = m_Files[seg.name()];

	if (!pFile)
		return;
#if defined(SERVER) || defined(SERVER_CLIENT) || defined(_DEBUG)
	printf("File Segment Recieved %s [%d bytes @ pos %d] (%d bytes / %d Bytes)\n", std::filesystem::path::path(pFile->GetFileName()).filename().string().c_str(), seg.data().size(), seg.pos(), pFile->TotalBytesWrote(), pFile->GetFileSize());
#endif
	pFile->WriteFile(seg.data(), seg.pos());

	if (pFile->GetFileSize() <= pFile->TotalBytesWrote())
	{
#if defined(SERVER) || defined(SERVER_CLIENT) || defined(_DEBUG)
		printf("File Recieved %s (%d bytes / %d Bytes)\n", pFile->GetFileName().c_str(), pFile->TotalBytesWrote(), pFile->GetFileSize());
#endif
		delete pFile;
		m_Files.erase(seg.name());
	}
}



