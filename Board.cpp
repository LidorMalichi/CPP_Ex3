#include "Board.hpp"

shared_ptr<Board> Board::instance;

Board::Board()
{
    vector<int> board_ids = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    vector<int> hex_ids = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    random_device rd;
    mt19937 g(rd());
    shuffle(board_ids.begin(), board_ids.end(), g);
    shuffle(hex_ids.begin(), hex_ids.end(), g);


    
    for(size_t i = 0; i <= 3; i++)
    {
        shared_ptr<Tile> forest_ptr = TileFactory::get_tile("Forest");

        shared_ptr<Hexagon> hex = Hexagon::get_hexagon(hex_ids[i], board_ids[i], forest_ptr);

        if(this->layout.find(board_ids[i]) == this->layout.end())
        {
            list<shared_ptr<Hexagon>> new_list = {hex};
            this->layout[board_ids[i]] = new_list;
        }
        else
        {
            this->layout[board_ids[i]].push_back(hex);
        }
    }

    for(size_t i = 4; i <= 6; i++)
    {
        shared_ptr<Tile> hills_ptr = TileFactory::get_tile("Hills");

        shared_ptr<Hexagon> hex = Hexagon::get_hexagon(hex_ids[i], board_ids[i], hills_ptr);

        if(this->layout.find(board_ids[i]) == this->layout.end())
        {
            list<shared_ptr<Hexagon>> new_list = {hex};
            this->layout[board_ids[i]] = new_list;
        }
        else
        {
            this->layout[board_ids[i]].push_back(hex);
        }
    }

    for(size_t i = 7; i <= 10; i++)
    {
        shared_ptr<Tile> pasture_ptr = TileFactory::get_tile("Pasture");

        shared_ptr<Hexagon> hex = Hexagon::get_hexagon(hex_ids[i], board_ids[i], pasture_ptr);

        if(this->layout.find(board_ids[i]) == this->layout.end())
        {
            list<shared_ptr<Hexagon>> new_list = {hex};
            this->layout[board_ids[i]] = new_list;
        }
        else
        {
            this->layout[board_ids[i]].push_back(hex);
        }
    }

    for(size_t i = 11; i <= 14; i++)
    {
        shared_ptr<Tile> fields_ptr = TileFactory::get_tile("Fields");

        shared_ptr<Hexagon> hex = Hexagon::get_hexagon(hex_ids[i], board_ids[i], fields_ptr);

        if(this->layout.find(board_ids[i]) == this->layout.end())
        {
            list<shared_ptr<Hexagon>> new_list = {hex};
            this->layout[board_ids[i]] = new_list;
        }
        else
        {
            this->layout[board_ids[i]].push_back(hex);
        }
    }

    for(size_t i = 15; i <= 17; i++)
    {
        shared_ptr<Tile> mountains_ptr = TileFactory::get_tile("Mountains");

        shared_ptr<Hexagon> hex = Hexagon::get_hexagon(hex_ids[i], board_ids[i], mountains_ptr);

        if(this->layout.find(board_ids[i]) == this->layout.end())
        {
            list<shared_ptr<Hexagon>> new_list = {hex};
            this->layout[board_ids[i]] = new_list;
        }
        else
        {
            this->layout[board_ids[i]].push_back(hex);
        }
    }

    shared_ptr<Tile> desert_ptr = TileFactory::get_tile("Desert");
    shared_ptr<Hexagon> hex = Hexagon::get_hexagon(10, 7, desert_ptr);
    this->layout[7] = {hex};

}

ostream& operator<<(ostream& os, const Board& board)
{
    
}