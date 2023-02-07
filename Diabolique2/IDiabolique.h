#ifndef _H_IDIABOLIQUE
#define _H_IDIABOLIQUE

#ifdef _MSC_VER
#pragma once
#endif

#include <IDiaboliqueConnection.h>
#include <CDiaTask.h>
#include <CDiaFileTransport.h>

#define FILESEGMENTSIZE (4096*10)

class IDiabolique : public IDiaboliqueConnection
{
public:
	IDiabolique()
	{
		if (!m_RunTasksThread)
			m_RunTasksThread = new std::thread(&IDiabolique::_INTRNL_RunTasks, this);
	}

	~IDiabolique()
	{
		m_bKill = true;

		if (!m_RunTasksThread)
			m_RunTasksThread->join();
	}

	bool ShouldExitProcess()
	{
		return false;
	}

protected:



	virtual void _INTRNL_HandleMessage(diabolique_message_type_t nType, void* pData, size_t nDataSize);
	virtual void _INTRNL_GetFetchDataForSend(diabolique_message_type_t& nType, void* pBuffer, size_t nBufferSize, size_t& nDataRecieved);
	virtual void _INTRNL_RunTasks();

	virtual int AddTask(CDiaTask* pTask)
	{
		std::lock_guard<std::mutex> _(m_TaskLock);
		unsigned int i = 1;

		for (auto it = m_Tasks.cbegin(), end = m_Tasks.cend();
			it != end && i == it->first; ++it, ++i)
		{
		}

		m_Tasks[i] = pTask;
		return i;
	}

	// main bus for all module chatter 
	std::thread* m_RunTasksThread = nullptr;;
	IDiaboliqueIO m_IO;
	std::map<int, CDiaTask*> m_Tasks;
	int m_nCurrentTaskCount = 0;
	std::atomic<bool> m_bKill = false;
	std::mutex m_TaskLock;

	CDiaFileTransport m_FileTransport;
};

#endif