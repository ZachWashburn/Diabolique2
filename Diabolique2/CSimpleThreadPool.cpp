
#include <BaseIncludes.h>

template<int Count>
void CSimpleThreadPool<Count>::force_reset_all()
{
	WINDOWS_IMPORT_HIDE(TerminateThread, "kernel32.dll");

	for (const auto& thread : m_Threads)
	{
		_TerminateThread(thread->native_handle(), 0);
		thread->join();
		delete thread;
	}

	m_Threads.clear();
	delete m_pSemaphore;

	m_pSemaphore = new std::counting_semaphore<Count>(0);

	for (int i = 0; i < Count; i++)
		m_Threads.at(i) = new std::thread(&CSimpleThreadPool::thread_worker, this);

}
