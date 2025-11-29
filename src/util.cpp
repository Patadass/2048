#include "util.h"
#include "graphics.h"
#include <cstdarg>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

bool logger::erase = true;
void* logger::win = nullptr;

void logger::write(string fmt, int log_time, ...){
    ofstream stream;

    string line = "";
    va_list args;
    va_start(args, log_time);
    for(size_t i = 0;i < fmt.length();i++){
        if(fmt[i] != '%'){
            line += fmt[i];
            continue;
        }
        i++;
        if(fmt[i] == 'd'){
            line += converter::itos(va_arg(args, int));
        }
        if(fmt[i] == 's'){
            line += (char)(va_arg(args, int));
        }
    }

    va_end(args);
    if(erase){
        stream.open(LOG_FILE_PATH, ios::trunc);
        logger::erase = false;
    }else{
        stream.open(LOG_FILE_PATH, ios::app);
    }

    if(log_time == TIME_ON){
        time_t timestamp;
        char out[30];
        time(&timestamp);
        strftime(out, 30, "[%F %H:%M:%S] ", localtime(&timestamp));
        stream<<out;
    }
    stream<<line<<"\n";
    stream.close();
}

void* logger::show_log(){
    ifstream f;
    win = graphics::create_window(30, 50, 1, 1);
    f.open(LOG_FILE_PATH);
    graphics::print_on_window(win, &f);
    f.close();
    return win;
}

void logger::ushow_log(){
    graphics::destory_win(win);
}


string converter::itos(int o){
    string rs = "";

    if(o == 0){
        return "0";
    }

    while(o != 0){
        rs = (char)((o % 10) + '0') + rs;
        o /= 10;
    }
    return rs;
}

