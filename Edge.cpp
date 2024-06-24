#include "Edge.hpp"

unordered_map<string, shared_ptr<Edge>> Edge::edge_map;

vector<string> Edge::edge_ids = {"1-2","1-9","9-10","2-3","10-11","3-11","3-4","11-12","4-5","12-13","5-13","5-6","13-14","6-7","14-15","7-15",
                                "8-9","8-18","18-19","19-20","10-20","20-21","21-22","12-22","22-23","23-24","14-24","24-25","15-16","25-26","16-26",
                                "17-18","17-28","28-29","29-30","19-30","30-31","31-32","21-32","32-33","33-34","23-34","34-35","35-36","25-36","36-37",
                                "37-38","27-38","29-39","39-40","40-41","31-41","41-42","42-43","33-43","43-44","44-45","35-45","45-46","46-47","37-47",
                                "40-48","48-49","49-50","42-50","50-51","51-52","44-52","52-53","53-54","46-54"};

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
    if(valid_edge(id))
    {
        if(edge_map.find(id) == edge_map.end())
        {
            edge_map[id] = make_shared<MakeSharedEnabler>(id, form);
        }
        return edge_map[id];
    }
    return nullptr;
}

bool Edge::valid_edge(const string edge_id)
{
    for(string id : edge_ids)
    {
        if(id == edge_id){return true;}
    }
    return false;
}

ostream &operator<<(ostream &os, const Edge &edge)
{
    os << edge.color << edge.form;
    return os;
}
