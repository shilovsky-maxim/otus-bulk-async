cmake_minimum_required(VERSION 3.9)
if(NOT DEFINED ENV{GITHUB_RUN_NUMBER})
    set(ENV{GITHUB_RUN_NUMBER} 1)
endif()

project(async VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

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

if (MSVC)
    target_compile_options(async PRIVAT-E
        /W4
    )
    target_compile_options(async_cli PRIVAT-E
        /W4
    )
else ()
    target_compile_options(async PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(async_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS async RUNTIME DESTINATION lib)
install(TARGETS async_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT max-in-3d@ngs.ru)

include(CPack)