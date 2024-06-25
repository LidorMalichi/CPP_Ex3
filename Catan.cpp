#include "Catan.hpp"

shared_ptr<GameLogic> GameLogic::instance;

GameLogic::GameLogic()
{
    players.push_back(Player::get_player(0, RED));
    players.push_back(Player::get_player(1, BLUE));
    players.push_back(Player::get_player(2, ORANGE));

    greatest_army_id = 3;

    board = Board::get_instance();

    deck = Deck::get_deck();

    init();

}

void GameLogic::init()
{
    std::cout << *this->board;
    
    
    for(size_t i = 0; i < players.size(); i++)
    {
        current_player_id = i;
        std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " choose your first settlement based on the vertex#\n";
        string answer;
        bool valid_input = false;
        do {
            std::cout << ">";
            getline(cin, answer);
            
            if(is_only_digits(answer))
            {
                int vertex_id = std::stoi(answer);
                
                if(can_build_settlement_init(vertex_id))
                {
                    build_settlement(vertex_id);
                    std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " built a settlement on vertex " << vertex_id << "\n";
                    valid_input = true;
                    std::cout << *this->board;
                
                }
                else
                {
                    std::cout << "Invalid vertex. Please enter a valid vertex number between 1 and 54.\n";
                }
            }
            else
            {
                std::cout << "Invalid vertex. Please enter a valid vertex number between 1 and 54.\n";
            }

        } while(!valid_input);

        std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " choose your first road based on the edge <vertex1#-vertex2#>\n";
        valid_input = false;
        do {
            std::cout << ">";
            getline(cin, answer);
            
            if(can_build_road(answer))
            {
                build_road(answer);
                std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " built a road on edge " << answer << "\n";
                valid_input = true;
                std::cout << *this->board;
            }
        } while(!valid_input);
    }
    
    for(size_t i = players.size(); i > 0; i--)
    {
        current_player_id = i-1;
        std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " choose your second settlement based on the vertex#\n";
        string answer;
        bool valid_input = false;
        do {
            std::cout << ">";
            getline(cin, answer);

            if(is_only_digits(answer))
            {
                int vertex_id = std::stoi(answer);
                
                if(can_build_settlement_init(vertex_id))
                {
                    build_settlement(vertex_id);
                    std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " built a settlement on vertex " << vertex_id << "\n";
                    valid_input = true;
                    std::cout << *this->board;
                }
                else
                {
                    std::cout << "Invalid vertex. Please enter a valid vertex number between 1 and 54.\n";
                }
            }
            else
            {
                std::cout << "Invalid vertex. Please enter a valid vertex number between 1 and 54.\n";
            }

        } while(!valid_input);

        std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " choose your second road based on the edge <vertex1#-vertex2#>\n";
        valid_input = false;
        do {
            std::cout << ">";
            getline(cin, answer);
            
            if(can_build_road(answer))
            {
                build_road(answer);
                std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " built a road on edge " << answer << "\n";
                valid_input = true;
                std::cout << *this->board;
            }
        } while(!valid_input);
    }

    std::cout << players[current_player_id]->get_color() << "Player " << current_player_id << RESET << " starts the game\n";

}

bool GameLogic::is_only_digits(const string &str)
{
    for(size_t i = 0; i < str.size(); i++)
    {
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool GameLogic::can_build_settlement_init(const int vertex_id)
{
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);
    if(vertex == nullptr){return false;}

    if(vertex->has_settlement())
    {
        std::cout << "A settlement has already been built here\n";
        return false;
    }
    else
    {
        for(shared_ptr<Vertex> adj_vertex : vertex->get_adjacent())
        {
            if(adj_vertex->has_settlement())
            {
                std::cout << "There is a settlement adjacent to this vertex, you can't build here\n";
                return false;
            }
        }
        
    }   
    return true;
}

void GameLogic::roll_dice()
{
    // Create a random number generator
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(2, 12); 

    int result = dis(gen);
    std::cout << "The roll result was: " << result << "\n";

    if(7 != result)
    {
        give_out_resources(result);
    }
    else
    {
        lose_resources();
    }
}

void GameLogic::give_out_resources(const int roll_result)
{
    for(shared_ptr<Hexagon> hex : (*board)[roll_result])
    {
        for(shared_ptr<Vertex> vertex: hex->get_vertices())
        {
            if(vertex->has_settlement())
            {
                size_t player_id = vertex->get_settlement().get_player_id();
                players[player_id]->add_resources(hex->get_resource(), vertex->get_settlement().get_victory_points());
            }
        }
    }   
}

void GameLogic::lose_resources()
{
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->get_num_of_resources() > 7)
        {
            int resources_to_lose = players[i]->get_num_of_resources() / 2;
            std::cout << players[i]->get_color() << "Player " << i << RESET << " has to lose " << resources_to_lose << " resources\n";

            for(int j = 0; j < resources_to_lose; j++)
            {
                std::cout << *players[i];
                std::cout << players[i]->get_color() << "Player " << i << RESET << " choose a resource to lose\n";

                string answer;
                bool valid_input = false;
                do {

                    getline(cin, answer);
            
                    if(!valid_resource(answer))
                    {
                        std::cout << "Resource is not valid, Use: Wood, Bricks, Wool, Grain, Ore\n";
                    }
                    else if (!players[i]->check_resource(answer))
                    {
                        std::cout << players[i]->get_color() << "Player " << i << RESET << " doesn't have " << answer << "\n";
                        
                    }
                    else
                    {
                        players[i]->add_resources(answer, -1);
                        valid_input = true;
                    }
                } while(!valid_input);
            } 
        }
    }
}

void GameLogic::settlements() const
{
    vector<int> player_settlements = players[current_player_id]->get_settlement_vertices();

    if(player_settlements.size() == 0)
    {
        std::cout << current_color << "Player " << current_player_id << RESET << " has no settlements\n";
    }
    else
    {
        std::cout << current_color << "Player " << current_player_id << RESET << " has:\n";
        for(int vertex_id : player_settlements)
        {
            if((*Vertex::get_vertex(vertex_id)).get_settlement().get_name() == "Settlement")
            {
                std::cout << "A settlement on vertex " << (*Vertex::get_vertex(vertex_id)) << "\n";
            }
            else
            {
                std::cout << "A city on vertex " << (*Vertex::get_vertex(vertex_id)) << "\n";
            }
        }
    }
}

bool GameLogic::can_build_road(const string edge_id)
{
    shared_ptr<Edge> edge = Edge::get_edge(edge_id);
    if(edge == nullptr)
    {
        std::cout << "Edge is not valid\n";
        return false;
    }

    if((*edge).has_road())
    {
        std::cout << "A road has already been built here\n";
        return false;
    }
    
    else if(!(*current_player()).can_build_road())
    {
        std::cout << "You don't have enough resources to build a road\n";
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
                            return true;
                        }
                    }
                }
            }
        }
    }
    std::cout << "There is no road  or settlement of " << players[current_player_id]->get_color() << "player " << players[current_player_id]->get_id() << RESET << " leading to this edge\n";
    return false;
}

void GameLogic::build_road(const string edge_id)
{
    
    Player& player = *current_player();
    Edge::get_edge(edge_id)->build_road(player.get_id(), player.get_color());
    player.add_resources(WOOD, -1);
    player.add_resources(BRICKS, -1);
    
}

bool GameLogic::can_build_settlement(const int vertex_id)
{
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);
    if(vertex == nullptr)
    {
        std::cout << "vertex is not valid\n";
        return false;
    }

    if(vertex->has_settlement())
    {
        std::cout << "A settlement has already been built here\n";
        return false;
    }
    else if(!(*current_player()).can_build_settlement())
    {
        std::cout << "You don't have enough resources to build a settlement\n";
        return false;
    }
    else
    {
        Player& player = *current_player();
        for(shared_ptr<Vertex> adj_vertex : vertex->get_adjacent())
        {
            if(adj_vertex->has_settlement())
            {
                std::cout << "There is a settlement adjacent to this vertex, you can't build here\n";
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
                    return true;
                }
            }
        }
        std::cout << "There is no road of " << player.get_color() << "player " << player.get_id() << RESET << " leading to this vertex\n";
        return false;
    }
}

void GameLogic::build_settlement(const int vertex_id)
{
    Player& player = *current_player();
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);

    player.add_points(vertex->build_settlement(player.get_id(), player.get_color()));
    player.add_settlement_vertex(vertex_id);
    player.add_resources(WOOD, -1);
    player.add_resources(BRICKS, -1);
    player.add_resources(WOOL, -1);
    player.add_resources(GRAIN, -1);
}

bool GameLogic::improve_settlement(const int vertex_id)
{
    shared_ptr<Vertex> vertex = Vertex::get_vertex(vertex_id);
    if(vertex == nullptr){return false;}

    Player& player = *current_player();

    if(!vertex->has_settlement())
    {
        std::cout << "There is no settlement here";
        return false;
    }
    else if(player.get_id() != vertex->get_settlement().get_player_id())
    {
        std::cout << "This settlement belongs to another player";
        return false;
    }
    else if("City" == vertex->get_settlement().get_name())
    {
        std::cout << "You already built a city here";
        return false;
    }
    else if(!player.can_build_city())
    {
        std::cout << "You don't have enough resources to build a city";
        return false;
    }
    else
    {
        player.add_points(-1);
        player.add_points(vertex->improve_settlement(player.get_id()));
        player.add_resources(ORE, -3);
        player.add_resources(GRAIN, -2);
        return true;

    }
    return false;
}

bool GameLogic::trade_resources(const size_t other_player, const string give, const string take)
{
    Player& player = *current_player();
    if(!valid_resource(give) || !valid_resource(take))
    {
        std::cout << "The resources are not valid\n";
        return false;
    }
    else if(!player.check_resource(give) || !players[other_player]->check_resource(take))
    {
        std::cout << "Resources not available\n";
        return false;
    }
    else
    {
        std::cout << "Do " << players[other_player]->get_color() << "player " << other_player << RESET << " agrees to the trade? Y/n\n";
        
        while(true){
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
            else if(other_answer == "n")
            {
                std::cout << players[other_player]->get_color() << "Player " << other_player << RESET << " refuses the trade\n";
                return false;
            }
            std::cout << "Invalid answer . Use: Y/n\n";
        }
    }
}

bool GameLogic::trade_dev_cards(const size_t other_player, const string give, const string take)
{
    Player& player = *current_player();
    if(!valid_dev(give) || !valid_dev(take))
    {
        std::cout << "The Development cards are not valid\n";
        return false;
    }
    else if(!player.check_dev(give) || !players[other_player]->check_dev(take))
    {
        std::cout << "Development cards not available\n";
        return false;
    }
    else
    {
        std::cout << "Do " << players[other_player]->get_color() << "player " << other_player << RESET << " agrees to the trade? Y/n\n";

        while(true){
            string other_answer;
            getline(cin ,other_answer);
        
            if(other_answer == "Y")
            {
                player.add_development_card(players[other_player]->remove_dev_card(take));
                players[other_player]->add_development_card(player.remove_dev_card(give));
                return true;
            }
            else if(other_answer == "n")
            {
                std::cout << players[other_player]->get_color() << "Player " << other_player << RESET << " refuses the trade\n";
                return false;
            }
            std::cout << "Invalid answer . Use: Y/n\n";
        }
    }
}

bool GameLogic::buy_dev_card()
{
    Player& player = *current_player();

    if(!player.can_buy_dev())
    {
        std::cout << "You don't have enough resources to buy a dev card\n";
        return false;
    }
    else if(deck->size() == 0)
    {
        std::cout << "The deck is empty\n";
        return false;
    }

    player.add_development_card(deck->draw_card());
    player.add_resources("Ore", -1);
    player.add_resources("Wool", -1);
    player.add_resources("Grain", -1);
    std::cout << player.get_color() << "Player " << player.get_id() << RESET << " bought a development card\n";
    return true;
}

void GameLogic::show_dev_cards() const
{
    current_player()->show_hand();
}

void GameLogic::play_knight()
{
    players[current_player_id]->activate_knight();
    if(3 <= players[current_player_id]->get_activated_knights())
    {
        if(greatest_army_id == 3)
        {
            greatest_army_id = current_player_id;
            players[current_player_id]->add_points(2);
            std::cout << current_color << "Player " << current_player_id << RESET <<" has the greatest army now!\n";
        }
        else if (greatest_army_id != current_player_id)
        {
            if(players[greatest_army_id]->get_activated_knights() < players[current_player_id]->get_activated_knights())
            {
                players[greatest_army_id]->add_points(-2);
                players[current_player_id]->add_points(2);
                greatest_army_id = current_player_id;
                std::cout << current_color << "Player " << current_player_id << RESET << " has the greatest army now!\n";
            }
        }
    }
}

void GameLogic::play_victory()
{
    players[current_player_id]->activate_victory();
}

bool GameLogic::play_year_of_plenty(const string first_resource, const string second_resource)
{
    if(!valid_resource(first_resource) || !valid_resource(second_resource))
    {
        std::cout << "Resources are not valid!\n";
        return false; 
    }
    players[current_player_id]->add_resources(first_resource, 1);
    players[current_player_id]->add_resources(second_resource, 1);
    players[current_player_id]->remove_dev_card(YEAR_OF_PLENTY);
    return true;
}

bool GameLogic::play_monopoly(const string resource)
{
    if(!valid_resource(resource))
    {
        std::cout << "Resource is not valid!\n";
        return false;; 
    }

    int quantity = 0;

    for(size_t i = 0; i < 3; i++)
    {
        if(i != current_player_id)
        {
            int player_quantity = players[i]->get_resource_num(resource);
            players[i]->add_resources(resource, -player_quantity);
            quantity += player_quantity;
        }
    }

    players[current_player_id]->add_resources(resource, quantity);
    players[current_player_id]->remove_dev_card(MONOPOLY);
    return true;
}

bool GameLogic::play_road_building(const string first_edge, const string second_edge)
{

    if(first_edge != second_edge)
    {
        players[current_player_id]->add_resources(BRICKS, 2);
        players[current_player_id]->add_resources(WOOD, 2);

        if(can_build_road(first_edge) && can_build_road(second_edge))
        {
            build_road(first_edge);
            build_road(second_edge);
            players[current_player_id]->remove_dev_card(ROAD_BUILDING);
            return true;
        }
        else
        {
            players[current_player_id]->add_resources(BRICKS, -2);
            players[current_player_id]->add_resources(WOOD, -2);
            return false;
        }
    }

    return false;

}

bool GameLogic::play_dev(const string card)
{
    if(KNIGHT == card)
    {
        if(players[current_player_id]->check_dev(KNIGHT))
        {
            play_knight();
            return true;
        }
        else
        {
            std::cout << "You don't have a non activated knight card\n";
            return false;
        }
    }
    else if (VICTORY == card)
    {
        if(players[current_player_id]->check_dev(VICTORY))
        {
            play_victory();
            return true;
        }
        else
        {
            std::cout << "You don't have a non activated victory card\n";
            return false;
        }
    }
    else
    {
        size_t space_pos = card.find(' ');
        if(space_pos != -1)
        {
            string promo = card.substr(0, space_pos);
            string dependencies = card.substr(space_pos + 1);

            if (YEAR_OF_PLENTY == promo)
            {
                if(players[current_player_id]->check_dev(YEAR_OF_PLENTY))
                {

                    size_t comma_pos = dependencies.find(',');
                    if(comma_pos != -1)
                    {
                        return play_year_of_plenty(dependencies.substr(0, comma_pos), dependencies.substr(comma_pos + 1));
                    }
                    else
                    {
                        std::cout << "Invalid command format. Use: Year-of-plenty <resource1,resource2>\n";
                        return false;
                    }
                }
                else
                {
                    std::cout << "You don't have a year of plenty card\n";
                    return false;
                }
            }
                
            else if (MONOPOLY == promo)
            {
                if(players[current_player_id]->check_dev(MONOPOLY))
                {
                    if(!dependencies.empty())
                    {
                        return play_monopoly(dependencies);
                    }
                    else
                    {
                        std::cout << "Invalid command format. Use: Monopoly <resource>\n";
                        return false;
                    }
                    
                }
                else
                {
                    std::cout << "You don't have a monopoly card\n";
                    return false;
                }
            }
            else if (ROAD_BUILDING == promo)
            {
                if(players[current_player_id]->check_dev(ROAD_BUILDING))
                {
                    size_t comma_pos = dependencies.find(',');
                    if(comma_pos != -1)
                    {
                        return play_road_building(dependencies.substr(0, comma_pos), dependencies.substr(comma_pos + 1));
                    }
                    else
                    {
                        std::cout << "Invalid command format. Use: Road-building <vertex1#-vertex2#,vertex1#-vertex2#>\n";
                        return false;
                    }
                }
                else
                {
                    std::cout << "You don't have a road building card\n";
                    return false;
                }   
            }
            else
            {
                std::cout << "Invalid command format. Use: play-dev <card (Victory, Monopoly <resource>, Year of plenty <resource1, resource2>, "
                << "Road building <vertex1#-vertex2#,vertex1#-vertex2#>, knight)>\n";
                return false;
            }
        }
        else
        {
            std::cout << "Invalid command format. Use: play-dev <card (Victory, Monopoly <resource>, Year of plenty <resource1, resource2>, "
            << "Road building <vertex1#-vertex2#,vertex1#-vertex2#>, knight)>\n";
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
            << "play-dev <card (Victory, Monopoly <resource>, Year-of-plenty <resource1,resource2>, "
            << "Road-building <vertex1#-vertex2#,vertex1#-vertex2#>, knight)>\n"
            << "end\n"
            << "help\n";
}

void GameLogic::next_turn()
{
    current_player_id = (current_player_id + 1) % players.size();
    current_color = players[current_player_id]->get_color();
    std::cout << current_color << "Player " << current_player_id << RESET << "'s turn.\n";
    std::cout << *players[current_player_id];
}

bool GameLogic::valid_resource(const string resource)
{
    if(WOOD != resource && BRICKS != resource && WOOL != resource && GRAIN != resource && ORE != resource){return false;}
    return true;
}

bool GameLogic::valid_dev(const string dev)
{
    if(KNIGHT != dev && VICTORY != dev && MONOPOLY != dev && YEAR_OF_PLENTY != dev && ROAD_BUILDING != dev){return false;}
    return true;
}

void GameLogic::executeCommand(const string& command)
{
    if (command == "help") {
            display_help();
    }
    else if (command == "board") {
        std::cout << *this->board;
    } 
    else if (command == "roll") {
        if(!rolled)
        {
            roll_dice();
            rolled = true;
        }
        else
        {
            std::cout << current_color << "Player " << current_player_id << RESET << " already rolled the dices\n";
        }
        
    } 
    else if (command == "status") {
        std::cout << *current_player();
    }
    else if (command == "settlements") {
        settlements();
    }
    else if (command.find("build-road") == 0) {
        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string edge_id = command.substr(space_pos + 1);

            // Build the road between the vertices
            if(can_build_road(edge_id)) 
            {
                build_road(edge_id);
                std::cout << current_color << "Player " << (*current_player()).get_id() << RESET << "  built a road on edge " << edge_id << "\n";
            } 
            else 
            {
                std::cout << "Failed to build a road on edge " << edge_id << "\n";
            }
                
                
        }
        else
        {
            std::cout << "Invalid command format. Use: build-road <vertex1#-vertex2#>\n";
        }
        
    }
    else if (command.find("build-settlement") == 0)
    {
        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string vertex = command.substr(space_pos + 1);
            
            if(is_only_digits(vertex))
            {
            
                int vertex_id = std::stoi(vertex);

                // Build the settlement on the vertex
                if (can_build_settlement(vertex_id)) 
                {
                    build_settlement(vertex_id);
                    std::cout << current_color << "Player " << (*current_player()).get_id() << RESET << " built a settlement on vertex " << vertex_id << "\n";
                    if(10 <= players[current_player_id]->get_points())
                    {
                        winner_id = current_player_id;
                    }
                } 
                else 
                {
                    std::cout << "Failed to build a settlement on vertex " << vertex_id<< "\n";
                }
            
            }
            else
            {
                std::cout << "Invalid vertex id\n";
            }
            
        }
        else
        {
            std::cout << "Invalid command format. Use: build-settlement <vertex#>\n";
        }
        
    }
    else if (command.find("improve") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string vertex = command.substr(space_pos + 1);
            

            if(is_only_digits(vertex))
            {
                int vertex_id = std::stoi(vertex);

                // Build the settlement on the vertex
                if (improve_settlement(vertex_id)) 
                {
                    std::cout << current_color << "Player " << (*current_player()).get_id() << "built a city on vertex " << vertex_id << "\n";
                    if(10 <= players[current_player_id]->get_points())
                    {
                        winner_id = current_player_id;
                    }
                } 
                else 
                {
                    std::cout << "Failed to build a city on vertex " << vertex_id<< "\n";
                }
            } 
            else 
            {
                std::cout << "Invalid vertex. Please enter a valid vertex number between 1 and 54.\n";
            }
        }
        else
        {
            std::cout << "Invalid command format. Use: improve <vertex#>\n";
        }
    } 
    else if (command.find("trade ") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string trade = command.substr(space_pos + 1);
            space_pos = trade.find(' ');
            if(space_pos != -1)
            {
                try
                {
                    size_t other_id = stoul(trade.substr(0, space_pos));
                    if (other_id < 0 || other_id >= players.size()) 
                    {
                        std::cout << "Invalid player ID. It should be between 0 and " << players.size() - 1 << ".\n";
                        return;
                    }

                    string resources = trade.substr(space_pos + 1);
                    space_pos = resources.find(' ');

                    if(space_pos != -1)
                    {
                        if (trade_resources(other_id, resources.substr(0, space_pos), resources.substr(space_pos + 1))) 
                        {
                            std::cout << "Trade successful between " << current_color << "player " << current_player_id << RESET << " and " << players[other_id]->get_color() << "player " << other_id << RESET << ".\n";
                        } 
                    }
                    else
                    {
                        std::cout << "Invalid command format. Use: trade <id> <give> <take>\n";
                    }

                }
                catch (const std::invalid_argument& e) 
                {
                    std::cout << "Invalid player ID.\n";
                }
            }
            else
            {
                std::cout << "Invalid command format. Use: trade <id> <give> <take>\n";
            }
        }
        else
        {
            std::cout << "Invalid command format. Use: trade <id> <give> <take>\n";
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
                    size_t other_id = stoul(trade.substr(0, space_pos));
                    if (other_id < 0 || other_id >= players.size()) 
                    {
                        std::cout << "Invalid player ID. It should be between 0 and " << players.size() - 1 << ".\n";
                        return;
                    }

                    string devs = trade.substr(space_pos + 1);
                    space_pos = devs.find(' ');

                    if(space_pos != -1)
                    {
                        if (trade_dev_cards(other_id, devs.substr(0, space_pos), devs.substr(space_pos + 1))) 
                        {
                            std::cout << "Trade successful between " << current_color << "player " << current_player_id << RESET << " and " << players[other_id]->get_color() << "player " << other_id << RESET << ".\n";
                        } 
                    }
                    else
                    {
                        std::cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
                    }

                }
                catch (const std::invalid_argument& e) 
                {
                    std::cout << "Invalid player ID.\n";
                }
            }
            else
            {
                std::cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
            }
        }
        else
        {
            std::cout << "Invalid command format. Use: trade-dev <id> <give> <take>\n";
        }
    }
    else if (command == "buy-dev") {

        buy_dev_card();
    }
    else if (command == "devs") {

        show_dev_cards();
    }
    else if (command.find("play-dev") == 0) {

        size_t space_pos = command.find(' ');
        if(space_pos != -1)
        {
            string card_to_play = command.substr(space_pos + 1);
            if(play_dev(card_to_play))
            {
                if(10 <= players[current_player_id]->get_points())
                {
                        winner_id = current_player_id;
                }
                rolled = false;
                next_turn();
            }
        }
        else
        {
            std::cout << "Invalid command format. Use: play-dev <card (Victory, Monopoly <resource>, Year of plenty <resource1, resource2>, "
            << "Road building <vertex1#-vertex2#,vertex1#-vertex2#>, knight)>\n";
        }
    }  
    else if (command == "end") {
        rolled = false;
        next_turn();
    } 
    else {
        std::cout << "Unknown command.\n";
    }
}
