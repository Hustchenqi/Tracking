#!/bin/zsh

DEPLOY=nets/tracker.prototxt
CAFFE_MODEL=nets/tracker.caffemodel

build/tracker $DEPLOY $CAFFE_MODEL 
