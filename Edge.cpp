#include "Edge.hpp"

unordered_map<string, shared_ptr<Edge>> Edge::edge_map;

Edge::Edge(const string id, const string form): id(id), form(form)
{
    size_t seperator = id.find('-');
        if (seperator == string::npos) {
            throw invalid_argument("Invalid edge format");
        }

        string startStr = id.substr(0, seperator);
        string endStr = id.substr(seperator + 1);
            
        vertices.push_back(Vertex::get_vertex(stoi(startStr)));
        vertices.push_back(Vertex::get_vertex(stoi(endStr)));

        vertices[0].get()->add_adjacent(vertices[1]);
        vertices[1].get()->add_adjacent(vertices[0]);

        color = "\033[0m";
}

shared_ptr<Edge> Edge::get_edge(const string id, const string form)
{
    struct MakeSharedEnabler : public Edge {
                MakeSharedEnabler(const string id, const string form) : Edge(id, form){}
            };

    if(edge_map.find(id) == edge_map.end())
    {
        edge_map[id] = make_shared<MakeSharedEnabler>(id, form);
    }
    return edge_map[id];
}

ostream &operator<<(ostream &os, const Edge &edge)
{
    os << edge.color << edge.form;
    return os;
}
