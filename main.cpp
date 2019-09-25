#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer.hpp>
#include <boost/program_options.hpp>
#include <bitset>
#include <algorithm>
#include <vector>
#include <numeric>

#include "YOLO_V3/src/Detecting.h"

using namespace cv;
using namespace std;

int main()
{
    YOLOv3::Detecting detector;
    vector<YOLOv3::DetectResult> result;
    namedWindow("src");
    char filename[100];
    for(int i = 1; i<1129; i++)
    {
        sprintf(filename,"/home/leo/Desktop/data/Human2/img/%04d.jpg",i);
        cout<<filename<<endl;
        Mat src = imread(filename);
        detector.Detect(src,result);
        detector.DrawResult(src,result);
        imshow("src",src);
        waitKey(30);
    }
}


