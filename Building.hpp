#ifndef BUILDING_H
#define BUILDING_H

#include <string>

using namespace std;

class Building
{
    private:

        int player_id;
        string name;

    public:

        Building(int player_id, string name) : player_id(player_id), name(name){};

        int get_player_id(){return player_id;}

        string get_name(){return name;}

};

class Abode : public Building
{
    private:

        int victory_points;

    public:

        Abode(int player_id, string name, int victory_points) : Building(player_id, name), victory_points(victory_points){};

        int get_victory_points(){return victory_points;}
};

class Settlement : public Abode
{
    public:

        Settlement(int player_id) : Abode(player_id, "Settlement", 1){};
};

class City : public Abode
{
    public:

        City(int player_id) : Abode(player_id, "City", 2){};
};

class Road : public Building
{
    public:

        Road(int player_id) : Building(player_id, "Road"){};
};
#endif