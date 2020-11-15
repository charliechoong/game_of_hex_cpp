#include "HexGraph.h"
#include <iostream>

using namespace std;

int main() {
    HexGraph board = HexGraph();
    board.initialize_players();
    board.print_board();
    int move, turn = 1;
    while (!board.is_won()) {
        cout << "Input move: ";
        cin >> move;
        while (!board.is_legal_move(move)) {
            cout << "Illegal move. Please input again: ";
            cin >> move;
        }
        board.make_move(turn, move);
        board.print_board();
        if (turn == 1) {
            turn = 2;
        }
        else turn = 1;
    }

    return 0;
}