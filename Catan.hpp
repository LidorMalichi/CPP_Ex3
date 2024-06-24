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

        size_t greatest_army_id;

        int winner_id = -1;

        shared_ptr<Board> board;

        shared_ptr<Deck> deck;

        static shared_ptr<GameLogic> instance;

        GameLogic();

        void init();

        bool can_build_settlement_init(const int vertex_id);     

        void roll_dice();

        void give_out_resources(const int roll_result);

        void lose_resources();

        void settlements() const;

        bool can_build_road(const string edge_id);

        void build_road(const string edge_id);

        bool can_build_settlement(const int vertex_id);

        void build_settlement(const int vertex_id);

        bool improve_settlement(const int vertex_id);

        bool trade_resources(const size_t other_player, const string give, const string take);

        bool trade_dev_cards(const size_t other_player, const string give, const string take);

        bool buy_dev_card();

        void show_dev_cards() const;

        void play_knight();

        void play_victory();

        bool play_year_of_plenty(const string first_resource, const string second_resource);

        bool play_monopoly(const string resource);

        bool play_road_building(const string first_edge, const string second_edge);

        bool play_dev(const string card);

        void display_help() const;

        void next_turn();

        bool valid_resource(const string resource);

        bool valid_dev(const string dev);

        Player* current_player() const {
            return players[current_player_id].get();
        }

    public:

        int get_winner_id() const {return this->winner_id;}

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