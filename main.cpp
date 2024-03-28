#include <iostream>
#include "Algorithm/AimLock.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()){
        cout << "Camera is not opened" << endl;
        cap.open(0);
    }

    // Ò»Ö±¶ÁÈ¡
    while (true){
        Mat img;
        cap >> img;
        if (img.empty()){
            cout << "Image is empty" << endl;
            break;
        }
        vector<Point_t> res = getBoard(img, Blue, "../Model/RM.onnx");
        for (auto &i : res){
            cout << i->x << " " << i->y << endl;
        }
        imshow("img", img); 
        if (waitKey(1) == 27){
            break;
        }
    }
}
