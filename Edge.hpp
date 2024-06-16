#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <memory>
#include "Vertex.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class Edge{

    private:
        string id;
        string form;
        vector<shared_ptr<Vertex>> vertices;

        static unordered_map<string, shared_ptr<Edge>> edge_map;

        Edge(const string id, const string form);

    public:

        static shared_ptr<Edge> get_edge(const string id, const string form = "");

        string get_id(){return this->id;}

        friend ostream& operator<<(ostream& os, const Edge& edge);
};

#endif