#ifndef _H_CTRANSFERFILETASK
#define _H_CTRANSFERFILETASK

#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <CDiaTask.h>
#include <CDiaFileTransport.h>

class CTransferFileTask : public CDiaTask
{
public:
	CTransferFileTask(std::string file_name, size_t nFileSize = -1)
	{
		pFile = new CDiaFile(file_name, nFileSize);
#ifdef _DEBUG
		printf("Sending File Of %d Bytes\n", pFile->GetFileSize());
#endif
	}
	virtual bool IsDone()
	{
		return !((pFile->GetFileSize() > m_nFilePos) && pFile->IsOpen());
	}
	virtual void TaskEnd()
	{
#ifdef _DEBUG
		printf("File Transfer Transmitted %d bytes\n", pFile->TotalBytesRead());
#endif
		return;
	}
	virtual void RunInternal();
private:
	CDiaFile* pFile;
	size_t m_nFilePos = 0;
};


#endif
