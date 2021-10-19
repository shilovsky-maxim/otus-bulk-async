#include "async_cout_printer.h"

#include <mutex>

static void printBlock(IBlockPtr block, size_t)
{
    if (!block)
        return;
    std::cout << "bulk: ";
    block->printContent(std::cout);
    std::cout << std::endl;
}

class AsyncPrinter final
{
public:
    AsyncPrinter();
    ~AsyncPrinter() = default;

    void process(IBlockPtr block);

private:
    ThreadPool<IBlockPtr> m_pool;
};

std::mutex printerMutex;
static AsyncPrinter& getPrinter()
{
    static AsyncPrinter printer;
    return printer;
}

AsyncPrinter::AsyncPrinter()
: m_pool(1, printBlock)
{
}

void AsyncPrinter::process(IBlockPtr block)
{
    m_pool.addData(block);
}

void AsyncCoutPrinter::process(IBlockPtr block)
{
    // Use global mutex to make sure that only one process access the printer
    // Because printer is asynchronous by itself, it shouldn't take long
    std::unique_lock<std::mutex> lock(printerMutex);
    getPrinter().process(block);
}
