#ifndef PLAYER_H
#define PLAYER_H

#include "Card.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

class Player
{
    private:

        int id;
        int points;
        unordered_map<int, int> resources;
        vector<unique_ptr<DevCard>> hand;

};

#endif