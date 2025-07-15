#include <cstddef>
#include <iostream>
#include <ctime>
#include <cstdlib>

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#define BOARD_HEIGHT 4
#define BOARD_WIDTH 4

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

const short directions[4][2] = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
};

struct game_board{
private:
    unsigned int board[BOARD_HEIGHT][BOARD_WIDTH];

    

public:
    game_board(){
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                board[i][j] = 0;
            }
        }
    }

    //print board
    void print(){
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                std::cout<<board[i][j]<<"\t";
            }
            std::cout<<std::endl;
        }
    }

    //is out of bounds
    bool is_ofb(unsigned int i, unsigned int j){
        return (i >= BOARD_HEIGHT) || (j >= BOARD_WIDTH);
    }

    //check if board[i][j] has been set
    bool is_set(unsigned int i, unsigned int j){
        if(is_ofb(i, j)){
            return true;
        }
        return board[i][j] != 0;
    }

    //check if all fields on board are set
    bool all_set(){
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                if(get(i, j) == 0){
                    return false;
                }
            }
        }
        return true;
    }

    //get the value of board[i][j]
    unsigned int get(unsigned int i, unsigned int j){
        if(is_ofb(i, j)){
            return 1;
        }
        return board[i][j];
    }

    //set the value of board[i][j] to o
    void set(unsigned int i, unsigned int j, unsigned int o){
        if(is_ofb(i, j)){
            return;
        }
        board[i][j] = o;
    }

    //set the value of random field of board to o
    void set_random(unsigned int o){
        if(all_set()){
            return;
        }
        srand(time(nullptr)); //set seed from current time
        unsigned int i = random_int(BOARD_HEIGHT);
        unsigned int j = random_int(BOARD_WIDTH);
        //TODO
        //bad
        while(is_set(i, j)){
            i = random_int(BOARD_HEIGHT);
            j = random_int(BOARD_WIDTH);
        }
        set(i, j, o);
    }

    //generate a random number from 0 to to
    unsigned int random_int(unsigned int to){
        return rand() % to;
    }

    //check if any i, j can move in direction i + h, j + v
    bool has_move(short h, short v){
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                if(!is_set(i, j)){
                    continue;
                }
                if(can_move(i, j, h, v)){
                    return true;
                }
            }
        }
        return false;
    }

    //check if board[i][j] can move is direction i + h, j + v
    bool can_move(unsigned int i, unsigned int j, short h, short v){
        if(is_ofb(i + h, j + v)){
            return false;
        }
        return !is_set(i + h, j + v) || get(i + h, j + v) == get(i, j);
    }
    
    void move_down(){
        short h = directions[DIR_DOWN][0];
        short v = directions[DIR_DOWN][1];
        for(size_t i = BOARD_HEIGHT - 1;i >= 0 && i < BOARD_HEIGHT;i--){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                if(!is_set(i, j)){
                    continue;
                }
                size_t k = i;
                while(can_move(k, j, h, v)){
                    if(!is_set(k + h, j + v)){
                        set(k + h, j + v, get(k, j));
                        set(k, j, 0);
                    }
                    if(get(k + h, j + v) == get(k, j)){
                        set(k + h, j + v, get(k, j) << 1);
                        set(k, j, 0);
                        break;
                    }
                    k++;
                }
            }
        }
    }

    void move_up(){
        short h = directions[DIR_UP][0];
        short v = directions[DIR_UP][1];
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                if(!is_set(i, j)){
                    continue;
                }
                size_t k = i;
                while(can_move(k, j, h, v)){
                    if(!is_set(k + h, j + v)){
                        set(k + h, j + v, get(k, j));
                        set(k, j, 0);
                    }
                    if(get(k + h, j + v) == get(k, j)){
                        set(k + h, j + v, get(k, j) << 1);
                        set(k, j, 0);
                        break;
                    }
                    k--;
                }
            }
        }
    }

    void move_left(){
        short h = directions[DIR_LEFT][0];
        short v = directions[DIR_LEFT][1];
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j < BOARD_WIDTH;j++){
                if(!is_set(i, j)){
                    continue;
                }
                size_t k = j;
                while(can_move(i, k, h, v)){
                    if(!is_set(i + h, k + v)){
                        set(i + h, k + v, get(i, k));
                        set(i, k, 0);
                    }
                    if(get(i + h, k + v) == get(i, k)){
                        set(i + h, k + v, get(i, k) << 1);
                        set(i, k, 0);
                        break;
                    }
                    k--;
                }
            }
        }
    }

    void move_right(){
        short h = directions[DIR_RIGHT][0];
        short v = directions[DIR_RIGHT][1];
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = BOARD_WIDTH - 1;j >= 0 && j < BOARD_WIDTH;j--){
                if(!is_set(i, j)){
                    continue;
                }
                size_t k = j;
                while(can_move(i, k, h, v)){
                    if(!is_set(i + h, k + v)){
                        set(i + h, k + v, get(i, k));
                        set(i, k, 0);
                    }
                    if(get(i + h, k + v) == get(i, k)){
                        set(i + h, k + v, get(i, k) << 1);
                        set(i, k, 0);
                        break;
                    }
                    k++;
                }
            }
        }
    }

    bool make_move(unsigned int dir){
        if(dir <= 3 && !has_move(directions[dir][0], directions[dir][1])){
            return false;
        }
        switch(dir){
            case DIR_DOWN:
                move_down();
            break;
            case DIR_UP:
                move_up();
            break;
            case DIR_LEFT:
                move_left();
            break;
            case DIR_RIGHT:
                move_right();
            break;
            default:
                return false;
            break;
        }
        return true;
    }
};

#endif
