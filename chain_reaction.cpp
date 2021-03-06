#include <iostream>
#include "board.h"
#include "player.h"
#include "rules.h"
#include "algorithm.h"
#include "string"
using namespace std;

int main(){

    Board board;
    Player red_player(RED);
    Player blue_player(BLUE);

    bool first_two_step = true;
    int round = 1;
    int index[2];

    Board record[1024];
    int row[1024];
    int col[1024];
    int i = 0;
    while(1){

        //////////// Red Player operations ////////////
        algorithm_A(board, red_player, index);
        board.place_orb(index[0], index[1], &red_player);

        if(rules_violation(red_player)) return 0;
        if (i < 1024) {
            record[i++] = board;
            row[i] = index[0];
            col[i] = index[1];
        }
        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(red_player) && !first_two_step){
            cout << "Red Player won the game !!!" << endl;
            break;
        }

        //////////// Blue Player operations ////////////
        algorithm_B(board, blue_player, index);
        board.place_orb(index[0], index[1], &blue_player);

        if(rules_violation(blue_player)) return 0;
        if (i < 1024) {
            record[i++] = board;
            row[i] = index[0];
            col[i] = index[1];
        }
        board.print_current_board(index[0], index[1], round);
        round++;

        if(board.win_the_game(blue_player) && !first_two_step){
            cout << "Blue Player won the game !!!" << endl;
            break;
        }

        first_two_step = false;
    }
    string cmd;
    cin >> cmd;
    while (cmd != "q") {
        if (cmd == "l") {
            if (i >= 0)
                --i;
            record[i].print_current_board(row[i], col[i], i + 1);
        }
        else if (cmd == "r") {
            if (i < 1024)
                ++i;
            record[i].print_current_board(row[i], col[i], i + 1);
        }
        else             record[i].print_current_board(row[i], col[i], i + 1);


        cin >> cmd;
    }

    return 0;
} 