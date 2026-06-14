cmake_minimum_required(VERSION 3.28)
project(accelerated_cpp)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/source)

add_subdirectory(source)
