#include "Card.hpp"

shared_ptr<Deck> Deck::deck;

Deck::Deck()
{
    for(size_t i = 1; i <= 14; i++)
    {
        cards.push_back(make_unique<Knight>());
    }

    for(size_t i = 1; i <= 5; i++)
    {
        cards.push_back(make_unique<PromoCard>("Monopoly"));
    }

    for(size_t i = 1; i <= 2; i++)
    {
        cards.push_back(make_unique<PromoCard>("Road building"));
    }

    for(size_t i = 1; i <= 2; i++)
    {
        cards.push_back(make_unique<PromoCard>("Year of plenty"));
    }

    for(size_t i = 1; i <= 4; i++)
    {
        cards.push_back(make_unique<Victory>());
    }
}