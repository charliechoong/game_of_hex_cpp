#include "HexGraph.h"
#include <iostream>

using namespace std;

// Constructs graph for board
HexGraph ::HexGraph(const int size) : size(size)
{
    int count = 0;
    map<int, vector<int>> *v_ptr = &edge_list;
    for (int i = 0; i < size; i++)
    {
        vector<char> new_row;
        for (int j = 0; j < size; j++) {
            make_node(i, j, v_ptr);
            new_row.push_back('.');
        }
        grids.push_back(new_row);
        
    }
}

// Create edges for a given node defined by (i, j)
// edge_list contains the edges list for every node.
void HexGraph::make_node(int i, int j, map<int, vector<int>> *m)
//vector<int> HexGraph::make_node(int i, int j, vector<int> v)
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
    (*m)[map_to_int(i, j)] = v;
}

int HexGraph ::get_board_size()
{
    return size;
}

void HexGraph ::initialize_players()
{
    grids[0][0] = 'X';
    grids[size - 1][size - 1] = 'O';
}
// Checks if a move is legal.
// Move is legal if it is unoccupied and at least one of surrounding
// grids is occupied by itself
// Returns true if move is legal, otherwise false
bool HexGraph ::is_legal_move(int pos)
{
    tuple<int, int> coord = map_to_coord(pos);
    int x = get<0>(coord);
    int y = get<1>(coord);
    return is_empty_grid(x, y);
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
    for (auto edge: edge_list[0])
        cout << edge << " ";

};