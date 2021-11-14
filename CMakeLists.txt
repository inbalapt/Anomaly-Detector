cmake_minimum_required(VERSION 3.20)
project(as1)

set(CMAKE_CXX_STANDARD 11)

add_executable(as1 main.cpp anomaly_detection_util.cpp anomaly_detection_util.h anomaly_detection.h AnomalyDetector.h MainTrain.cpp SimpleAnomalyDetector.h anomaly_detection.cpp SimpleAnomalyDetection.cpp SimpleAnomalyDetection.h timeseries.cpp timeseries.h)
