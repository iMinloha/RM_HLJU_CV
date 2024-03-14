#include "Camera.hpp"
#include <iostream>
#include <thread>

using namespace std;

// 单双目切换消除畸变
#if Monocular == ON && DoubleEye == OFF
    void ElimDistortion(Mat img, Mat dst, CameraOBJ obj){
        mutex mtx;
        mtx.lock();
        undistort(img, dst, obj->Camera, obj->distortion);
        mtx.unlock();
    }
#elif Monocular == OFF && DoubleEye == ON
    void ElimDistortion(Mat left,Mat left_dst, Mat right, Mat right_dst, DoubleCameraOBJ obj){
        mutex mtx;
        mtx.lock();
        undistort(left, left_dst, obj->CameraLeft, obj->left_distortion);
        undistort(right, right_dst, obj->CameraRight, obj->right_distortion);
        mtx.unlock();
    }
#else
    void ElimDistortion(){
        Logger newlog();
        newlog().out("No camera defined or duplicated, please check the global configuration file.");
    }
#endif

