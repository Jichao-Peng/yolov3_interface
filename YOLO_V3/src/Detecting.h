//
// Created by leo on 18-11-13.
//

#ifndef PROJECT_DETECTING_H
#define PROJECT_DETECTING_H

#include <string>
#include <darknet.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <condition_variable>
#include "DetectResult.h"

using namespace std;
using namespace cv;
namespace YOLOv3
{
    class TransMethod;

    class Detecting
    {
    public:
        Detecting();

        void Detect(cv::Mat Frame, vector<DetectResult>& vDetectResults);

        void DrawResult( cv::Mat &Image, vector<DetectResult> Result);


    private:
        network *mpNetwork;
        metadata mData;

        TransMethod *mpTransMethod;
    };


    class TransMethod
    {
    public:
        image MattoImage(cv::Mat m)
        {
            IplImage ipl = m;
            image im = IpltoImage(&ipl);
            rgbgr_image(im);
            return im;
        }

    private:
        image IpltoImage(IplImage *src)
        {
            int h = src->height;
            int w = src->width;
            int c = src->nChannels;
            image im = make_image(w, h, c);
            unsigned char *data = (unsigned char *) src->imageData;
            int step = src->widthStep;
            int i, j, k;

            for (i = 0; i < h; ++i)
            {
                for (k = 0; k < c; ++k)
                {
                    for (j = 0; j < w; ++j)
                    {
                        im.data[k * w * h + i * w + j] = data[i * step + j * c + k] / 255.;
                    }
                }
            }
            return im;
        }
    };
}
#endif //PROJECT_DETECTING_H
