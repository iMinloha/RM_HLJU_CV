#include <iostream>
#include "Algorithm/AimLock.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("C:/Users/28211/Desktop/download.jpg");
    vector<Point_t> res = getBoard(img, Blue, "../Model/RM.onnx");
    for (auto &i : res){
        cout << i->x << " " << i->y << endl;
    }
    // Logger logger("C:/Users/28211/Desktop/", Save);
    // logger.out("Hello World");
}
