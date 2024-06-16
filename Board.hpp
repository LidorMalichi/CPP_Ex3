#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <list>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Hexagon.hpp"
#include "Tile.hpp"

using namespace std;

class Board
{
    private:

        static shared_ptr<Board> instance;

        unordered_map<int, list<shared_ptr<Hexagon>>> layout;

        Board();

    public:

        static shared_ptr<Board> get_instance()
        {
            struct MakeSharedEnabler : public Board {
                MakeSharedEnabler() : Board(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }
        
        friend ostream& operator<<(ostream& os, const Board& board);
};


#endif