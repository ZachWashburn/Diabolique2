#ifndef _H_CSIMPLETHREADPOOL
#define _H_CSIMPLETHREADPOOL


#ifdef _MSC_VER
#pragma once
#endif


#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <semaphore>
#include <chrono>

template<class T>
class CSimpleThreadSafeQueue
{
public:
	void push(T val)
	{
		std::lock_guard<std::mutex> _(m_QueueLock);
		m_Queue.push(val);
	}

	T pop()
	{
		std::lock_guard<std::mutex> _(m_QueueLock);
		T ret = m_Queue.front();
		m_Queue.pop();
		return ret;
	}

	bool empty()
	{
		std::lock_guard<std::mutex> _(m_QueueLock);
		return m_Queue.empty();
	}

private:
	std::mutex m_QueueLock;
	std::queue<T> m_Queue;
};

#if 0 // will this work? it might. Not in use for now
struct thread_job_t
{
	thread_job_t(std::function<void()> func)
	{
		m_Work = new std::function<void()>;
		*m_Work = func;
		m_Sema = new std::binary_semaphore(1);
		m_Sema->acquire();
		m_Ran = new std::atomic<bool>;
		*m_Ran = false;
	}

	~thread_job_t()
	{
		if (*m_Ran)
		{
			delete m_Work;
			delete m_Sema;
			delete m_Ran;
		}
	}
	void operator()()
	{
		(*m_Work)();
		m_Sema->release();
	}

	bool join()
	{
		m_Sema->acquire();
	}

	std::function<void()>* m_Work;
	std::binary_semaphore* m_Sema;
	std::atomic<bool>* m_Ran;
};
#endif

template<int Count = 8>
class CSimpleThreadPool
{
public:

	// todo : finish watchdog implementation!!!!
	struct threaded_job_t
	{
		threaded_job_t(std::function<void()> work)
		{
			m_Work = work;
		}
		std::function<void()> m_Work;
		std::chrono::seconds m_WatchDogTimeOut = 0;
	};

	CSimpleThreadPool()
	{
		m_pSemaphore = new std::counting_semaphore<Count>(0);

		m_nThreadCount = Count;

		for (int i = 0; i < Count; i++)
			m_Threads.at(i) = new std::thread(&CSimpleThreadPool::thread_worker, this);

	}

	~CSimpleThreadPool()
	{
		m_bKill = true;

		for(int i = 0; i < Count; i++)
			m_pSemaphore->release();

		for (const auto& thread : m_Threads)
		{
			thread->join();
			delete thread;
		}

		delete m_pSemaphore;

	}

	template<typename F, typename... Args>
	void submit(F f, Args&&... args) {
		m_WorkQueue.push(std::bind(f, std::forward<Args>(args)...));
		m_pSemaphore->release();
	}

	// expermental, dangerous, and may lead to S E R I O U S memory leaks
	void force_reset_all();

protected:

	void thread_worker()
	{
		while (true)
		{
			m_pSemaphore->acquire();

			if (m_bKill)
				return;

			std::function<void()> work = m_WorkQueue.pop();

			work();
		}
	}

#if 0
	template<typename F, typename... Args>
	void submit2(F f, Args&&... args) {
		m_WorkQueue.push_back([f, args...]{ f->Func(args); });
	}
#endif

private:
	int m_nThreadCount = 0;

	std::atomic<bool> m_bKill = false;
	
	std::counting_semaphore<Count>* m_pSemaphore;

	CSimpleThreadSafeQueue<std::function<void()>> m_WorkQueue;
	std::array<std::thread*, Count> m_Threads;
};




#endif
