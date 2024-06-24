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

        string description;

        string color;

        vector<shared_ptr<Vertex>> adjacent_vertices;

        unique_ptr<Abode> abode;

        static unordered_map<int, shared_ptr<Vertex>> vertex_map;

        Vertex(int id): id(id)
        {
            if(id < 10){description = "0" + to_string(id);}
            else{description = to_string(id);}

            color = "\033[0m";
        }

    public:

        static shared_ptr<Vertex> get_vertex(int id);

        void add_adjacent(shared_ptr<Vertex> adj_vertex);

        int get_id(){return this->id;}

        bool has_settlement() const {return abode != nullptr;}

        Abode& get_settlement() const {return *abode;}

        int build_settlement(int player_id, string color);

        int improve_settlement(int player_id);

        vector<shared_ptr<Vertex>> get_adjacent() const {return this->adjacent_vertices;}

        friend ostream& operator<<(ostream& os, const Vertex& vertex);

};

#endif
