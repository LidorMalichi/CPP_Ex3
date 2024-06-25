#ifndef BUILDING_H
#define BUILDING_H

#include <string>

using namespace std;

// A base class that represents a building
class Building
{
    private:

        // Player id
        size_t player_id;
        // Building name
        string name;

    public:

        Building(size_t player_id, string name) : player_id(player_id), name(name){};

        const  size_t get_player_id(){return player_id;}

        const string get_name(){return name;}

};

// Base class for reprsenting an abode = Settlement/City
class Abode : public Building
{
    private:

        // Victopry pints give by specific abode
        int victory_points;

    public:

        Abode(size_t player_id, string name, int victory_points) : Building(player_id, name), victory_points(victory_points){};

        int get_victory_points(){return victory_points;}
};

// Settlement class
class Settlement : public Abode
{
    public:

        Settlement(size_t player_id) : Abode(player_id, "Settlement", 1){};
};

// City class
class City : public Abode
{
    public:

        City(size_t player_id) : Abode(player_id, "City", 2){};
};

// Road class
class Road : public Building
{
    public:

        Road(size_t player_id) : Building(player_id, "Road"){};
};
#endif