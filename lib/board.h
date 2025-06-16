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

struct game_board{
private:
    unsigned int board[BOARD_HEIGHT][BOARD_WIDTH];

    const short directions[4][2] = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };

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
        srand(time({})); //set seed from current time
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

    //TODO
    //bad
    bool has_movable(short h, short v){
        for(size_t i = 0;i < BOARD_HEIGHT;i++){
            for(size_t j = 0;j< BOARD_WIDTH;j++){
                if(is_ofb(i + h, j + v)){
                    continue;
                }
                if(get(i, j) == 0){
                    continue;
                }
                if(!is_set(i + h, j + v)){
                    return true;
                }
                if(get(i, j) == get(i + h, j + v)){
                    return true;
                }
            }
        }
        return false;
    }
    
    //TODO
    //this bad make 4 diff funcs than call them from this func
    //take pos in board move it fully than go to next one
    //take pos starting from the direction you want to move in 
    //if going down start from bottom of array
    void make_move(unsigned int dir){
        if(dir > 3){
            return;
        }
        short h = directions[dir][0];
        short v = directions[dir][1];
        while(has_movable(h, v)){
            for(size_t i = 0;i < BOARD_HEIGHT;i++){
                for(size_t j = 0;j < BOARD_WIDTH;j++){
                    if(is_ofb(i + h,j + v)){
                        continue;
                    }
                    if(!is_set(i + h,j + v)){
                        set(i + h,j + v, get(i, j));
                        set(i, j, 0);
                    }
                    if(get(i, j) == get(i + h,j + v)){
                        set(i + h, j + v, get(i, j) << 1);
                        set(i, j, 0);
                    }
                }
            }
        }
    }
};

#endif
