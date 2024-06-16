#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <memory>
#include "Vertex.hpp"
#include <string>
#include <stdexcept>
using namespace std;

class Edge{

    private:
        string id;
        vector<shared_ptr<Vertex>> vertices;

        static unordered_map<string, shared_ptr<Edge>> edge_map;

        Edge(const string id);

    public:

        static shared_ptr<Edge> get_edge(const string id);

        string get_id(){return this->id;}
};

#endif