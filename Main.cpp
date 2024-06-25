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
        std::cout << ">";
        getline(cin, command);

        if(command == "close")
        {
            return 0;
        }

        game_logic.executeCommand(command);
    }
    std::cout << "The winner is player " << game_logic.get_winner_id() << "\n";

    return 0;
}
