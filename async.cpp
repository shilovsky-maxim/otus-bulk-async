#include "async.h"

#include <memory>
#include <thread>
#include <map>
#include "input_provider.h"
#include "input_processor.h"
#include "default_block_factory.h"
#include "composite_processor.h"
#include "file_printer.h"
#include "async_cout_printer.h"
#include "async_input_provider.h"

namespace async {

using ThreadPtr = std::shared_ptr<std::thread>;
struct ThreadData {
    ThreadPtr m_thread;
    std::shared_ptr<AsyncInputProvider> m_input;
};
using ThreadMap = std::map<handle_t, ThreadData>;

ThreadMap threads;

void worker(std::size_t size, IInputProviderPtr in)
{
    // Create input processor
    auto factory = std::make_shared<DefaultBlockFactory>(size);
    auto printer = std::make_shared<CompositeProcessor>();
    printer->addProcessor(std::make_shared<FilePrinter>());
    printer->addProcessor(std::make_shared<AsyncCoutPrinter>());

    InputProcessor processor(factory, printer);
    processor.processInput(in); // It will work until input provider has input
                                // Because it will wait until destroy or data addition, it will work for entire life of this thread
}

handle_t connect(std::size_t bulk) {
    // Create a thread and return a pointer to it as a handle
    ThreadData thrData;
    thrData.m_input = std::make_shared<AsyncInputProvider>();
    thrData.m_thread = std::make_shared<std::thread>(worker, bulk, thrData.m_input);
    auto handle = static_cast<handle_t>(thrData.m_thread.get());
    threads.emplace(handle, thrData);
    return handle;
}

void receive(handle_t handle, const char *data, std::size_t size) {
    std::string str(data, size);
    auto it = threads.find(handle);
    if (threads.end() == it)
        return;
    it->second.m_input->addData(str);
}

void disconnect(handle_t handle) {
    auto it  = threads.find(handle);
    if (threads.end() == it)
        return;
    // ToDo - add code to finish the process
    if (it->second.m_input)
        it->second.m_input->destroy();

    if (it->second.m_thread && it->second.m_thread->joinable())
        it->second.m_thread->join();
}

}
