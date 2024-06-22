#include "Player.hpp"

ostream &operator<<(ostream &os, const Player &player)
{
    std::cout << player.color << "Player " << player.id << RESET << " has " << player.points << " victory points, "
                  << player.resources.at("Wood") << " Wood, "
                  << player.resources.at("Bricks") << " Bricks, "
                  << player.resources.at("Wool") << " Wool, "
                  << player.resources.at("Grain") << " Grain, and "
                  << player.resources.at("Ore") << " Ore.\n";
}

void Player::add_development_card(unique_ptr<DevCard> card)
{
    hand.push_back(card);
}

unique_ptr<DevCard> Player::remove_dev_card(const string dev)
{
    if("Knight" == dev || "Victory" == dev)
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == dev)
            {
                unique_ptr<DevCard> card = move(hand[i]);
                hand.erase(hand.begin() + i);
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
                    hand.erase(hand.begin() + i);
                    return card;
                }
            }
        }
    }
}

bool Player::can_build_road()
{
    if(resources["Wood"] > 0 && resources["Bricks"] > 0){return true;}
    return false;
}

bool Player::can_build_settlement()
{
    if(resources["Wood"] > 0 && resources["Bricks"] > 0 && resources["Wool"] > 0){return true;}
    return false;
}

bool Player::can_build_city()
{
    if(resources["Ore"] > 2 && resources["Grain"] > 1){return true;}
    return false;
}

void Player::add_resources(string resource, int units)
{
    this->resources[resource] += units;
}

bool Player::check_dev(const string dev)
{
    if("Knight" == dev || "Victory" == dev)
    {
        for(size_t i = 0; i < this->hand.size(); i++)
        {
            if(hand[i]->development_type() == dev)
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
                if(dev == card->get_promo_type())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
