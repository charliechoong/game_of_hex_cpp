#include "HexGraph.h"
#include <iostream>

using namespace std;

int main() {
    HexGraph board = HexGraph();
    board.print_board();
    board.initialize_players();
    board.print_board();
    return 0;
}