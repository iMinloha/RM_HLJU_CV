#include <iostream>
#include "Algorithm/AimLock.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("C:/Users/28211/Desktop/download.jpg");
    getBoard(img, Blue);
    // Logger logger("C:/Users/28211/Desktop/", Save);
    // logger.out("Hello World");
}
