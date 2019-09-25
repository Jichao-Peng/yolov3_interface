//
// Created by leo on 18-11-13.
//

#include "Detecting.h"

namespace YOLOv3
{
    Detecting::Detecting()
    {
        string ConfigPath = "../YOLO_V3/config/yolov3.cfg";
        string WeightsPath = "../YOLO_V3/config/yolov3.weights";
        string MetaDataPath = "../YOLO_V3/config/coco.data";

        mpNetwork = load_network((char *) ConfigPath.data(), (char *) WeightsPath.data(), 0);
        mData = get_metadata((char *) MetaDataPath.data());
        mpTransMethod = new TransMethod;
    }

    void Detecting::Detect(cv::Mat Frame, vector<DetectResult>& vDetectResults)
    {
        vDetectResults.clear();
        image Image = mpTransMethod->MattoImage(Frame);//讲Mat数据转成Image类型

        //下面的检测过程是仿照python接口写的，还没有太弄明白是怎么回事,具体可能需要花时间看paper了，先把框架搭起来吧
        int *pCount = new int(0);
        network_predict_image(mpNetwork, Image);
        detection *pDetection = get_network_boxes(mpNetwork, Image.w, Image.h, 0.5, 0.5, nullptr, 0,
                                                  pCount);//第一步：get_network_boxes
        do_nms_obj(pDetection, *pCount, mData.classes, 0.45);//第二步：do_nms_obj

        //获取检测结果
        for (size_t j = 0; j < *pCount; j++)
        {
            for (size_t i = 0; i < mData.classes; i++)
            {
                if (pDetection[j].prob[i] > 0)
                {
                    DetectResult Result;
                    Result.mName = mData.names[i];
                    Result.mConfidence = pDetection[j].prob[i];
                    Result.mTop = (pDetection[j].bbox.y - pDetection[j].bbox.h / 2);
                    Result.mBottom = (pDetection[j].bbox.y + pDetection[j].bbox.h / 2);
                    Result.mLeft = (pDetection[j].bbox.x - pDetection[j].bbox.w / 2);
                    Result.mRight = (pDetection[j].bbox.x + pDetection[j].bbox.w / 2);
                    vDetectResults.push_back(Result);
                }
            }
        }

    }

    void Detecting::DrawResult( cv::Mat &Image, vector<DetectResult> Result)
    {
        for (vector<DetectResult>::iterator it = Result.begin(); it != Result.end(); it++)
        {
            cv::Point2f PointA(it->mLeft, it->mTop);
            cv::Point2f PointB(it->mRight, it->mBottom);
            cv::rectangle(Image, PointA, PointB, cv::Scalar(5, 100, 255), 5);
        }
    }
}