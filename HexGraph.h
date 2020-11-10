#include <vector>

namespace N {
class HexGraph
{
    public:
        void print_board();
    private:
        std::vector<std::vector<int>> edge_list;
};
}