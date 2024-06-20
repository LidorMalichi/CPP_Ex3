#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include "Building.hpp"

using namespace std;

class Vertex{
    
    private:
        int id;

        vector<shared_ptr<Vertex>> adjacent_vertices;

        unique_ptr<Abode> abode;

        static unordered_map<int, shared_ptr<Vertex>> vertex_map;

        Vertex(int id): id(id){}

    public:

        static shared_ptr<Vertex> get_vertex(int id);

        void add_adjacent(shared_ptr<Vertex> adj_vertex);

        int get_id(){return this->id;}

        bool has_settlement(){return abode == nullptr;}

        int build_settlement(int player_id);

        int improve_settlement(int player_id);

        friend ostream& operator<<(ostream& os, const Vertex& vertex);

};

#endif
