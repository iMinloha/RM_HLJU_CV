#include "Type.hpp"

Logger::Logger(std::string filePath, SaveLogger mode) {
    this->file = filePath;
    this->mode = mode;
}

Logger::Logger() {

}

void Logger::out(std::string msg) {
    time_t now = time(nullptr);
    tm* curr = localtime(&now);
    char name[80] = {0};
    strftime(name, 80, "%Y-%m-%d_%H", curr);
    string names = name;
    if (this->mode == Save){
        fstream f;
        f.open(this->file + names + ".log", ios::out);
        f << msg << endl;
    }else{
        cout << "["<< names << "]: " << msg << endl;
    }
}

