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

TEST_CASE("check board constructor")
{
    shared_ptr<Board> board = Board::get_instance();
    cout << *board << endl;
}

TEST_CASE("Check Resource cards and basic ploymorphism"){

}

TEST_CASE("check Tile Factory and Shared_ptr auto memory managment"){

    
    shared_ptr<Tile> ptr1;
    {
        auto ptr2 = TileFactory::get_tile("Forest");
        ptr1 = ptr2;
        CHECK(ptr2.use_count() == 7);
        
    }
    CHECK(ptr1.use_count() == 6);
}

TEST_CASE("check get_vertex()"){

    shared_ptr<Vertex> ptr1;
    {
        ptr1 = Vertex::get_vertex(1);
    }
    shared_ptr<Vertex> ptr2 = Vertex::get_vertex(1);
    CHECK(ptr1.use_count() == 8);
}

TEST_CASE("check get_edge()"){

    shared_ptr<Edge> ptr1;
    {
        ptr1 = Edge::get_edge("1-9");
    }
    shared_ptr<Edge> ptr2 = Edge::get_edge("1-9");
    CHECK(ptr1.use_count() == 4);
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
    CHECK(ptr1.use_count() == 4);


    
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

TEST_CASE("check hexagon <<")
{
    shared_ptr<Hexagon> ptr = Hexagon::get_hexagon(1);
    cout << *ptr;
    cout << "\n";
}

