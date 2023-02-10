cmake_minimum_required(VERSION 3.16)
project(socket-interaction)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(prog_1 src/prog_1/prog_1.h src/prog_1/prog_1.cpp)
target_link_libraries(prog_1 Threads::Threads)
add_executable(prog_2 src/prog_2/prog_2.h src/prog_2/prog_2.cpp)
