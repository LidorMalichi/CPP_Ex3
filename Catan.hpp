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

// Game Logic class
class GameLogic
{
    private:

        // Players vector
        vector<shared_ptr<Player>> players;

        // Current player id
        size_t current_player_id = 0;

        // Indicates if current player rolled the dices
        bool rolled = false;

        // Current player color
        string current_color = RED;

        // Id of player with greatest army
        size_t greatest_army_id;

        // Id of winner
        int winner_id = -1;

        // Board singelton instance
        shared_ptr<Board> board;

        // Deck singelton instance
        shared_ptr<Deck> deck;

        // Static game logic instance
        static shared_ptr<GameLogic> instance;

        GameLogic();

        // Init function for the first builds
        void init();

        // Checks if str contains only digits
        bool is_only_digits(const string& str);

        // Returns true if a player can build an initial settlement
        bool can_build_settlement_init(const int vertex_id);     

        // A function to roll the dices
        void roll_dice();

        // Give resources to players according to the dices result
        void give_out_resources(const int roll_result);

        // Take  half of the resources from players with more than 7 resources
        void lose_resources();

        // prints the locations of the player's settlements
        void settlements() const;

        // Returns true if the player can build a road on the edge
        bool can_build_road(const string edge_id);

        // Builds a road on the edge
        void build_road(const string edge_id);

        // Returns true if a player can build a settlement on the vertex
        bool can_build_settlement(const int vertex_id);

        // Builds a settlement on the vertex
        void build_settlement(const int vertex_id);

        // Builds a city on the vertex
        bool improve_settlement(const int vertex_id);

        // Trades resources betweeen players
        bool trade_resources(const size_t other_player, const string give, const string take);

        // Trades dev cards between players
        bool trade_dev_cards(const size_t other_player, const string give, const string take);

        // Buys dev card
        bool buy_dev_card();

        // Shows players dev cards
        void show_dev_cards() const;

        // Plays knight dev card
        void play_knight();

        // Plays victory dev card
        void play_victory();

        // Plays year of plenty dev card
        bool play_year_of_plenty(const string first_resource, const string second_resource);

        // Plays monopoly dev card
        bool play_monopoly(const string resource);

        // Plays road building dev card
        bool play_road_building(const string first_edge, const string second_edge);

        // Wrapper function to play dev cards
        bool play_dev(const string card);

        // Displays available commands
        void display_help() const;

        // Calculates next turn
        void next_turn();

        // Checks if string is a valid resource
        bool valid_resource(const string resource);

        // Checks if string is a valid dev card
        bool valid_dev(const string dev);

        // Returns current player pointer
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

        // Executes command
        void executeCommand(const string& command);
};

#endif