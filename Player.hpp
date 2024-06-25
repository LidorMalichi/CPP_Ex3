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

// A class that represnts a player in the game
class Player
{
    private:

        // Player's id
        size_t id;

        // Player's color
        string color;

        // Player's points
        int points;

        // Player's army
        int activated_knights;

        // Player's total number of resources
        int num_of_resources;

        // Player's resource map
        unordered_map<string, int> resources;

        // Player's development cards 
        vector<unique_ptr<DevCard>> hand;

        // Player's settlements locations
        vector<int> settlement_vertices;

        // Players vector
        static vector<shared_ptr<Player>> players;

        Player(size_t id, string color, int points) : id(id), color(color), points(points)
        {
            // Initialize resources for the init
            resources["Wood"] = 4;
            resources["Bricks"] = 4;
            resources["Wool"] = 2;
            resources["Grain"] = 2;
            resources["Ore"] = 0;
            activated_knights = 0;
            num_of_resources = 12;
        }

    public:

        // Get player from players vector
        static shared_ptr<Player> get_player(size_t id, string color)
        {
            // A struct that gets access to private constructor 
            struct MakeSharedEnabler : public Player {
                MakeSharedEnabler(size_t id, string color) : Player(id, color, 0){}
            };

            if(players[id] == nullptr)
            {
                // Create a player if it doesn't exist
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

        // Checks if the player has enough resources to build a road
        bool can_build_road() const;

        // Checks if the player has enough resources to build a settlement
        bool can_build_settlement() const ;

        // Checks if the player has enough resources to build a city
        bool can_build_city() const;

        // Checks if the player has enough resources to buy a development card
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

        // print operator
        friend ostream& operator<<(ostream& os, const Player& player);

};

#endif