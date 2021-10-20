cmake_minimum_required(VERSION 3.20)
project(as1)

set(CMAKE_CXX_STANDARD 11)

add_executable(as1 main.cpp anomaly_detection_util.cpp anomaly_detection_util.h)
