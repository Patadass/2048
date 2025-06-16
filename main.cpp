#include "lib/board.h"
#include <cstdlib>

#if defined(_WIN32)
    #define PLATFOMR "windows"
#elif defined(_WIN64)
    #define PLATFORM "windows"
#elif defined(__linux__)
    #define PLATFORM "linux"
#else
    #define PLATFORM NULL
#endif


using namespace std;

int get_dir_from_string(string s){
    if(s[0] == 'u' || s[0] == 'U'){
        return DIR_UP;
    }
    if(s[0] == 'r' || s[0] == 'R'){
        return DIR_RIGHT;
    }
    if(s[0] == 'd' || s[0] == 'D'){
        return DIR_DOWN;
    }
    if(s[0] == 'l' || s[0] == 'L'){
        return DIR_LEFT;
    }
    return DIR_UP;
}

void clear_screen(){
    string platform = PLATFORM;
    if(platform == "linux"){
        system("clear");
    }
    if(platform == "windows"){
        system("cls");
    }
}

int main(){
    if(PLATFORM == NULL){
        return 0;
    }
    game_board gb;
    gb.set_random(2);
    gb.print();
    while(!gb.all_set()){
        string s_dir;
        cout<<endl;
        cout<<"(u)p (r)ight (d)own (l)eft (q)uit"<<endl;
        cin>>s_dir;
        if(s_dir[0] == 'q' || s_dir[0] == 'Q'){
            return 0;
        }
        //clear_screen();
        int dir = get_dir_from_string(s_dir);
        gb.make_move(dir);
        gb.set_random(2);
        gb.print();
    }
}
