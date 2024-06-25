#ifndef HEXAGON_H
#define HEXAGON_H

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Card.hpp"
#include <vector>
#include <iostream>

// A class that represents a hexagon on the board 
class Hexagon{

    private:

        // Hex id
        int id;
        // hex board id for the dices roll
        int board_id;
        // Tile that represents the land
        shared_ptr<Tile> tile;
        // Hex vertices
        vector<shared_ptr<Vertex>> vertices;
        // Hex edges
        vector<shared_ptr<Edge>>edges;
        // A map of all hexagons
        static unordered_map<int, shared_ptr<Hexagon>> hexagon_map;

        Hexagon(int id, int board_id, shared_ptr<Tile> tile);

    public:

        // Get the hexagon from the map
        static shared_ptr<Hexagon> get_hexagon(int id, int board_id = 0, shared_ptr<Tile> tile = nullptr);

        // Get the hex vertices
        vector<shared_ptr<Vertex>> get_vertices() const {return this->vertices;}

        // Get the hex edges
        vector<shared_ptr<Edge>> get_edges() const {return this->edges;}

        // Get the resource from the land tile
        string get_resource() const {return tile->get_resource();}

        // print operator
        friend ostream& operator<<(ostream& os, const Hexagon& hexagon);

};

#endif