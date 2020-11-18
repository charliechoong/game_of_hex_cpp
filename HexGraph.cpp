#include "HexGraph.h"
#include <iostream>

using namespace std;

// Constructs graph for board
HexGraph ::HexGraph(const int size) : size(size)
{
    for (int i = 0; i < size; i++)
    {
        vector<char> new_row;
        for (int j = 0; j < size; j++) {
            new_row.push_back('.');
        }
        grids.push_back(new_row);       
    }
}

// Create edges for a given node defined by (i, j)
// edge_list contains the edges list for every node.
void HexGraph::make_node(int i, int j, map<int, vector<int>> *player)
{
    vector<int> v;
    // corner node: top left
    if (i == 0 and j == 0)
    {
        v.push_back(map_to_int(i, j + 1));
        v.push_back(map_to_int(i + 1, j));
    }
    // corner node: top right
    else if (i == 0 and j == size - 1)
    {
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i + 1, j));
        v.push_back(map_to_int(i + 1, j -1));
    }
    // corner node: bottom left
    else if (i == size-1 and j == 0)
    {
        v.push_back(map_to_int(i, j + 1));
        v.push_back(map_to_int(i - 1, j));
        v.push_back(map_to_int(i - 1, j + 1));
    }
    // corner node: bottom right
    else if (i == size-1 and j == size-1)
    {
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i - 1, j));
    }
    // non_corner side nodes: top
    else if (i == 0)
    {
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i, j + 1));
        v.push_back(map_to_int(i + 1, j - 1));
        v.push_back(map_to_int(i + 1, j));
    }
    // non_corner side nodes: left
    else if (j == 0)
    {
        v.push_back(map_to_int(i - 1, j));
        v.push_back(map_to_int(i - 1, j + 1));
        v.push_back(map_to_int(i, j + 1));
        v.push_back(map_to_int(i + 1, j));
    }
    // non_corner side nodes: right
    else if (j == size - 1)
    {
        v.push_back(map_to_int(i - 1, j));
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i + 1, j - 1));
        v.push_back(map_to_int(i + 1, j));
    }
    // non_corner side nodes: bottom
    else if (i == size - 1)
    {
        v.push_back(map_to_int(i - 1, j));
        v.push_back(map_to_int(i - 1, j + 1));
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i, j + 1));
    }
    // internal node
    else 
    {
        v.push_back(map_to_int(i - 1, j));
        v.push_back(map_to_int(i - 1, j + 1));
        v.push_back(map_to_int(i, j - 1));
        v.push_back(map_to_int(i, j + 1));
        v.push_back(map_to_int(i + 1, j - 1));
        v.push_back(map_to_int(i + 1, j));
    }    
    (*player)[map_to_int(i, j)] = v;
}

int HexGraph ::get_board_size()
{
    return size;
}

void HexGraph ::initialize_players()
{
    grids[0][0] = 'X';
    grids[size - 1][size - 1] = 'O';
    map<int, vector<int>> *p1 = &player1;
    map<int, vector<int>> *p2 = &player2;
    make_node(0, 0, p1);
    make_node(size-1, size-1, p2);
}

// Checks if a move is legal.
// Move is legal if it is unoccupied and at least one of surrounding
// grids is occupied by itself
// Returns true if move is legal, otherwise false
bool HexGraph ::is_legal_move(int turn, int pos)
{
    tuple<int, int> coord = map_to_coord(pos);
    int x = get<0>(coord);
    int y = get<1>(coord);
    char shape;
    if (turn == 1) {
        shape = 'X';
    } else {
        shape = 'O';
    } 
    return (is_empty_grid(x, y) && is_reachable_move(x, y, shape));
}

// Returns the coordinates of the grid given integer input by user
tuple<int, int> HexGraph ::map_to_coord(int pos)
{
    int x = pos / size;
    int y = pos % size;
    return make_tuple(x, y);
}

// Returns integer based on coordinates of a grid
int HexGraph ::map_to_int(int x, int y)
{
    return x * size + y;
}

// Checks if a grid is empty
bool HexGraph ::is_empty_grid(int x, int y)
{
    return grids[x][y] == '.';
}

// Checks if game is won
bool HexGraph ::is_won() {
    return false;
}

bool HexGraph ::is_reachable_move(int x, int y, char player) {
    // check corner nodes
    if (x == 0 and y == 0) 
        return (grids[x][y+1] == player ||  grids[x+1][y] == player);
    else if (x == 0 and y == size-1)
        return (grids[x][y-1] == player || grids[x+1][y] == player || grids[x+1][y-1] == player);
    else if (x == size-1 and y == 0)
        return (grids[x][y+1] == player ||  grids[x-1][y] == player || grids[x-1][y+1] == player);
    else if (x == size-1 and y == size-1)
        return (grids[x][y-1] == player ||  grids[x-1][y] == player);
    // check top nodes
    else if (x == 0)
        return (grids[x][y-1] == player || grids[x][y+1] == player || grids[x+1][y] == player || grids[x+1][y-1] == player);
    // check left nodes
    else if (y == 0)
        return (grids[x-1][y] == player || grids[x-1][y+1] == player || grids[x][y+1] == player || grids[x+1][y] == player);
    // check right nodes
    else if (y == size-1)
        return (grids[x-1][y] == player || grids[x][y-1] == player || grids[x+1][y] == player || grids[x+1][y-1] == player); 
    // check bottom nodes
    else if (x == size-1)
        return (grids[x-1][y] == player || grids[x-1][y+1] == player || grids[x][y+1] == player || grids[x][y-1] == player);
    // check internal node
    else
        return (grids[x-1][y] == player || grids[x-1][y+1] == player || grids[x][y+1] == player || grids[x][y-1] == player || 
        grids[x+1][y] == player || grids[x+1][y-1] == player);
}

// Makes a move
// Updates the content of the grid square
// & adds edges to player's graph
void HexGraph ::make_move(int player, int move) {
    map<int, vector<int>> *v_ptr;
    char shape;
    if (player == 1) {
        shape = 'X';
        v_ptr = &player1;
    } else {
        shape = 'O';
        v_ptr = &player2;
    }   
    int x = get<0>(map_to_coord(move));
    int y = get<1>(map_to_coord(move));
    grids[x][y] = shape;
    make_node(x, y, v_ptr);
}

// Prints the board at current state
void HexGraph::print_board()
{
    cout << "Initial state: " << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i * 2; j++)
            cout << " ";
        for (int j = 0; j < size; j++)
        {
            cout << grids[i][j];
            if (j < size - 1)
                cout << " _ ";
            else
            {
                cout << endl;
            }
        }
        if (i == size - 1)
            break;
        for (int j = 0; j < i * 2 + 1; j++)
            cout << " ";
        for (int j = 0; j < size - 1; j++)
            cout << "\\ / ";
        cout << "\\" << endl;
    }
    cout << "Size of board: " << size << endl;
    cout << get<0>(map_to_coord(32)) << " " << get<1>(map_to_coord(32)) << endl;
    cout << "Edges of (0, 0): ";
    //for (auto edge: edge_list[0])
    //    cout << edge << " ";

};