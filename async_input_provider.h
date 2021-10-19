#pragma once

#include "input_provider.h"
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <atomic>

class AsyncInputProvider final : public IInputProvider
{
public:
    AsyncInputProvider();
    virtual ~AsyncInputProvider() override;

    bool getLine(std::string& line) override;
    void addData(const std::string& data);
    void destroy();

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::stringstream m_data;
    std::atomic<bool> m_eof{false};
    std::atomic<bool> m_onDestroy{false};
    std::atomic<bool> m_hasData{false};
};
