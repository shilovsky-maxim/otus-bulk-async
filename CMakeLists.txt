cmake_minimum_required(VERSION 3.9)
project(async)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_library(async SHARED async_cout_printer.cpp
                         async_input_provider.cpp
                         base_block.cpp
                         command.cpp
                         composite_processor.cpp
                         default_block_factory.cpp
                         dynamic_block.cpp
                         file_printer.cpp
                         input_processor.cpp
                         static_block.cpp
                         async.cpp
                         async.h)

add_executable(async_cli main.cpp)

target_link_libraries(async 
                      ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(async_cli async)