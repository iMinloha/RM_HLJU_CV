#include <iostream>
#include "Algorithm/AimLock.hpp"
#include "opencv2/opencv.hpp"
#include "Algorithm/inference.hpp"
#include "GlobalType/SerialServer.hpp"
#include "Algorithm/Operation.hpp"

using namespace std;
using namespace cv;

vector<Point_t> historyData;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()){
        cout << "Camera is not opened" << endl;
        cap.open(0);
    }
    // cap设置尺寸
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 640);

    Inference inf("../Model/RM.onnx", cv::Size(640, 640));
    int rc = 0;

    // 一直读取
    while (true){
        Mat frame;
        cap >> frame;
        vector<Point_t> points;
        points = getBoard(frame, inf);

        // 输出坐标

        if (waitKey(1) == 27){
            break;
        }
    }
}
