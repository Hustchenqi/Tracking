# Caffe package
UNSET(Caffe_FOUND)

###Set the variable Caffe_DIR as the root of your caffe directory
#set(Caffe_DIR /*Specify path to caffe here*/)

SET(Caffe_DIR /home/cvlab/caffe-master)

FIND_PATH(Caffe_INCLUDE_DIRS NAMES caffe/caffe.hpp caffe/common.hpp caffe/net.hpp caffe/proto/caffe.pb.h caffe/util/io.hpp caffe/layers/*.hpp HINTS ${Caffe_DIR}/include)

FIND_LIBRARY(Caffe_LIBRARIES NAMES caffe HINTS ${Caffe_DIR}/build/lib)

MESSAGE("lib_dirs: ${Caffe_LIBRARIES}")

IF(Caffe_LIBRARIES AND Caffe_INCLUDE_DIRS)
    SET(Caffe_FOUND 1)
ENDIF()
