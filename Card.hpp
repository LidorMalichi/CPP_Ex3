#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <memory>
#include "General.hpp"
#include <algorithm>
#include <random>

using namespace std;

// A  base class that represents a development card
class DevCard
{
    public:

        string development_type() const {return this->type;}

        bool is_played() const {return this->played;}

        void play() {this->played = true;}

        virtual ~DevCard() = default;

    protected:

        DevCard(const string& type) : type(type){played = false;}

    private:

        string type;

        bool played;
};

// A class that represents a promotion card
class PromoCard : public DevCard
{
    private:

        string promo_type;

    public:

        PromoCard(const string& promo_type) : DevCard(PROMO), promo_type(promo_type){};

        string get_promo_type(){return promo_type;}
}; 

// A class that represents a knight card
class Knight : public DevCard
{
    public:

        Knight() : DevCard(KNIGHT){}
};

// A class that represents a victory card
class Victory : public DevCard
{
    public:

        Victory() : DevCard(VICTORY){}
};

// A class that represents the development cards deck
class Deck
{
    private:

        // A singelton instance
        static shared_ptr<Deck> deck;

        vector<unique_ptr<DevCard>> cards;

        Deck();

        
    public:

        static shared_ptr<Deck> get_deck()
        {
            // A struct that gets access to private constructor
            struct MakeSharedEnabler : public Deck {
                MakeSharedEnabler() : Deck(){}
            };
            if(!deck)
            {
                // Create a deck if it doesn't exist
                deck = make_shared<MakeSharedEnabler>();
            }
            return deck;
        }

        // the size of the deck
        int size() const {return cards.size();}

        // Draws a card
        unique_ptr<DevCard> draw_card()
        {
            unique_ptr<DevCard> card = move(cards.back());
            cards.pop_back();
            return card;
        }        
};

#endif