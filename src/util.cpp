#include "util.h"
#include <fstream>
#include <ctime>

using namespace std;

bool logger::erase = true;

void logger::write(string line, int log_time){
    ofstream stream;
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
        strftime(out, 30, "%F %H:%M:%S ", localtime(&timestamp));
        stream<<out;
    }
    stream<<line<<"\n";
    stream.close();
}

