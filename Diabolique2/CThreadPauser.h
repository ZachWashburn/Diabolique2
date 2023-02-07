#ifndef _H_CTHREADPAUSER
#define _H_CTHREADPAUSER

#ifdef _MSC_VER
#pragma once
#endif



#include <mutex>
#include <condition_variable>

class CThreadPauser
{
public:
    CThreadPauser() {}
    CThreadPauser(bool DefaultState) : m_bLocked(DefaultState) {}
    void Check()
    {
        if (m_bLocked)
        {
            printf("waiting!\n");
            std::unique_lock<std::mutex> _lck(m_mtxNotifierLock);
            m_cvCondLock.wait(_lck);
            printf("done!\n");
        }
    }


    void PauseThreads()
    {
        std::lock_guard<std::mutex> _(m_mtxbLockedLock);
        m_bLocked = true;
    }

    void UnPauseThreads()
    {
        std::lock_guard<std::mutex> _(m_mtxbLockedLock);
        if (!m_bLocked)
            return;

        m_bLocked = false;
        m_cvCondLock.notify_all();
    }

    void UnPauseOneThread()
    {
        std::lock_guard<std::mutex> _(m_mtxbLockedLock);
        if (!m_bLocked)
            return;

        m_bLocked = false;
        m_cvCondLock.notify_one();
    }
private:
    std::condition_variable m_cvCondLock;
    std::mutex m_mtxNotifierLock;
    std::atomic<bool> m_bLocked = false;
    std::mutex m_mtxbLockedLock;
};

#endif // _H_CTHREADPAUSER