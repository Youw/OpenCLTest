cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

find_package(OpenCL)

add_executable(OpenCLTest OpenCLTest.cpp)
target_link_libraries(OpenCLTest OpenCL::OpenCL)
