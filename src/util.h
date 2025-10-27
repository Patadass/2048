#include <cstdio>
#include <string>

#ifndef UTIL
#define UTIL

#define TIME_ON 1
#define TIME_OFF 0

const std::string LOG_FILE_PATH = "./log";

struct logger{
private:
    static bool erase;
public:
    static void write(std::string fmt, int log_time, ...);
};

struct converter{
public:
    //int to string
    static std::string itos(int o);
};

#endif
