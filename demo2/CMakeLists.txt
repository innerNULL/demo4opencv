# 2020-09-22


cmake_minimum_required(VERSION 3.0)
project(demo2)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4.0.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR}) 
link_directories(${OpenCV_LIB_DIR}) 

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
