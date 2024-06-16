#include "doctest.h"
#include "Card.hpp"
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Hexagon.hpp"
#include "Board.hpp"

#include <string>
#include <memory>

using namespace std;

TEST_CASE("Check Resource cards and basic ploymorphism"){

    ResourceCard* card = new Wood();
    CHECK(card->resource_type() == WOOD);

    delete card;

    card = new Bricks();
    CHECK(card->resource_type() == BRICKS);

    delete card;

    card = new Wool();
    CHECK(card->resource_type() == WOOL);

    delete card;

    card = new Grain();
    CHECK(card->resource_type() == GRAIN);

    delete card;

    card = new Ore();
    CHECK(card->resource_type() == ORE);

    delete card;

}

TEST_CASE("check Tile Factory and Shared_ptr auto memory managment"){

    
    shared_ptr<Tile> ptr1;
    {
        auto ptr2 = TileFactory::get_tile("Forest");
        ptr1 = ptr2;
        CHECK(ptr2.use_count() == 3);
        
    }
    CHECK(ptr1.use_count() == 2);

    ptr1.reset();
    CHECK(ptr1.use_count() == 0);
}

TEST_CASE("check get_vertex()"){

    shared_ptr<Vertex> ptr1;
    {
        ptr1 = Vertex::get_vertex(1);
    }
    shared_ptr<Vertex> ptr2 = Vertex::get_vertex(1);
    CHECK(ptr1.use_count() == 3);
}

TEST_CASE("check get_edge()"){

    shared_ptr<Edge> ptr1;
    {
        ptr1 = Edge::get_edge("1-9");
    }
    shared_ptr<Edge> ptr2 = Edge::get_edge("1-9");
    CHECK(ptr1.use_count() == 3);
}

TEST_CASE("check get_hexagon()")
{
    shared_ptr<Hexagon> ptr1;
    {
        ptr1 = Hexagon::get_hexagon(1);
    }
    shared_ptr<Hexagon> ptr2 = Hexagon::get_hexagon(1);

    Hexagon* hex1 = ptr1.get();
    for(shared_ptr<Vertex> ptr : hex1->get_vertices())
    {
        cout << ptr.get()->get_id() <<endl;
    }

    for(shared_ptr<Edge> ptr : hex1->get_edges())
    {
        cout << ptr.get()->get_id() <<endl;
    }
    CHECK(ptr1.use_count() == 3);


    ptr1.reset();
    ptr1 = Hexagon::get_hexagon(4);

    Hexagon* hex2 = ptr1.get();
    for(shared_ptr<Vertex> ptr : hex2->get_vertices())
    {
        cout << ptr.get()->get_id() <<endl;
    }

    for(shared_ptr<Edge> ptr : hex2->get_edges())
    {
        cout << ptr.get()->get_id() <<endl;
    }
}

TEST_CASE("check board constructor")
{
    shared_ptr<Board> board = Board::get_instance();
}