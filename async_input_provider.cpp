#include "async_input_provider.h"

AsyncInputProvider::AsyncInputProvider()
{
}

AsyncInputProvider::~AsyncInputProvider()
{
}

bool AsyncInputProvider::getLine(std::string& line)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this] () {return m_hasData || m_eof;});
    auto res = m_hasData && std::getline(m_data, line).good();
    if (!res)
        m_hasData = false;

    if (m_onDestroy && !m_hasData)
        m_cv.notify_all();
    
    return m_hasData || !m_eof;
}

void AsyncInputProvider::addData(const std::string& data)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_data << data;
    m_hasData  = true;
    m_cv.notify_all();
}

void AsyncInputProvider::destroy()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_onDestroy = true;
    // Wait until all data is processed
    m_cv.wait(lock, [this](){ return !m_hasData; });
    m_eof = true;
    m_cv.notify_all();
}
