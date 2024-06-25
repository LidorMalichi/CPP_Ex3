#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Vertex.hpp"
#include "Building.hpp"
#include "General.hpp"

using namespace std;

class Edge{

    private:

        // Edge id
        string id;

        // Edge form for printing
        string form;

        // Edge color
        string color;

        // Edge vertices
        vector<shared_ptr<Vertex>> vertices;

        // Edge road
        shared_ptr<Road> road;

        // Edge map
        static unordered_map<string, shared_ptr<Edge>> edge_map;

        // Edge id repository
        static vector<string> edge_ids;

        Edge(const string id, const string form);

    public:

        // Get the edge
        static shared_ptr<Edge> get_edge(const string id, const string form = "");

        // Check if edge id is valid
        static bool valid_edge(const string edge_id);

        // Returns the edge id
        string get_id(){return this->id;}

        // Get the edge vertices
        vector<shared_ptr<Vertex>> get_vertices(){return this->vertices;}

        // Returns true if a road was built on the edge
        bool has_road(){return road != nullptr;}

        // Gets the road on the edge
        Road& get_road(){return *this->road;}

        // Builds a road on the edge
        void build_road(int player_id, string color)
        {
            this->road = make_shared<Road>(player_id);
            this->color = color;
        }

        // print operator
        friend ostream& operator<<(ostream& os, const Edge& edge);
};

#endif