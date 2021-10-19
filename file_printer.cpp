#include "file_printer.h"

#include <sstream>
#include <ctime>
#include <fstream>
#include <atomic>

void FilePrinter::process(const IBlockPtr block)
{
    if (!block)
        return;
    static std::atomic<unsigned int> counter{0u};
    // Get the current timestamp
    std::stringstream fileName;
    ++counter; 
    fileName << "bulk" << std::time(nullptr) << "_" << counter << ".log";
    std::ofstream file;
    file.open(fileName.str());
    block->printContent(file);
    file << std::endl;
    file.close();
}
