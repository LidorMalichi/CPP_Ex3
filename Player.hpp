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

        size_t id;

        string color;

        int points;

        int activated_knights;

        int num_of_resources;

        unordered_map<string, int> resources;

        vector<unique_ptr<DevCard>> hand;

        vector<int> settlement_vertices;

        static vector<shared_ptr<Player>> players;

        Player(size_t id, string color, int points) : id(id), color(color), points(points)
        {
            resources["Wood"] = 4;
            resources["Bricks"] = 4;
            resources["Wool"] = 2;
            resources["Grain"] = 2;
            resources["Ore"] = 0;
            activated_knights = 0;
            num_of_resources = 12;
        }

    public:

        static shared_ptr<Player> get_player(size_t id, string color)
        {
            struct MakeSharedEnabler : public Player {
                MakeSharedEnabler(size_t id, string color) : Player(id, color, 0){}
            };

            if(!players[id])
            {
                players[id] = make_shared<MakeSharedEnabler>(id, color);
            }
            return players[id];
        }

        size_t get_id(){return this->id;}

        string get_color(){return this->color;}

        int get_points(){return this->points;}

        void add_points(int points_to_add){this->points += points_to_add;}

        void add_settlement_vertex(int vertex_id){this->settlement_vertices.push_back(vertex_id);}

        void add_development_card(unique_ptr<DevCard> card);

        unique_ptr<DevCard> remove_dev_card(const string dev);

        vector<int> get_settlement_vertices(){return this->settlement_vertices;}

        bool can_build_road() const;

        bool can_build_settlement() const ;

        bool can_build_city() const;

        bool can_buy_dev() const;

        void add_resources(string resource, int units);

        int get_resource_num(const string resource) const {return this->resources.at(resource);}

        bool check_resource(const string resource) const {return this->resources.at(resource) > 0;}

        bool check_dev(const string dev) const ;

        void show_hand () const;

        int get_activated_knights() const {return this->activated_knights;}

        int get_num_of_resources() const {return this->num_of_resources;}

        void activate_knight();

        void activate_victory();

        friend ostream& operator<<(ostream& os, const Player& player);

};

#endif