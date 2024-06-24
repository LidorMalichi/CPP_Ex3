#include "Catan.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    GameLogic game_logic = *GameLogic::get_instance();

    string command;

    while(game_logic.get_winner_id() == -1)
    {
        std::cout << ">\n";
        getline(cin, command);

        game_logic.executeCommand(command);
    }
    std::cout << "The winner is player " << game_logic.get_winner_id() << "\n";

    return 0;
}