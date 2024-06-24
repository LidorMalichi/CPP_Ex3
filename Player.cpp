#include "Player.hpp"

vector<shared_ptr<Player>> Player::players;

ostream &operator<<(ostream &os, const Player &player)
{
    os << player.color << "Player " << player.id << RESET << " has " << player.points << " victory points, "
                  << player.resources.at("Wood") << " Wood, "
                  << player.resources.at("Bricks") << " Bricks, "
                  << player.resources.at("Wool") << " Wool, "
                  << player.resources.at("Grain") << " Grain, and "
                  << player.resources.at("Ore") << " Ore.\n";
    return os;
}

void Player::add_development_card(unique_ptr<DevCard> card)
{
    hand.push_back(move(card));
}

unique_ptr<DevCard> Player::remove_dev_card(const string dev)
{
    if("Knight" == dev || "Victory" == dev)
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == dev && !hand[i]->is_played())
            {
                unique_ptr<DevCard> card = move(hand[i]);
                hand.erase(hand.begin() + static_cast<long>(i));
                return card;
            }
        }
    }
    else
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == "Promo")
            {
                PromoCard* card = dynamic_cast<PromoCard*>(hand[i].get());
                if(dev == card->get_promo_type())
                {
                    unique_ptr<DevCard> card = move(hand[i]);
                    hand.erase(hand.begin() +  static_cast<long>(i));
                    return card;
                }
            }
        }
    }
    return nullptr;
}

bool Player::can_build_road() const
{
    if(resources.at(WOOD) > 0 && resources.at(BRICKS) > 0){return true;}
    return false;
}

bool Player::can_build_settlement() const 
{
    if(resources.at(WOOD) > 0 && resources.at(BRICKS) > 0 && resources.at(WOOL) > 0 && resources.at(GRAIN) > 0){return true;}
    return false;
}

bool Player::can_build_city() const
{
    if(resources.at(ORE) > 2 && resources.at(GRAIN) > 1){return true;}
    return false;
}

bool Player::can_buy_dev() const
{
    if(resources.at(ORE) > 0 && resources.at(GRAIN) > 0 && resources.at(WOOL) > 0){return true;}
    return false;
}

void Player::add_resources(string resource, int units)
{
    this->resources[resource] += units;
    this->num_of_resources += units;
}

void Player::show_hand() const
{
    if(this-> hand.size() == 0)
    {
        cout << "Player " << this->id << "doesn't have any development cards\n ";
        return;
    }

    cout << "Player " << this->id << "'s development cards:\n";
    for(size_t i = 0; i < hand.size(); i++)
    {
        if("Promo" != hand[i]->development_type())
        {
            cout << hand[i]->development_type() << "\n";
        }
        else
        {
            PromoCard* card = dynamic_cast<PromoCard*>(hand[i].get());
            cout << card->get_promo_type() << "\n";
        }
    }

}

void Player::activate_knight()
{
    for(size_t i = 0; i < hand.size(); i++)
    {
        if(KNIGHT == hand[i]->development_type() && !hand[i]->is_played())
        {
            hand[i]->play();
            activated_knights += 1;
            break;
        }
    }
}

void Player::activate_victory()
{
    for(size_t i = 0; i < hand.size(); i++)
    {
        if(VICTORY == hand[i]->development_type() && !hand[i]->is_played())
        {
            hand[i]->play();
            this->points += 1;
            break;
        }
    }
}

bool Player::check_dev(const string dev) const
{
    if("Knight" == dev || "Victory" == dev)
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == dev && !hand[i]->is_played())
            {
                return true;
            }
        }
    }
    else
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == "Promo")
            {
                PromoCard* card = dynamic_cast<PromoCard*>(hand[i].get());
                if(dev == card->get_promo_type() && !card->is_played())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
