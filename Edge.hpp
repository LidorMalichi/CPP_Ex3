#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Vertex.hpp"
#include "Building.hpp"

using namespace std;

class Edge{

    private:

        string id;

        string form;

        string color;

        vector<shared_ptr<Vertex>> vertices;

        shared_ptr<Road> road;

        static unordered_map<string, shared_ptr<Edge>> edge_map;

        Edge(const string id, const string form);

    public:

        static shared_ptr<Edge> get_edge(const string id, const string form = "");

        string get_id(){return this->id;}

        vector<shared_ptr<Vertex>> get_vertices(){return this->vertices;}

        bool has_road(){return road != nullptr;}

        Road& get_road(){return *this->road;}

        void build_road(int player_id, string color)
        {
            this->road = make_shared<Road>(player_id);
            this->color = color;
        }

        friend ostream& operator<<(ostream& os, const Edge& edge);
};

#endif