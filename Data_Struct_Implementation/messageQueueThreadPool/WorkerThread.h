#ifndef _THREAD_STD_H
#define _THREAD_STD_H

#include <thread>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

struct UserData
{
    std::string msg;
    int year;
};

struct ThreadMsg;

class WorkerThread
{
public:
    /// Constructor
    WorkerThread(const char* threadName);

    /// Destructor
    ~WorkerThread();

    /// Called Once to create the worker thread
    /// @return True if thread is created. False otherwise
    bool CreateThread();

    /// Called once a program exit to exit the worker thread
    void ExitThread();

    /// Get the ID of this thread instance
    /// @return The worker thread ID
    std::thread::id GetThreadId();

    /// Get the ID of the currently executing thread
    /// @return The current thread ID
    static std::thread::id GetCurrentThreadId();

    /// Add a message to the thread queue
    /// @param[in] data - thread specific mesage information
    void PostMsg(std::shared_ptr<UserData> msg);

private:
    WorkerThread(const WorkerThread&) = delete;
    WorkerThread& operator=(const WorkerThread&) = delete;

    /// Entry point for the worker thread
    void Process();

    /// Entry point for timer thread
    void TimerThread();

    std::unique_ptr<std::thread> m_thread;
    std::queue<std::shared_ptr<ThreadMsg>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::atomic<bool> m_timerExit;
    const char* THREAD_NAME;
};

#endif