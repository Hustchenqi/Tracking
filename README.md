# Tracking
The project is rectified from <a href="https://github.com/davheld/GOTURN">GOTURN Project</a>.  
The camera we used is Kinect1, any webcam can be used and you just need to modify the `main.cpp`.

##Dependencies
<ul>
<li>OpenCV</li>
<li>Caffe</li>
<li>Cmake</li>
</ul>
##Caffemodel
tracker.caffemodel can be 
<a href=http://cs.stanford.edu/people/davheld/public/GOTURN/trained_model/tracker.caffemodel>Download</a>  
tracker.prototxt has existed in nets folder
##Compile
clean the build folder,and then
```javascript
mkdir build
cd build
cmake ..
make
cd ..
sh run.sh
```
##Problem coming across
<ol>
<li>cannot find #include "caffe/proto/caffe.pb.h"</li>
<p>In the Caffe install directory</p>
```javascript
protoc src/caffe/proto/caffe.proto --cpp_out=.
mkdir include/caffe/proto
mv src/caffe/proto/caffe.pb.h include/caffe/proto
```
<li>error while loading shared libraries: libcaffe.so.1.0.0-rc3: cannot open shared object file: No such file or directory</li>
<p>Solution</p>

<code>sudo gedit /etc/ld.so.conf.d/caffe.conf</code>  
copy the path of libcaffe.so to caffe.conf, in my computer it is
<code>/home/cvlab/caffe-master/build/lib</code>
<p>then</p> 
<code>sudo ldconfig</code>
