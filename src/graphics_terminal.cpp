#include "graphics.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

unsigned int graphics::board_row = 1;
unsigned int graphics::board_column = 0;
unsigned int graphics::field_size = 9;

//set size of field
void graphics::set_field_size(unsigned int n){
    if(n < 4 || n > 20){
        n = graphics::field_size;
    }else{
        if(n % 2 == 0){
            n++;
        }
        graphics::field_size = n;
    }
}

//set the position from which to draw the board
void graphics::set_board_draw_pos(unsigned int row, unsigned int column){
    graphics::board_row = row;
    graphics::board_column = column;
}

//TODO
//check number of columns and rows before setting cursos
void graphics::set_cursor(unsigned int i, unsigned int j){
    cout<<"\033["<<i<<";"<<j<<"H";
}

//move the cursor n rows down
void graphics::cursor_down(unsigned int n = 1){
    cout<<"\033["<<n<<"B";
}

//move the cursor n rows up
void graphics::cursor_up(unsigned int n = 1){
    cout<<"\033["<<n<<"A";
}

//move the cursor n columns foward
void graphics::cursor_foward(unsigned int n = 1){
    cout<<"\033["<<n<<"C";
}

//move the cursor n columns back
void graphics::cursor_back(unsigned int n = 1){
    cout<<"\033["<<n<<"D";
}

void graphics::draw_board(game_board board){
    set_cursor(board_row, board_column);
    for(size_t i = 0;i < BOARD_HEIGHT;i++){
        for(size_t j = 0;j < BOARD_WIDTH;j++){
            int num_of_digits = 1;
            if(board.get(i, j) > 0){
                num_of_digits = log10(board.get(i, j)) + 1;
            }

            int left_space = field_size / 2;
            int right_space = (field_size / 2) - (num_of_digits / 2);
            if(num_of_digits % 2 == 0){
                left_space -= (num_of_digits / 2) - 1;
            }else{
                left_space -= (num_of_digits / 2);
            }

            cout<<get_color(board.get(i, j));

            for(int k = 0;k < field_size;k++){
                cout<<" ";
            }
            cursor_down(1);
            cursor_back(field_size);

            for(int k = 0;k < left_space;k++){
                cout<<" ";
            }
            if(board.get(i, j) == 0){
                cout<<" ";
            }else{
                cout<<board.get(i, j);
            }
            for(int k = 0;k < right_space;k++){
                cout<<" ";
            }

            cursor_down(1);
            cursor_back(field_size);
            for(int k = 0;k < field_size;k++){
                cout<<" ";
            }
            cursor_up(2);
        }
        cursor_back(field_size*BOARD_WIDTH);
        cursor_down(3);
    }
    //reset
    cout<<"\033[0m";
}

//get the ansi escape code for the given n=2^a board field
//codes 41-46 (red-cyan) for numbers 2 4 8 16 32 64
//codes 101-106 (brightred-brightcyan) for numbers 128 256 512 1024 2048 4096
string graphics::get_color(unsigned int n){
    if(n == 0){
        return "\033[37;100m";
    }
    string ansi = "\033[";
    n = log2(n);
    if(n <= 6){
        ansi += "37;";
        ansi += "4";
        ansi += (n + '0');
    }else if(n <= 12){
        ansi += "30;";
        n -= 6;
        ansi += "10";
        ansi += (n + '0');
    }else{
        ansi += "37;";
        ansi += 40;
    }
    ansi += 'm';
    return ansi;
}

void graphics::clear_screen(){
    string platform = PLATFORM;
    if(platform == "linux" || platform == "apple"){
        system("clear");
    }
    if(platform == "windows"){
        system("cls");
    }
}

