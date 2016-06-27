cmake_minimum_required(VERSION 2.8)
project(qrcode)


option(DEBUG_SVG "SVG debugging" Off )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(zbar)

FIND_PACKAGE(OpenCV)

if(OpenCV_FOUND)
    include_directories(SYSTEM ${OpenCV_INCLUDE_DIR})
endif(OpenCV_FOUND)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCE_FILES main.cpp)
add_executable(qrcode ${SOURCE_FILES})

target_link_libraries(qrcode ${OpenCV_LIBS} zbar)