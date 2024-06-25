#include "Card.hpp"

// A deck singleton instance
shared_ptr<Deck> Deck::deck;

// Deck constructor
Deck::Deck()
{
    for(size_t i = 1; i <= 14; i++)
    {
        cards.push_back(make_unique<Knight>());
    }

    for(size_t i = 1; i <= 5; i++)
    {
        cards.push_back(make_unique<PromoCard>(MONOPOLY));
    }

    for(size_t i = 1; i <= 2; i++)
    {
        cards.push_back(make_unique<PromoCard>(ROAD_BUILDING));
    }

    for(size_t i = 1; i <= 2; i++)
    {
        cards.push_back(make_unique<PromoCard>(YEAR_OF_PLENTY));
    }

    for(size_t i = 1; i <= 4; i++)
    {
        cards.push_back(make_unique<Victory>());
    }

    // Shuffles the deck
    random_device rd;
    mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);
    
}