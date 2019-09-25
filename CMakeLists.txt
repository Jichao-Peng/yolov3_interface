cmake_minimum_required(VERSION 3.14)
project(slic)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${EIGEN_INCLUDE_DIRS}
        /opt/ros/crystal/include/cv_bridge
        ${PROJECT_SOURCE_DIR}/YOLO_V3/include)

set(CMAKE_CXX_STANDARD 14)

add_executable(slic
        main.cpp
        YOLO_V3/src/Detecting.cpp
        YOLO_V3/src/Detecting.h
        YOLO_V3/src/DetectResult.h)

target_link_libraries(slic
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        /opt/ros/crystal/lib/libcv_bridge.so
        ${PROJECT_SOURCE_DIR}/YOLO_V3/lib/libdarknet.so)