#include <iostream>
#include <stdio.h>
#include <queue>
//#include <thread>
//#include <chrono>
#include <opencv2/opencv.hpp>
#include "headall.h"

using namespace std;
using namespace cv;

Point point1, point2; /* vertical points of the bounding box */
int drag = 0;
Rect rect; /* bounding box */
Mat img; /* roiImg - the part of the image in the bounding box */
const bool show_intermediate_output = false;
int select_flag = 0;

void mouseHandler(int event, int x, int y, int flags, void* param)
{
    if (event == CV_EVENT_LBUTTONDOWN && !drag)
    {
        /* left button clicked. ROI selection begins */
        point1 = Point(x, y);
        drag = 1;
    }

    if (event == CV_EVENT_MOUSEMOVE && drag)
    {
        /* mouse dragged. ROI being selected */
        Mat img1 = img.clone();
        point2 = Point(x, y);
        rectangle(img1, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);
        imshow("image", img1);
    }

    if (event == CV_EVENT_LBUTTONUP && drag)
    {
        point2 = Point(x, y);
        rect = Rect(point1.x,point1.y,x-point1.x,y-point1.y);
//        roiImg = img(rect);
        drag = 0;
        printf("LeftTop:(%d, %d),RightDown:(%d, %d)\n",point1.x,point1.y,point2.x,point2.y);
    }

    if (event == CV_EVENT_LBUTTONUP)
    {
       /* ROI selected */
        select_flag = 1;
        drag = 0;
    }
}

int main(int argc, char *argv[])
{
    char key = ' ';
    bool stop = false;
    VideoCapture cap(CV_CAP_OPENNI);/* Start webcam */
    if(!cap.isOpened())
    {
        cerr << "Can not open kinect!"<<endl;
        return -1;
    }
    const string& model_file = argv[1];
    //"/home/cvlab/Chenqi/nets/tracker.prototxt";
    const string& trained_file =argv[2];
    //"/home/cvlab/Chenqi/nets/tracker.caffemodel";

    int gpu_id = 0;
    const bool do_train = false;
    Regressor regressor(model_file, trained_file,gpu_id, do_train);
    Tracker tracker(show_intermediate_output);

    //***********Select Tracking Target*******************************
    while(1)
    {
        cap.grab();
        cap.retrieve(img,CV_CAP_OPENNI_BGR_IMAGE);
        if(!select_flag)
        {
            cvSetMouseCallback("image", mouseHandler, NULL);
            rectangle(img, rect, CV_RGB(255, 0, 0), 3, 8, 0);
        }
        //mouse event cancel, finish choosing target
        else
        {
            cvSetMouseCallback("image", NULL, NULL);
            break;
        }
        imshow("image", img);
        key = waitKey(10);
    }
    destroyWindow("image");
    //****************Start Tracking Target****************************
    Mat image_curr = img.clone();
    BoundingBox bbox_gt(point1, point2);
    //Initialize the tracker.
    tracker.Init(image_curr, bbox_gt, &regressor);
    while(!stop)
    {
        cap.grab();
        cap.retrieve(img,CV_CAP_OPENNI_BGR_IMAGE);
        Mat image_curr = img.clone();

        //Get ready to track the object

        BoundingBox bbox_estimate_uncentered;
        tracker.Track(image_curr, &regressor, &bbox_estimate_uncentered);

        ProcessTrackingOutPut(image_curr,bbox_estimate_uncentered);
        //imshow("image", img);
        key = waitKey(30);
        switch(key)
        {
        case 'q':
        case 'Q':
        case 27:   // 'ESC'
            stop = true;
            break;
        default:
            break;
        }
    }
    return 0;
}
