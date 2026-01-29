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

        int dir;
        switch(s_dir){
            case 'a':        
            case 'A':
                dir = DIR_LEFT;
            break;
            case 'd':
            case 'D':
                dir = DIR_RIGHT;
            break;
            case 's':
            case 'S':
                dir = DIR_DOWN;
            break;
            case 'w':
            case 'W':
                dir = DIR_UP;
            break;
            case 'l':
            case 'L':
                dir = DIR_LOG;
            break;
            case 'q':
            case 'Q':
                attron(COLOR_PAIR(7));
                mvprintw(graphics::board_row + 3 + (graphics::field_height * 4)
                        , graphics::board_column - 5 + (graphics::field_width * 2)
                        , "QUIT? [y/n]");
                refresh();
                s_dir = getch();
                attroff(COLOR_PAIR(7));
                if(s_dir == 'y' || s_dir == 'Y'){
                    graphics::end();
                    return 0;
                }
                attron(COLOR_PAIR(9));
                mvprintw(graphics::board_row + 3 + (graphics::field_height * 4)
                        , graphics::board_column - 5 + (graphics::field_width * 2)
                        , "            ");
                refresh();
                attroff(COLOR_PAIR(9));
                dir = DIR_UNDEF;
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
