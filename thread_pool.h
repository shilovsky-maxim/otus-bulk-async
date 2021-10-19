#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <atomic>

template<class Data> 
class ThreadPool
{
public:
    using Processor = std::function<void(Data, size_t threadIndex)>;
public:
    ThreadPool(size_t size, Processor processor)
    : m_processor(processor)
    {
        using namespace std::placeholders;
        for (size_t i = 0; i < size; ++i)
            m_threads.emplace_back(std::bind(&ThreadPool::process, this, _1), i);
    }

    virtual ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_onDestroy = true;
            m_condition.wait(lock, [this]() { return m_queue.empty(); });
            m_stop = true;
            m_condition.notify_all();
        }

        for (auto& thrd : m_threads)
            thrd.join();
    }

    void addData(Data data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_condition.notify_one();
    }

private:
    void process(size_t threadIndex)
    {
        Data data;
        while (!m_stop)
        {
            {
                std::unique_lock<std::mutex>lock(m_mutex);
                m_condition.wait(lock, [this]() {return m_stop || !m_queue.empty();});
                if (m_stop)
                    break;
                data = m_queue.front();
                m_queue.pop();
                if (m_onDestroy && m_queue.empty())
                    m_condition.notify_all();
            }
            m_processor(data, threadIndex);
        }
    }

    std::queue<Data> m_queue;
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    Processor m_processor;
    std::atomic<bool> m_onDestroy{false};
    std::atomic<bool> m_stop{false};
};
