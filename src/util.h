#include <cstdio>
#include <string>

#ifndef UTIL
#define UTIL

const std::string LOG_FILE_PATH = "./log";

struct logger{
private:
    static bool erase;
public:
    static void write(std::string line);
};
#endif
