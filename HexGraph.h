#include <vector>
#include <tuple>
#include <map>

class HexGraph
{
public:
    HexGraph(const int size = 11);
    int get_board_size();
    void make_node(int, int, std::map<int, std::vector<int>> *);
    void initialize_players();
    void print_board();
    void make_move(int, int);
    bool is_legal_move(int);
    bool is_won();
    bool is_empty_grid(int, int);

private:
    std::tuple<int, int> map_to_coord(int);
    int map_to_int(int, int);   
    std::map<int, std::vector<int>> player1;
    std::map<int, std::vector<int>> player2;
    std::vector<std::vector<char>> grids;
    int size;
};
