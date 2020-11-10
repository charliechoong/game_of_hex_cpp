#include "HexGraph.h"
#include <iostream>

using namespace std;

HexGraph ::HexGraph(const int size): size(size)
{
    for(int i=0; i<size; i++) {
        vector<char> new_row;
        for(int j=0; j<size; j++) 
            new_row.push_back('.');
        grids.push_back(new_row);
    }
}

int HexGraph ::get_board_size()
{
    return size;
}

void HexGraph ::initialize_players()
{
    grids[0][0] = 'X';
    grids[size-1][size-1] = 'O';
}

tuple<int, int> HexGraph ::map(int pos) 
{
    int x = pos/size;
    int y = pos%size;
    return make_tuple(x,y);
}

void HexGraph::print_board()
{
    cout << "Initial state: " << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<i*2; j++)
            cout << " ";
        for(int j=0; j<size; j++) {           
            cout << grids[i][j];
            if(j < size-1)
                cout << " _ ";
            else {
                cout << endl;
            }
        }
        if (i == size-1) break;
        for(int j=0; j<i*2+1; j++)
            cout << " ";
        for(int j=0; j<size-1; j++)
            cout << "\\ / ";
        cout << "\\" << endl;
    }
    cout << "Size of board: " << size << endl;
    cout << get<0>(map(32)) << " " << get<1>(map(32)) << endl;
};