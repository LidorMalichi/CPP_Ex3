#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Hexagon.hpp"
#include "Tile.hpp"

using namespace std;

class Board
{
    private:

        static shared_ptr<Board> instance;

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
        
};


#endif