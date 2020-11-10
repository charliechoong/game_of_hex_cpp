#include <vector>
#include <tuple>
//#include <string>

class HexGraph
{
public:
    HexGraph(const int size = 11);
    int get_board_size();
    void initialize_players();
    void print_board();
    void make_move();
    bool is_legal_move();
    bool is_won();

private:
    std::tuple<int, int> map(int pos);
    std::vector<std::vector<int>> edge_list;
    std::vector<std::vector<char>> grids;
    int size;
};
