#include "util.h"
#include <fstream>

using namespace std;

bool logger::erase = true;

void logger::write(string line){
    ofstream stream;
    if(erase){
        stream.open(LOG_FILE_PATH, ios::trunc);
        logger::erase = false;
    }else{
        stream.open(LOG_FILE_PATH, ios::app);
    }
    stream<<line<<"\n";
    stream.close();
}

