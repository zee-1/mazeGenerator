#include <iostream>

std::string LogLevel[3] = {"[LOG]","[WARNING]","[ERROR]"};

#define log(message) std::cerr<<"[LOG]: From "<<__func__<<message<<std::endl;