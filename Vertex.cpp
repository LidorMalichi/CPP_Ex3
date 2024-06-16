#include "Vertex.hpp"

unordered_map<int, shared_ptr<Vertex>> Vertex::vertex_map;

shared_ptr<Vertex> Vertex::get_vertex(int id)
{
    if(id >= 1 && id <= 54){
        struct MakeSharedEnabler : public Vertex {
            MakeSharedEnabler(int id) : Vertex(id){}
        };

        if(vertex_map.find(id) == vertex_map.end())
        {
            vertex_map[id] = make_shared<MakeSharedEnabler>(id);
        }
        return vertex_map[id];
    }
    return nullptr;
}

void Vertex::add_adjacent(shared_ptr<Vertex> adj_vertex)
{
    this->adjacent_vertices.push_back(adj_vertex);
}

ostream& operator<<(ostream& os, const Vertex& vertex)
{
    if(vertex.id < 10){os << "0" ;}
    os << to_string(vertex.id);
    return os;
}