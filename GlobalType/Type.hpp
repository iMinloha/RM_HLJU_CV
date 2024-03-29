#ifndef RMARMOR_TYPE_HPP
#define RMARMOR_TYPE_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include <opencv2/opencv.hpp>
using namespace std;

typedef struct TPoint{
    int x;
    int y;
    TPoint(int x, int y) : x(x), y(y) {};
}* Point_t;

enum SaveLogger{
    Save,
    NoSave
};

class Logger : public ostream {
public:
    Logger();
    Logger(std::string filePath, SaveLogger mode);
    void out(std::string msg);
private:
    std::string file;
    SaveLogger mode;
};

#endif
