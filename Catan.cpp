#include "Catan.hpp"

GameLogic::GameLogic()
{
    players.push_back(Player::get_player(0, RED));
    players.push_back(Player::get_player(1, BLUE));
    players.push_back(Player::get_player(2, ORANGE));

    board = Board::get_instance();

    deck = Deck::get_deck();

}

int GameLogic::roll_dice() const
{
    // Create a random number generator
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(2, 12); 

    int result = dis(gen);
    std::cout << "The roll result was: " << result << "\n";

    return result;
}

void GameLogic::settlements() const
{
    vector<int> player_settlements = (*current_player()).get_settlement_vertices();

    if(player_settlements.size() == 0)
    {
        cout << "Player " << (*current_player()).get_id() << " has no settlements\n";
    }
    else
    {
        cout << "Player " << (*current_player()).get_id() << " has:\n";
        for(int vertex_id : player_settlements)
        {
            if((*Vertex::get_vertex(vertex_id)).get_settlement().get_name() == "Settlement")
            {
                cout << "A settlement on vertex " << (*Vertex::get_vertex(vertex_id)) << "\n";
            }
            else
            {
                cout << "A city on vertex " << (*Vertex::get_vertex(vertex_id)) << "\n";
            }
        }
    }
}

bool GameLogic::build_road(const string edge_id)
{
    shared_ptr<Edge> edge = Edge::get_edge(edge_id);
    if(edge == nullptr){return false;}

    if((*edge).has_road())
    {
        cout << "A road has already been built here";
        return false;
    }
    
    else if(!(*current_player()).can_build_road())
    {
        cout << "You don't have enough resources to build a road";
        return false;
    }
    else
    {
        Player& player = *current_player();
        for(shared_ptr<Vertex> vertex : edge->get_vertices())
        {
            if((*vertex).has_settlement())
            {
                if(player.get_id() == vertex->get_settlement().get_player_id())
                {
                    edge->build_road(player.get_id(), player.get_color());
                    return true;
                }
            }
            else
            {
                for(shared_ptr<Vertex> adj_vertex : vertex->get_adjacent())
                {
                    int min_id, max_id;
                    min_id = min(adj_vertex->get_id(), vertex->get_id());
                    max_id = max(adj_vertex->get_id(), vertex->get_id());

                    string check_edge_id = to_string(min_id) + "-" + to_string(max_id);
                    shared_ptr<Edge> edge_adj = Edge::get_edge(check_edge_id);
                    
                    if(edge_adj->has_road())
                    {
                        if(player.get_id() == edge_adj->get_road().get_player_id())
                        {
                            edge->build_road(player.get_id(), player.get_color());
                            player.add_resources("Wood", -1);
                            player.add_resources("Bricks", -1);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool GameLogic::build_settlement(const int vertex_id)
{
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);
    if(vertex == nullptr){return false;}

    if(vertex->has_settlement())
    {
        cout << "A settlement has already been built here";
        return false;
    }
    else if(!(*current_player()).can_build_settlement())
    {
        cout << "You don't have enough resources to build a settlement";
        return false;
    }
    else
    {
        Player& player = *current_player();
        for(shared_ptr<Vertex> adj_vertex : vertex->get_adjacent())
        {
            if(adj_vertex->has_settlement())
            {
                cout << "There is a settlement adjacent to this vertex, you can't build here\n";
                return false;
            }
        }
        for(shared_ptr<Vertex> adj_vertex : vertex->get_adjacent())
        {
            int min_id, max_id;
            min_id = min(adj_vertex->get_id(), vertex->get_id());
            max_id = max(adj_vertex->get_id(), vertex->get_id());

            string check_edge_id = to_string(min_id) + "-" + to_string(max_id);
            shared_ptr<Edge> edge = Edge::get_edge(check_edge_id);

            if(edge->has_road())
            {
                if(player.get_id() == edge->get_road().get_player_id())
                {
                    player.add_points(vertex->build_settlement(player.get_id(), player.get_color()));
                    player.add_resources("Wood", -1);
                    player.add_resources("Bricks", -1);
                    player.add_resources("Wool", -1);
                    return true;
                }
            }
        }
    }

    return false;
}

bool GameLogic::improve_settlement(const int vertex_id)
{
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);
    if(vertex == nullptr){return false;}

    Player& player = *current_player();

    if(!vertex->has_settlement())
    {
        cout << "There is no settlement here";
        return false;
    }
    else if(player.get_id() != vertex->get_settlement().get_player_id())
    {
        cout << "This settlement belongs to another player";
        return false;
    }
    else if("City" == vertex->get_settlement().get_name())
    {
        cout << "You already built a city here";
        return false;
    }
    else if(!player.can_build_city())
    {
        cout << "You don't have enough resources to build a city";
        return false;
    }
    else
    {
        player.add_points(-1);
        player.add_points(vertex->improve_settlement(player.get_id()));
        player.add_resources("Ore", -3);
        player.add_resources("Grain", -2);
        return true;

    }
    return false;
}

bool GameLogic::trade_resources(const int other_player, const string give, const string take)
{
    Player& player = *current_player();
    if(!valid_resource(give) || !valid_resource(take))
    {
        cout << "The resources are not valid\n";
        return false;
    }
    else if(!player.check_resource(give) || !players[other_player]->check_resource(take))
    {
        cout << "Resources not available\n";
        return false;
    }
    else
    {
        cout << "Do player " << other_player << " agrees to the trade? Y/n\n";

        string other_answer;
        getline(cin ,other_answer);
        
        if(other_answer == "Y")
        {
            player.add_resources(give, -1);
            player.add_resources(take, 1);
            players[other_player]->add_resources(give, 1);
            players[other_player]->add_resources(take, -1);
            return true;
        }
        else if("n")
        {
            cout << "Player " << other_player << " refuses the trade\n";
            return false;
        }
        else
        {
            cout << "Trade failed";
            return false;
        }
    }

}

bool GameLogic::trade_dev_cards(const int other_player, const string give, const string take)
{
    Player& player = *current_player();
    if(!valid_dev(give) || !valid_dev(take))
    {
        cout << "The Development cards are not valid\n";
        return false;
    }
    else if(!player.check_dev(give) || !players[other_player]->check_dev(take))
    {
        cout << "Development cards not available\n";
        return false;
    }
    else
    {
        cout << "Do player " << other_player << " agrees to the trade? Y/n\n";

        string other_answer;
        getline(cin ,other_answer);
        
        if(other_answer == "Y")
        {
            player.add_development_card(players[other_player]->remove_dev_card(take));
            players[other_player]->add_development_card(player.remove_dev_card(give));
            return true;
        }
        else if("n")
        {
            cout << "Player " << other_player << " refuses the trade\n";
            return false;
        }
        else
        {
            cout << "Trade failed";
            return false;
        }
    }
}

void GameLogic::display_help() const
{
    std::cout << "Valid commands:\n"
            << "board\n"
            << "roll\n"
            << "status\n"
            << "settlements\n"
            << "build-road <vertex1#-vertex2# >\n"
            << "build-settlement <vertex#>\n"
            << "improve <vertex#>\n"
            << "trade <id> <give> <take>\n"
            << "trade-dev <id> <give> <take>\n"
            << "buy-dev\n"
            << "devs\n"
            << "play-dev <card (vp, monopoly (card), knight)>\n"
            << "end\n"
            << "help\n";
}

void GameLogic::next_turn()
{
    current_player_id = (current_player_id + 1) % players.size();
    cout << "Player " << current_player_id << "'s turn.\n";
    cout << *players[current_player_id];
}

bool GameLogic::valid_resource(const string resource)
{
    if("Wood" != resource && "Bricks" != resource && "Wool" != resource && "Grain" != resource && "Ore" != resource){return false;}
    return true;
}

bool GameLogic::valid_dev(const string dev)
{
    if("Knight" != dev && "Victory" != dev && "Monopoly" != dev && "Year of plenty" != dev && "Road building" != dev){return false;}
    return true;
}

void GameLogic::executeCommand(const string& command)
{
    if (command == "help") {
            display_help();
    }
    else if (command == "board") {
        cout << *board;
    } 
    else if (command == "roll") {
        roll_dice();
    } 
    else if (command == "status") {
        cout << *current_player();
    }
    else if (command == "settlements") {
        settlements();
    }
    else if (command.find("build-road") == 0) {
        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string edge_id = command.substr(space_pos + 1);
            size_t dash_pos = edge_id.find('-');

            if (dash_pos != std::string::npos) {
                string vertex1Str = edge_id.substr(0, dash_pos);
                string vertex2Str = edge_id.substr(dash_pos + 1);

                try {
                    int vertex1 = std::stoi(vertex1Str);
                    int vertex2 = std::stoi(vertex2Str);

                    // Build the road between the vertices
                    if (build_road(edge_id)) 
                    {
                        std::cout << "Player " << (*current_player()).get_id() << "built a road on edge " << edge_id << "\n";
                    } 
                    else 
                    {
                        std::cout << "Failed to build a road on edge " << edge_id << "\n";
                    }
                } 
                catch (const std::invalid_argument& e) 
                {
                    cout << "Invalid vertex numbers.\n";
                }
            }
            else 
            {
                std::cout << "Invalid command format. Use: build-road <vertex1#-vertex2#>\n";
            }
        }
        else
        {
            cout << "Invalid command format. Use: build-road <vertex1#-vertex2#>\n";
        }
        
    }
    else if (command.find("build-settlement") == 0)
    {
        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string vertex = command.substr(space_pos + 1);
            

            try {
                int vertex_id = std::stoi(vertex);

                // Build the settlement on the vertex
                if (build_settlement(vertex_id)) 
                {
                    std::cout << "Player " << (*current_player()).get_id() << "built a settlement on vertex " << vertex_id << "\n";
                } 
                else 
                {
                    std::cout << "Failed to build a settlement on vertex " << vertex_id<< "\n";
                }
            } 
            catch (const std::invalid_argument& e) 
            {
                cout << "Invalid vertex number.\n";
            }
        }
        else
        {
            cout << "Invalid command format. Use: build-settlement <vertex#>\n";
        }
        
    }
    else if (command.find("improve") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string vertex = command.substr(space_pos + 1);
            

            try {
                int vertex_id = std::stoi(vertex);

                // Build the settlement on the vertex
                if (improve_settlement(vertex_id)) 
                {
                    std::cout << "Player " << (*current_player()).get_id() << "built a city on vertex " << vertex_id << "\n";
                } 
                else 
                {
                    std::cout << "Failed to build a city on vertex " << vertex_id<< "\n";
                }
            } 
            catch (const std::invalid_argument& e) 
            {
                cout << "Invalid vertex number.\n";
            }
        }
        else
        {
            cout << "Invalid command format. Use: improve <vertex#>\n";
        }
    } 
    else if (command.find("trade") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string trade = command.substr(space_pos + 1);
            space_pos = trade.find(' ');
            if(space_pos != -1)
            {
                try
                {
                    int other_id = stoi(trade.substr(0, space_pos));
                    if (other_id < 0 || other_id >= players.size()) 
                    {
                        std::cout << "Invalid player ID. It should be between 0 and " << players.size() - 1 << ".\n";
                        return;
                    }

                    string resources = trade.substr(space_pos + 1);
                    space_pos = resources.find(' ');

                    if(space_pos != -1)
                    {
                        if (trade_resources(other_id, resources.substr(0, space_pos), resources.substr(0, space_pos))) 
                        {
                            std::cout << "Trade successful between player " << current_player_id << " and " << other_id<< ".\n";
                        } 
                    }
                    else
                    {
                        cout << "Invalid command format. Use: trade <id> <give> <take>\n";
                    }

                }
                catch (const std::invalid_argument& e) 
                {
                    std::cout << "Invalid player ID.\n";
                }
            }
            else
            {
                cout << "Invalid command format. Use: trade <id> <give> <take>\n";
            }
        }
        else
        {
            cout << "Invalid command format. Use: trade <id> <give> <take>\n";
        }

    }
    else if (command.find("trade-dev") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string trade = command.substr(space_pos + 1);
            space_pos = trade.find(' ');
            if(space_pos != -1)
            {
                try
                {
                    int other_id = stoi(trade.substr(0, space_pos));
                    if (other_id < 0 || other_id >= players.size()) 
                    {
                        std::cout << "Invalid player ID. It should be between 0 and " << players.size() - 1 << ".\n";
                        return;
                    }

                    string devs = trade.substr(space_pos + 1);
                    space_pos = devs.find(' ');

                    if(space_pos != -1)
                    {
                        if (trade_dev_cards(other_id, devs.substr(0, space_pos), devs.substr(0, space_pos))) 
                        {
                            std::cout << "Trade successful between player " << current_player_id << " and " << other_id<< ".\n";
                        } 
                    }
                    else
                    {
                        cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
                    }

                }
                catch (const std::invalid_argument& e) 
                {
                    std::cout << "Invalid player ID.\n";
                }
            }
            else
            {
                cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
            }
        }
        else
        {
            cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
        }
    }  
    else if (command == "end") {
        next_turn();
    } 
    else {
        std::cout << "Unknown command.\n";
    }
}
