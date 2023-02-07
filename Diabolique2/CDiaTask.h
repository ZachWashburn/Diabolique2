#ifndef _H_CDIATASK
#define _H_CDIATASK

#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <WindowsImportHide/WindowsImportHide.h>
#include <IDiaboliqueConnection.h>

class CDiaTask
{
public:
	virtual void SetRunTicks(int nTicks)
	{
		m_nTicksBetween = nTicks;
	}

	virtual void Run()
	{
		//WINDOWS_IMPORT_HIDE(GetTickCount64, "kernel32.dll");
		std::chrono::system_clock::time_point a = std::chrono::system_clock::now();

		std::chrono::duration<double, std::milli> work_time = a - m_LastRanPoint;

		if (work_time.count() < (double)m_nTicksBetween)
		{
			return;
		}

		RunInternal();
		m_LastRanPoint = std::chrono::system_clock::now();


#if 0
		if ((m_nTicksBetween == -1) || _GetTickCount64() > (m_nLastRanTick + m_nTicksBetween))
		{
			RunInternal();
			m_nLastRanTick = _GetTickCount64();
		}
#endif
	}


	std::pair<diabolique_message_type_t, std::string> GetTaskData()
	{
		std::lock_guard<std::mutex> _(m_TaskDataLock);
		if (m_TaskData.empty())
			return std::pair<diabolique_message_type_t, std::string>(diabolique_message_type_t::k_dmATAINVALID,"");

		std::pair<diabolique_message_type_t, std::string> Data = m_TaskData.back();
		m_TaskData.pop_back();
		return Data;
	}
	virtual bool IsDone() = 0;
	virtual void TaskEnd() = 0;

protected:
	virtual void RunInternal() = 0;

	//__int64 m_nLastRanTick = 0;
	__int64 m_nTicksBetween = 0;
	std::chrono::system_clock::time_point m_LastRanPoint = std::chrono::system_clock::now();

	std::deque<std::pair<diabolique_message_type_t, std::string>> m_TaskData;
	std::mutex m_TaskDataLock;
};



#endif
