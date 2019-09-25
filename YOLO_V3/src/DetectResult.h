//
// Created by leo on 18-11-20.
//

#ifndef PROJECT_DETECTRESULT_H
#define PROJECT_DETECTRESULT_H

#include <string>

using namespace std;

//把这个类单独放一个h文件是因为Frame类的编译链接问题
namespace YOLOv3
{
    class DetectResult
    {
    public:
        string mName;
        float mConfidence;
        float mTop;
        float mBottom;
        float mLeft;
        float mRight;

        bool mbGoodFlag = false;//不是好的检测结果

        char mDynamicPointsCount = 0;
        bool mbDynamicFlag = false;
    };
}

#endif //PROJECT_DETECTRESULT_H
