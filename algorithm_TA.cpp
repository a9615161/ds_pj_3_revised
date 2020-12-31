#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "algorithm.h"

using namespace std;

void algorithm_B(Board board, Player player, int index[]){
    srand(time(NULL)*time(NULL)+788);
    int row, col;
    int color = player.get_color();
    int in1, in2;
    while(1){
        cin >> in1>>in2;
        row = --in1;
        col = --in2;
        //row = rand() % 5;
        //col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
}