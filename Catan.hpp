#ifndef CATAN_H
#define CATAN_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include "Board.hpp"
#include "Hexagon.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Building.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "General.hpp"


using namespace std;

class GameLogic
{
    private:

        vector<shared_ptr<Player>> players;

        size_t current_player_id = 0;

        shared_ptr<Board> board;

        shared_ptr<Deck> deck;

        static shared_ptr<GameLogic> instance;

        GameLogic();

        int roll_dice() const;

        void settlements() const;

        bool build_road(const string edge_id);

        bool build_settlement(const int vertex_id);

        bool improve_settlement(const int vertex_id);

        bool trade_resources(const int other_player, const string give, const string take);

        bool trade_dev_cards(const int other_player, const string give, const string take);

        void display_help() const;

        void next_turn();

        bool valid_resource(const string resource);

        bool valid_dev(const string dev);

        Player* current_player() const {
            return players[current_player_id].get();
        }

    public:

        static shared_ptr<GameLogic> get_instance()
        {
            struct MakeSharedEnabler : public GameLogic {
                MakeSharedEnabler() : GameLogic(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

        void executeCommand(const string& command);
};

#endif