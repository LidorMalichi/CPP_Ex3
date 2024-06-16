#ifndef HEXAGON_H
#define HEXAGON_H

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Card.hpp"
#include <vector>


class Hexagon{

    private:
        int id;
        int board_id;
        shared_ptr<Tile> tile;
        vector<shared_ptr<Vertex>> vertices;
        vector<shared_ptr<Edge>>edges;

        static unordered_map<int, shared_ptr<Hexagon>> hexagon_map;

        Hexagon(int id);

    public:

        static shared_ptr<Hexagon> get_hexagon(int id);

        vector<shared_ptr<Vertex>> get_vertices(){return this->vertices;}

        vector<shared_ptr<Edge>> get_edges(){return this->edges;}



};

#endif