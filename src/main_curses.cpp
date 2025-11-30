#include "board.h"
#include "graphics.h"
#include "util.h"
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

int main(){
    if(PLATFORM == NULL){
        cout<<"os not supported"<<endl;
        return 0;
    }
    graphics::init();
    game_board gb;
    gb.set_random(2);
    graphics::clear_screen();
    graphics::center_board();
    graphics::draw_board(gb);
    graphics::draw_score(gb);

    WINDOW* win = nullptr;
    while(!gb.all_set()){
        if(win != nullptr){
            refresh();
            logger::ushow_log();
            win = (WINDOW*) logger::show_log();
            wrefresh(win);
        }
        int s_dir = getch();
        if(s_dir == 'q' || s_dir == 'Q'){
            break;
        }
        int dir;
        switch(s_dir){
            case 'a':        
                dir = DIR_LEFT;
            break;
            case 'd':
                dir = DIR_RIGHT;
            break;
            case 's':
                dir = DIR_DOWN;
            break;
            case 'w':
                dir = DIR_UP;
            break;
            case 'l':
                dir = DIR_LOG;
            break;
            default:
                dir = DIR_UNDEF;
            continue;
        }
        if(dir == DIR_LOG){
            if(win != nullptr){
                logger::ushow_log();
                win = nullptr;
                graphics::clear_screen();
                graphics::draw_board(gb);
                graphics::draw_score(gb);
                continue;
            }
            win = (WINDOW*) logger::show_log();
            continue;
        }
        if(!gb.make_move(dir)){
            continue;
        }
        graphics::clear_screen();
        gb.set_random(2);
        graphics::draw_board(gb);
        graphics::draw_score(gb);
    }
    graphics::end();
    return 0;
}
