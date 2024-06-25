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

// Board class
class Board
{
    private:

        // Board singleton instance
        static shared_ptr<Board> instance;

        // the board hex layout
        unordered_map<int, list<shared_ptr<Hexagon>>> layout;

        Board();

    public:

        // Get the singelton instance
        static shared_ptr<Board> get_instance()
        {
            // A struct that gets access to private constructor
            struct MakeSharedEnabler : public Board {
                MakeSharedEnabler() : Board(){}
            };

            if(!instance)
            {
                // Create the singelton instance if it doesn't exist
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }
        
        // Access operator
        const list<shared_ptr<Hexagon>>& operator[](const int index) const;

        // print operator
        friend ostream& operator<<(ostream& os, const Board& board);
};


#endif