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

int Vertex::build_settlement(int player_id, string color)
{
    abode = make_unique<Settlement>(player_id);
    this->color = color;
    return (*abode).get_victory_points();
}

int Vertex::improve_settlement(int player_id)
{
    abode.reset();
    abode = make_unique<City>(player_id);
    return (*abode).get_victory_points();     
}

ostream& operator<<(ostream& os, const Vertex& vertex)
{ 
    os << vertex.color << vertex.description;
    return os;
}