#include <iostream>
#include "Algorithm/AimLock.hpp"
#include "opencv2/opencv.hpp"
#include "Algorithm/inference.hpp"

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()){
        cout << "Camera is not opened" << endl;
        cap.open(0);
    }

    Inference inf("../Model/RM.onnx", cv::Size(1024, 1024));

    // Ò»Ö±¶ÁÈ¡
    while (true){
        Mat frame;
        cap >> frame;
        vector<Point_t> points;
        points = getBoard(frame, Blue, inf);
        if (waitKey(1) == 27){
            break;
        }
    }
}
