cmake_minimum_required(VERSION 3.9)
project(VideoProcess)

# Importing OpenCV (link it in the end of this file)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(VideoProcess main.cpp)

target_link_libraries(VideoProcess ${OpenCV_LIBS})
