#include <cstdio>
#include <string>

#ifndef UTIL
#define UTIL

const std::string LOG_FILE_PATH = "./log";

struct logger{
private:
    static bool erase;
    static void* win;
public:
    static void write(std::string fmt, ...);
    static void* show_log();
    static void ushow_log();
};

struct converter{
public:
    //int to string
    static std::string itos(int o);
};

#endif
