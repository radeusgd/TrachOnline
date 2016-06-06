cmake_minimum_required(VERSION 2.6)
project(TrachOnline)

include_directories("${PROJECT_SOURCE_DIR}/../seasocks/src/main/c/")
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "-g -std=c++11 ${CMAKE_CXX_FLAGS} -pthread")

file(GLOB SOURCES
         "*.hpp"
         "*.cpp"
         "cards/*.cpp"
         "cards/*.hpp"
         )

# Define sources and executable
set(EXECUTABLE_NAME "trachserver")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

#link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(${EXECUTABLE_NAME} "${PROJECT_SOURCE_DIR}/lib/libseasocks.so")
