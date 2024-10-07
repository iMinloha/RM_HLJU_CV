#ifndef RMARMOR_SERIALSERVER_HPP
#define RMARMOR_SERIALSERVER_HPP

#include <iostream>
#include "Type.hpp"

#define BEGIN 0xAA

class Data{
private:
    int height_x;
    int low_x;
    int sig_x;

    int height_y;
    int low_y;
    int sig_y;

    int height_crc;
    int low_crc;

public:
    int getData(int index);
    Data(Point_t p1);

};

int ReceiveData(int* result);

int SendData(int data);



#endif //RMARMOR_SERIALSERVER_HPP
