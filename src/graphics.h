#include "board.h"
#include <string>

#ifndef GRAPHICS_H
#define GRAPHICS_H

#if defined(_WIN32)
    #define PLATFORM "windows"
#elif defined(_WIN64)
    #define PLATFORM "windows"
#elif defined(__linux__)
    #define PLATFORM "linux"
#elif defined(__APPLE__)
    #define PLATFORM "apple"
#else
    #define PLATFORM NULL
#endif

struct graphics{
    static unsigned int board_row;
    static unsigned int board_column;
    static unsigned int field_size;

    static void set_board_draw_pos(unsigned int row, unsigned int column);
    static void set_field_size(unsigned int n);
    static void set_cursor(unsigned int row, unsigned int column);

    static void cursor_down(unsigned int n);
    static void cursor_foward(unsigned int n);
    static void cursor_back(unsigned int n);
    static void cursor_up(unsigned int n);

    static void draw_board(game_board board);

    static std::string get_color(unsigned int n);

    static void clear_screen();
};
#endif
