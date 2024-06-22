#ifndef PLAYER_H
#define PLAYER_H

#include "Card.hpp"
#include "General.hpp"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Player
{
    private:

        int id;

        string color;

        int points;

        unordered_map<string, int> resources;

        vector<unique_ptr<DevCard>> hand;

        vector<int> settlement_vertices;

        static vector<shared_ptr<Player>> players;

        Player(int id, string color, int points) : id(id), color(color), points(points)
        {
            resources["Wood"] = 0;
            resources["Bricks"] = 0;
            resources["Wool"] = 0;
            resources["Grain"] = 0;
            resources["Ore"] = 0;
        }

    public:

        static shared_ptr<Player> get_player(int id, string color)
        {
            struct MakeSharedEnabler : public Player {
                MakeSharedEnabler(int id, string color) : Player(id, color, 0){}
            };

            if(!players[id])
            {
                players[id] = make_shared<MakeSharedEnabler>();
            }
            return players[id];
        }

        int get_id(){return this->id;}

        string get_color(){return this->color;}

        int get_points(){return this->points;}

        void add_points(int points_to_add){this->points += points_to_add;}

        void add_settlement_vertex(int vertex_id){this->settlement_vertices.push_back(vertex_id);}

        void add_development_card(unique_ptr<DevCard> card);

        unique_ptr<DevCard> remove_dev_card(const string dev);

        vector<int> get_settlement_vertices(){return this->settlement_vertices;}

        bool can_build_road();

        bool can_build_settlement();

        bool can_build_city();

        void add_resources(string resource, int units);

        bool check_resource(const string resource){this->resources[resource] > 0;}\

        bool check_dev(const string dev);

        friend ostream& operator<<(ostream& os, const Player& player);

};

#endif