#include "board.h"
#include "graphics.h"
#include "util.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int get_dir_from_string(string s){
    if(s[0] == 'w' || s[0] == 'W'){
        return DIR_UP;
    }
    if(s[0] == 'd' || s[0] == 'D'){
        return DIR_RIGHT;
    }
    if(s[0] == 's' || s[0] == 'S'){
        return DIR_DOWN;
    }
    if(s[0] == 'a' || s[0] == 'A'){
        return DIR_LEFT;
    }
    if(s[0] == 'l' || s[0] == 'L'){
        return DIR_LOG;
    }
    return DIR_UNDEF;
}

int main(){
    if(PLATFORM == NULL){
        cout<<"os not supported"<<endl;
        return 0;
    }
    game_board gb;
    gb.set_random(2);
    graphics::clear_screen();
    graphics::center_board();
    graphics::draw_score(gb);
    graphics::draw_board(gb);
    while(!gb.all_set()){
        string s_dir;
        cout<<endl;
        cout<<"(w)up (d)right (s)down (a)left (q)uit"<<endl;
        cin>>s_dir;
        if(s_dir[0] == 'q' || s_dir[0] == 'Q'){
            return 0;
        }
        int dir = get_dir_from_string(s_dir);
        if(dir == DIR_UNDEF){
            graphics::clear_screen();
            graphics::draw_score(gb);
            graphics::draw_board(gb);
            continue;
        }
        if(dir == DIR_LOG){
            logger::show_log();
            cin>>s_dir;
            logger::ushow_log();
            graphics::draw_score(gb);
            graphics::draw_board(gb);
            continue;
        }
        if(!gb.make_move(dir)){
            graphics::draw_score(gb);
            graphics::draw_board(gb);
            continue;
        }
        gb.set_random(2);
        graphics::draw_score(gb);
        graphics::draw_board(gb);
    }
}
