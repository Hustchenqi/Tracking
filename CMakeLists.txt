CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Tracker)

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
    MESSAGE(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
ENDIF()

FIND_PACKAGE(Boost COMPONENTS system filesystem regex REQUIRED)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")    

FIND_PACKAGE(OpenCV REQUIRED)
MESSAGE("OpenCV version is ${OpenCV_VERSION}")

IF(CUDA_FOUND)
INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
ENDIF()
#########################################################################
FIND_PACKAGE(Caffe REQUIRED)               #specify Caffe_DIR in cmake/findcmake.cmake
INCLUDE_DIRECTORIES(${Caffe_INCLUDE_DIRS})
ADD_DEFINITIONS(${Caffe_DEFINITIONS})      #ex. -DCPU_ONLY
MESSAGE("Caffe directory is ${Caffe_DIR}")
#########################################################################
#FILE(GLOB_RECURSE HDRS ${CMAKE_SOURCE_DIR}/*.h)
FILE(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.*)
ADD_LIBRARY(${PROJECT_NAME} ${SRCS})

SET(GLOG_LIB glog)
SET(BOOST_LIB boost_system)

ADD_EXECUTABLE(tracker src/main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} ${Caffe_LIBRARIES} ${GLOG_LIB} ${BOOST_LIB})
TARGET_LINK_LIBRARIES(tracker ${PROJECT_NAME})


