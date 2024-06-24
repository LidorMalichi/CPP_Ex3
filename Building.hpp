#ifndef BUILDING_H
#define BUILDING_H

#include <string>

using namespace std;

class Building
{
    private:

        size_t player_id;
        string name;

    public:

        Building(size_t player_id, string name) : player_id(player_id), name(name){};

        const  size_t get_player_id(){return player_id;}

        const string get_name(){return name;}

};

class Abode : public Building
{
    private:

        int victory_points;

    public:

        Abode(size_t player_id, string name, int victory_points) : Building(player_id, name), victory_points(victory_points){};

        int get_victory_points(){return victory_points;}
};

class Settlement : public Abode
{
    public:

        Settlement(size_t player_id) : Abode(player_id, "Settlement", 1){};
};

class City : public Abode
{
    public:

        City(size_t player_id) : Abode(player_id, "City", 2){};
};

class Road : public Building
{
    public:

        Road(size_t player_id) : Building(player_id, "Road"){};
};
#endif