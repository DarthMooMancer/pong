cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(pong)

set(SOURCES
	src/main.cpp
	src/engine.cpp
	src/timer.cpp
)
add_executable(pong ${SOURCES})

target_include_directories(pong PRIVATE include)
find_package(Curses REQUIRED)
target_link_libraries(pong PRIVATE ${CURSES_LIBRARIES})
