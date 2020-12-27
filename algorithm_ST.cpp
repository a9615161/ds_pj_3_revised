#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
#define INF 2147483647
#define INF_N -2147483648

using namespace std;
#define ROW 5
#define COL 6
#define RED 'r'
#define BLUE 'b'
#define MAX_DEEP 5

typedef struct pair_{
    int i;
    int j;
}pos;

int evaluate(Board board,int color); //count for the current state of 
//int find_value(int i, int j, Board board, Player& me, Player& he, bool my_turn, int deep, int& upper, int& lower);
int algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
       srand(time(NULL)*time(NULL));
    int row, col;
    int color = player.get_color();
    
    Board copied(board);

    copied.get_orbs_num(1, 1);
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
    
}

int evaluate(Board board,int my_color) {
    int score = 0;
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            int current_color = board.get_cell_color(i, j);

            if (current_color == my_color)
                ++score;
            else if(current_color != 'w')//own by other players
                --score;
        }
    }

    return score;
}

