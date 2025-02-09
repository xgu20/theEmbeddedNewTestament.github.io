#include "WorkerThread.h"
#include "Fault.h"
#include <iostream>

using namespace std;

#define MSG_EXIT_THREAD 1
#define MSG_POST_USER_DATA 2
#define MSG_TIMER 3

struct ThreadMsg
{
    ThreadMsg(int i, std::shared_ptr<void> m) {id = i; msg = m;}
    int id;
    std::shared_ptr<void> msg;
};

//----------------------------------------------------------------------------
// WorkerThread
//----------------------------------------------------------------------------
WorkerThread::WorkerThread(const char* threadName) : THREAD_NAME(threadName), m_thread(nullptr), m_timerExit(false)
{
}

//----------------------------------------------------------------------------
// ~WorkerThread
//----------------------------------------------------------------------------
WorkerThread::~WorkerThread()
{
    ExitThread();
}

//----------------------------------------------------------------------------
// CreateThread
//----------------------------------------------------------------------------
bool WorkerThread::CreateThread()
{
    if (!m_thread)
        m_thread = std::unique_ptr<std::thread> (new thread(&WorkerThread::Process, this));
    return true;
}

//----------------------------------------------------------------------------
// GetThreadId
//----------------------------------------------------------------------------
std::thread::id WorkerThread::GetThreadId()
{
	ASSERT_TRUE(m_thread != nullptr);
	return m_thread->get_id();
}

//----------------------------------------------------------------------------
// GetCurrentThreadId
//----------------------------------------------------------------------------
std::thread::id WorkerThread::GetCurrentThreadId()
{
	return this_thread::get_id();
}

//----------------------------------------------------------------------------
// ExitThread
//----------------------------------------------------------------------------
void WorkerThread::ExitThread()
{
    if (!m_thread)
        return;
    
    // Create a new ThreadMsg
    std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_EXIT_THREAD, 0));
    
    {
        lock_guard<mutex> lock(m_mutex);
        m_queue.push(threadMsg);
        m_cv.notify_one();
    }

    m_thread->join();
    m_thread = nullptr;
}

//----------------------------------------------------------------------------
// PostMsg
//----------------------------------------------------------------------------
void WorkerThread::PostMsg(std::shared_ptr<UserData> data)
{
    ASSERT_TRUE(m_thread);

    // Create a new ThreadMsg
    std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_POST_USER_DATA, data));

    // Add user data msg to queue and notify worker thread
    std::unique_lock<std::mutex> lk(m_mutex);
    m_queue.push(threadMsg);
    m_cv.notify_one();
}

//----------------------------------------------------------------------------
// TimerThread
//----------------------------------------------------------------------------
void WorkerThread::TimerThread()
{
    while (!m_timerExit)
    {
        std::this_thread::sleep_for(250ms);

        std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_TIMER, 0));

        // Add timer msg to queue and notify worker thread
        std::unique_lock<std::mutex> lk(m_mutex);
        m_queue.push(threadMsg);
        m_cv.notify_one();
    }
}


//----------------------------------------------------------------------------
// Process
//----------------------------------------------------------------------------
void WorkerThread::Process()
{
    m_timerExit = false;
    std::thread timerThread(&WorkerThread::TimerThread, this);

    while (1)
    {
        std::shared_ptr<ThreadMsg> msg;
        {
            // Wait for a message
            std::unique_lock<std::mutex> lk(m_mutex);
            m_cv.wait(lk, [&](){return !m_queue.empty();});

            msg = m_queue.front();
            m_queue.pop();
        }

        switch(msg->id)
        {
            case MSG_POST_USER_DATA:
            {
                ASSERT_TRUE(msg->msg != NULL);
                auto userData = std::static_pointer_cast<UserData>(msg->msg);
                break;
            }
            case MSG_TIMER:
                cout << "Timer expired on " << THREAD_NAME << endl;
            
            case MSG_EXIT_THREAD:
            {
                m_timerExit = true;
                timerThread.join();
                return;
            }

            default:
                ASSERT();
        }
    }
}
