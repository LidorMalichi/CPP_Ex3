#include "Hexagon.hpp"

unordered_map<int, shared_ptr<Hexagon>> Hexagon::hexagon_map;

Hexagon::Hexagon(int id, int board_id, shared_ptr<Tile> tile):id(id), board_id(board_id), tile(tile)
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
                string edge_form;
                switch (i)
                {
                case 0:
                    edge_form = "/ ";
                    break;
                case 1:
                    edge_form = " \\";
                    break;
                case 2:
                    edge_form = " \\";
                    break;
                case 3:
                    edge_form = "/ ";
                    break;
                }
                this->edges.push_back(Edge::get_edge(edge_id, edge_form));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 8);
                this->edges.push_back(Edge::get_edge(edge_id, "||"));
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
                string edge_form;
                switch (i)
                {
                case 0:
                    edge_form = "/ ";
                    break;
                case 1:
                    edge_form = " \\";
                    break;
                case 2:
                    edge_form = " \\";
                    break;
                case 3:
                    edge_form = "/ ";
                    break;
                }
                this->edges.push_back(Edge::get_edge(edge_id, edge_form));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 10);
                this->edges.push_back(Edge::get_edge(edge_id, "||"));
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
                string edge_form;
                switch (i)
                {
                case 0:
                    edge_form = "/ ";
                    break;
                case 1:
                    edge_form = " \\";
                    break;
                case 2:
                    edge_form = " \\";
                    break;
                case 3:
                    edge_form = "/ ";
                    break;
                }
                this->edges.push_back(Edge::get_edge(edge_id, edge_form));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 11);
                this->edges.push_back(Edge::get_edge(edge_id, "||"));
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
                string edge_form;
                switch (i)
                {
                case 0:
                    edge_form = "/ ";
                    break;
                case 1:
                    edge_form = " \\";
                    break;
                case 2:
                    edge_form = " \\";
                    break;
                case 3:
                    edge_form = "/ ";
                    break;
                }
                this->edges.push_back(Edge::get_edge(edge_id, edge_form));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 10);
                this->edges.push_back(Edge::get_edge(edge_id, "||"));
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
                string edge_form;
                switch (i)
                {
                case 0:
                    edge_form = "/ ";
                    break;
                case 1:
                    edge_form = " \\";
                    break;
                case 2:
                    edge_form = " \\";
                    break;
                case 3:
                    edge_form = "/ ";
                    break;
                }
                this->edges.push_back(Edge::get_edge(edge_id, edge_form));
        
            }
            if(i == 0 || i == 4)
            {
                string edge_id = to_string(current_id) + "-" + to_string(current_id + 8);
                this->edges.push_back(Edge::get_edge(edge_id, "||"));
            }
        }
    }
}

shared_ptr<Hexagon> Hexagon::get_hexagon(int id, int board_id, shared_ptr<Tile> tile)
{
    // checks if the hex id is valid   
    if(id >= 1 && id <= 19){
        // A struct that gets access to private constructor
        struct MakeSharedEnabler : public Hexagon {
            MakeSharedEnabler(int id, int board_id, shared_ptr<Tile> tile) : Hexagon(id, board_id, tile){}
        };

        if(hexagon_map.find(id) == hexagon_map.end())
        {
            // Create a hex if it doesn't exist
            hexagon_map[id] = make_shared<MakeSharedEnabler>(id, board_id, tile);
        }
        return hexagon_map[id];
    }
    return nullptr;
}

ostream &operator<<(ostream &os, const Hexagon &hexagon)
{
    os << hexagon.tile->land() << "(";
    os << (hexagon.board_id > 9 ? to_string(hexagon.board_id) : "0" + to_string(hexagon.board_id));
    os << ")";
    return os;
}
