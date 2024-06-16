#include "Hexagon.hpp"

unordered_map<int, shared_ptr<Hexagon>> Hexagon::hexagon_map;

Hexagon::Hexagon(int id):id(id)
{
    if(id < 1 || id > 19)
    {
        throw invalid_argument("Hexagon id not in valid range");
    }
    
    //Build first row hexagon
    if(id >= 1 && id <= 3)
    {
        //Insert vertices
        int first_vertex = id + (id -1);
        for(int i = first_vertex; i <= first_vertex + 2; i++)
        {
            this->vertices.push_back(Vertex::get_vertex(i));
            this->vertices.push_back(Vertex::get_vertex(i + 8));
        }

        //Insert edges
        for(size_t i = 0; i < 5; i++)
        {
            int current_id = vertices[i].get()->get_id();
            if(i != 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 1);
                this->edges.push_back(Edge::get_edge(edge_id));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 8);
                this->edges.push_back(Edge::get_edge(edge_id));
            }
        }
    }

    //Build second row hexagon
    if(id >= 4 && id <= 7)
    {
        //Insert vertices
        int first_vertex = id + id;
        for(int i = first_vertex; i <= first_vertex + 2; i++)
        {
            this->vertices.push_back(Vertex::get_vertex(i));
            this->vertices.push_back(Vertex::get_vertex(i + 10)); 
        }

        //Insert edges
        for(size_t i = 0; i < 5; i++)
        {
            int current_id = vertices[i].get()->get_id();
            if(i != 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 1);
                this->edges.push_back(Edge::get_edge(edge_id));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 10);
                this->edges.push_back(Edge::get_edge(edge_id));
            }
        }
    }

    //Build third row hexagon
    if(id >= 8 && id <= 12)
    {
        //Insert vertices
        int first_vertex = id + (id +1);
        for(int i = first_vertex; i <= first_vertex + 2; i++)
        {
            this->vertices.push_back(Vertex::get_vertex(i));
            this->vertices.push_back(Vertex::get_vertex(i + 11)); 
        }

        //Insert edges
        for(size_t i = 0; i < 5; i++)
        {
            int current_id = vertices[i].get()->get_id();
            if(i != 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 1);
                this->edges.push_back(Edge::get_edge(edge_id));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 11);
                this->edges.push_back(Edge::get_edge(edge_id));
            }
        }
    }

    //Build fourth row hexagon
    if(id >= 13 && id <= 16)
    {
        //Insert vertices
        int first_vertex = 2*id + 3;
        for(int i = first_vertex; i <= first_vertex + 2; i++)
        {
            this->vertices.push_back(Vertex::get_vertex(i));
            this->vertices.push_back(Vertex::get_vertex(i + 10)); 
        }

        //Insert edges
        for(size_t i = 0; i < 5; i++)
        {
            int current_id = vertices[i].get()->get_id();
            if(i != 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 1);
                this->edges.push_back(Edge::get_edge(edge_id));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 10);
                this->edges.push_back(Edge::get_edge(edge_id));
            }
        }
    }

    //Build fifth row hexagon
    if(id >= 17 && id <= 19)
    {
        //Insert vertices
        int first_vertex = 2*id + 6;
        for(int i = first_vertex; i <= first_vertex + 2; i++)
        {
            this->vertices.push_back(Vertex::get_vertex(i));
            this->vertices.push_back(Vertex::get_vertex(i + 8)); 
        }

        //Insert edges
        for(size_t i = 0; i < 5; i++)
        {
            int current_id = vertices[i].get()->get_id();
            if(i != 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 1);
                this->edges.push_back(Edge::get_edge(edge_id));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 8);
                this->edges.push_back(Edge::get_edge(edge_id));
            }
        }
    }
}

shared_ptr<Hexagon> Hexagon::get_hexagon(int id)
{
    if(id >= 1 && id <= 19){
        struct MakeSharedEnabler : public Hexagon {
            MakeSharedEnabler(int id) : Hexagon(id){}
        };

        if(hexagon_map.find(id) == hexagon_map.end())
        {
            hexagon_map[id] = make_shared<MakeSharedEnabler>(id);
        }
        return hexagon_map[id];
    }
    return nullptr;
}
