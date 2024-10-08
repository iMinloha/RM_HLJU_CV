
#ifndef RMARMOR_AIMLOCK_HPP
#define RMARMOR_AIMLOCK_HPP

#include "opencv2/opencv.hpp"
#include <iostream>
#include "../GlobalDef.hpp"
#include "../GlobalType/Type.hpp"
#include "inference.hpp"

using namespace cv;

#define Pi 3.1415
#define rotate_angle 80
#define horizontal_angle 10

int Check();

void NMS(vector<Rect> &srcRect, float thresh);

void TrainSVM(string path);

vector<Point_t> getBoard(Mat img
#if ONNX == ON && TensorRT == OFF
        , Inference inf
#endif
);

#endif
