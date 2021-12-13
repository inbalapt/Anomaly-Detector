cmake_minimum_required(VERSION 3.20)
project(as1)

set(CMAKE_CXX_STANDARD 11)

add_executable(as1 anomaly_detection_util.cpp anomaly_detection_util.h
        AnomalyDetector.h MainTrain.cpp
        SimpleAnomalyDetector.h timeseries.cpp timeseries.h SimpleAnomalyDetector.cpp minCircle.h minCircle.cpp)
