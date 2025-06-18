#include "board.h"
#include <string>

#ifndef GRAPHICS_H
#define GRAPHICS_H

//TODO
//make graphics be responsible for clearing the screen and checking os

struct graphics{
    static unsigned int board_row;
    static unsigned int board_column;

    static void set_board_draw_pos(unsigned int row, unsigned int column);
    static void set_cursor(unsigned int row, unsigned int column);

    static void cursor_down(unsigned int n);
    static void cursor_foward(unsigned int n);
    static void cursor_back(unsigned int n);

    static void draw_board(game_board board);

    static std::string get_color(unsigned int n);
};

#endif
