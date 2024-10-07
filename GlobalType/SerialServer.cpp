#include "SerialServer.hpp"
#include "../GlobalDef.hpp"

Data::Data(Point_t p1){
    if(p1->x < 0 || p1->y < 0){
        sig_x = 1;
        sig_y = 1;
        height_x = abs(p1->x / 100);
        low_x = abs(p1->x % 100);
        height_y = abs(p1->y / 100);
        low_y = abs(p1->y % 100);
        int temp = p1->x + p1->y < 0 ? -(p1->x + p1->y + 1) : p1->x + p1->y + 1;
        height_crc = temp / 100;
        low_crc = temp % 100;
    }
}

int Data::getData(int index){
    switch (index){
        case 0:
            return sig_x;
        case 1:
            return height_x;
        case 2:
            return low_x;
        case 3:
            return sig_y;
        case 4:
            return height_y;
        case 5:
            return low_y;
        case 6:
            return height_crc;
        case 7:
            return low_crc;
        default:
            return -1;
    }
}


