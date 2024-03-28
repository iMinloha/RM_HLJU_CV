#include <unistd.h>
#include "Operation.hpp"
#include "thread"

template <typename T, typename R>
void operation(Func func, T *args, R *result){
#if MultiThread == ON
    std::thread t(func, args, result);
    t.join();
#endif
}

void ReceiveData(void* result, int length){
    // 串口收发数据
#if defined(__linux__) || defined(__gnu_linux__)
    int fd = open(SerialPort,O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1){
        perror("Open Serial Port Error");
        return;
    }else{
        fcntl(fd, F_SETFL, 0);
    }
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetospeed(&options, B115200);
    cfsetispeed(&options, B115200);
    tcsetattr(fd, TCSANOW, &options);
    read(fd, args, length);
    close(fd);
#endif
}

void SendData(void* args, int length){
    // 串口收发数据
#if defined(__linux__) || defined(__gnu_linux__)
    int fd = open(SerialPort,O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1){
        perror("Open Serial Port Error");
        return;
    }else{
        fcntl(fd, F_SETFL, 0);
    }
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetospeed(&options, B115200);
    cfsetispeed(&options, B115200);
    tcsetattr(fd, TCSANOW, &options);
    write(fd, result, length);
    close(fd);
#endif

}