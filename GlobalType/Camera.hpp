#ifndef RMARMOR_CAMERA_HPP
#define RMARMOR_CAMERA_HPP

#include "opencv2/opencv.hpp"
#include "../GlobalDef.hpp"
#include "Type.hpp"

using namespace cv;

typedef struct DoubleCameraParam{
    Mat CameraLeft;
    Mat CameraRight;

    Mat left_distortion;
    Mat right_distortion;

    Mat R;
    Mat t;

    double f;
    int baseLine;
}* DoubleCameraOBJ;

typedef struct CameraParam{
    Mat Camera;
    Mat distortion;

    Mat R;
    Mat T;
}* CameraOBJ;

// 使用Matlab标定
// const DoubleCameraOBJ DoubleEyes;
// const CameraOBJ C;

void ElimDistortion(Mat img);

#endif //RMARMOR_CAMERA_HPP
