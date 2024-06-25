#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include "Building.hpp"
#include "General.hpp"

using namespace std;

// A vertex class that represents an intersection in the game
class Vertex{
    
    private:

        // Vertex id
        int id;

        // Vertex print format
        string description;

        // Vertex color format
        string color;

        // Vertex neighbors 
        vector<shared_ptr<Vertex>> adjacent_vertices;

        // Vertex settlement/city
        unique_ptr<Abode> abode;

        // Vertices map
        static unordered_map<int, shared_ptr<Vertex>> vertex_map;

        Vertex(int id): id(id)
        {
            if(id < 10){description = "0" + to_string(id);}
            else{description = to_string(id);}

            // Initiate every vertex color to white 
            color = "\033[0m";
        }

    public:

        // Get vertex by id 
        static shared_ptr<Vertex> get_vertex(int id);

        // Add neighbor vertex to neighbors
        void add_adjacent(shared_ptr<Vertex> adj_vertex);

        // Get vertex id
        int get_id(){return this->id;}

        // Returns true if a settlement was built on the vertex
        bool has_settlement() const {return abode != nullptr;}

        // Get the settlement on the vertex
        Abode& get_settlement() const {return *abode;}

        // Build a settlement on the vertex
        int build_settlement(int player_id, string color);

        // Improve settlement to city
        int improve_settlement(int player_id);

        // Get the neighbors
        vector<shared_ptr<Vertex>> get_adjacent() const {return this->adjacent_vertices;}

        // Print operator
        friend ostream& operator<<(ostream& os, const Vertex& vertex);

};

#endif
