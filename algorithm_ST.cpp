#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "algorithm.h"

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
#define MAX_DEEP 4

#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

typedef struct pair_{
    int i;
    int j;
}pos;

int evaluate(Board board,int color); //count for the current state of 
int find_value(int i, int j, Board board, Player& me, Player& he, bool my_turn, int deep, int upper, int lower);
//upper bound for max,lower bound for min .for the alpha-beta pruning

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
       srand(time(NULL)*time(NULL));
    int row, col;
    int color = player.get_color();
    int b_color;
   
    


    Board copied(board);
    int max_val = INF_N;
    int val;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            b_color = board.get_cell_color(i, j);
            if (b_color == player.get_color() || b_color =='w') {

                if (color == RED) {
                    Player he(BLUE);
                    val = find_value(i, j, board, player, he, 1, 0, INF_N, INF);
                }
                else {
                    Player he(RED);
                    val = find_value(i, j, board, player, he, 1, 0, INF_N, INF);
                }
                
                if (val > max_val) {
                    max_val = val;
                    index[0] = i;
                    index[1] = j;
                }
            }
        }
    }

  
    
}

int evaluate(Board board, int my_color) {
    int score = 0;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            int current_color = board.get_cell_color(i, j);

            if (current_color == my_color)
                 ++score;
            else if (current_color != 'w')//own by other players
                --score;
        }
    }

    return score;
}

int find_value(int i, int j, Board board, Player& me, Player& he, bool my_turn, int deep, int lower, int upper) {
    int a;
    //cin >> a;
    if (my_turn)
        board.place_orb(i, j, &me);

    else
        board.place_orb(i, j, &he);

    //board.print_current_board(i, j, deep);
    int my_color = me.get_color();
    int he_color = he.get_color();

    int my_color_cnt = 0;
    int he_color_cnt = 0;
    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            if (board.get_cell_color(row,col) == my_color) ++my_color_cnt;
            else if (board.get_cell_color(row,col) == he_color) ++he_color_cnt;

        }
    }
    bool is_win = board.win_the_game(me);
    bool is_loss = board.win_the_game(he);




    if (is_win&&my_color_cnt>1)
        return INF;
    else if (is_loss&& he_color_cnt > 1) 
        return INF_N;
    else if (deep == MAX_DEEP) //return the current score
        return evaluate(board, me.get_color());

    else {//find the best path recurrsively
        if (my_turn) {//should do sth to end finding earily

            int score = INF_N;
            int val;
            bool cut = 0;
            for (int row = 0; row < ROW && !cut; ++row) {
                for (int col = 0; col < COL; ++col) {

                    int current_color = board.get_cell_color(row, col);

                    if (current_color == he_color || current_color == 'w') {
                        val = find_value(row, col, board, me, he, 0, deep + 1,upper,lower );
                        score = max(score, val);

                        lower = max(lower, score);

                        if (upper <= lower) {
                            cut = 1;
                            break;
                        }
                    }
                }
            }
            upper = lower; 
            lower = INF_N; //to search for new min, the upper is unknow
            return score;
        }
        else {//minimum score that the maximizing player is assured .althpa
            //maximum score that the minimizing player is assured of. beta
            int score = INF;
            int val;
            bool cut = 0;
            for (int row = 0; row < ROW&&!cut; ++row) {
                for (int col = 0; col < COL; ++col) {

                    int current_color = board.get_cell_color(row, col);

                    if (current_color == my_color || current_color == 'w') {
                        val = find_value(row, col, board, me, he, 1, deep + 1, upper, lower);
                        score = min(score, val);

                        upper = min(upper, score);

                        if (upper <= lower) {
                            cut = 1;
                            break;
                        }
                            
                    }
                }
            }

            lower = upper;//in the end of finding "min", the upper will be ensured ,and thus become the lower 
            upper = INF; //to search for new min, the upper is unknow
            return score;

        }
    }


}

/*
int evaluate(Board board,int my_color) {
    int score = 0;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            int current_color = board.get_cell_color(i, j);
            int cap = board.get_capacity(i,j);
            int num = board.get_orbs_num(i,j);
            int max_val = 0;

            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l)
                    if (i+k<ROW&&j+l<COL&&board.get_cell_color(i + k, j + l) != current_color)
                        ++max_val;
            }
            if (cap - num == 0)
                cin >> max_val;
            int val = max_val / (cap - num);
            if (current_color == my_color)
                score += val;
            else if (current_color != 'w')//own by other players
                score -= val;
        }
    }

    return score;
}
*/

