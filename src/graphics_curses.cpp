#include "graphics.h"
#include "util.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <string>

#include <ncurses.h>

//for line numbers
#ifdef __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

unsigned int graphics::board_row = 1;
unsigned int graphics::board_column = 0;
unsigned int graphics::field_width = 9;
unsigned int graphics::field_height = 3;

void graphics::init(){
    initscr();
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    bkgd(COLOR_PAIR(9));
}

void graphics::end(){
    endwin();
}

void graphics::set_field_width(unsigned int n){
    if(n < 4 || n > 20){
        n = graphics::field_width;
    }else{
        if(n % 2 == 0){
            n++;
        }
        graphics::field_width = n;
    }
}

void graphics::set_board_draw_pos(unsigned int row, unsigned int column){
    graphics::board_row = row;
    graphics::board_column = column;
}

void graphics::center_board(){
    string platform = PLATFORM;
    if(platform != "linux"){
        return;
    }
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    int row = (ws.ws_row / 2) - (field_height * BOARD_HEIGHT) / 2;
    int column = (ws.ws_col / 2) - (field_width * BOARD_WIDTH) / 2;
    graphics::set_board_draw_pos(row, column);
}

void graphics::set_cursor(unsigned int row, unsigned int column){
    move(row, column);
}

void graphics::cursor_down(unsigned int n = 1){
    unsigned int row, column;
    getyx(stdscr, row, column);
    move(row + n, column);
}

void graphics::cursor_up(unsigned int n = 1){
    int row, column;
    getyx(stdscr, row, column);
    if(row - n < 0){return;}
    move(row - n, column);
}

void graphics::cursor_foward(unsigned int n = 1){
    unsigned int row, column;
    getyx(stdscr, row, column);
    move(row, column + n);
}

void graphics::cursor_back(unsigned int n = 1){
    int row, column;
    getyx(stdscr, row, column);
    if(column - n < 0){return;}
    move(row, column - n);
}

void graphics::draw_board(game_board board, bool center){
    if(center){
        center_board();
    }
    set_cursor(board_row, board_column);
    for(size_t i = 0;i < BOARD_HEIGHT;i++){
        for(size_t j = 0;j < BOARD_WIDTH;j++){
            int num_of_digits = 1;
            if(board.get(i, j) > 0){
                num_of_digits = log10(board.get(i, j)) + 1;
            }

            int left_space = field_width / 2;
            int right_space = (field_width / 2) - (num_of_digits / 2);
            if(num_of_digits % 2 == 0){
                left_space -= (num_of_digits / 2) - 1;
            }else{
                left_space -= (num_of_digits / 2);
            }

            attron(COLOR_PAIR(get_color_pair(board.get(i, j))));
            for(unsigned int k = 0;k < field_width;k++){
                printw(" ");
            }

            cursor_down(1);
            cursor_back(field_width);

            for(int k = 0;k < left_space;k++){
                printw(" ");
            }
            if(board.get(i, j) == 0){
                printw(" ");
            }else{
                printw("%d", board.get(i, j));
            }
            for(int k = 0;k < right_space;k++){
                printw(" ");
            }

            cursor_down(1);
            cursor_back(field_width);
            for(unsigned int k = 0;k < field_width;k++){
                printw(" ");
            }
            cursor_up(2);
            attroff(COLOR_PAIR(get_color_pair(board.get(i, j))));
        }
        cursor_back(field_width*BOARD_WIDTH);
        cursor_down(3);
    }
}

int graphics::get_color_pair(unsigned int n){
    if(n == 0){
        return 9;
    }
    n = log2(n);
    if(n % 6 == 0){
        return 6;
    }
    return n%6;
}

void graphics::clear_screen(){
    clear();
}
