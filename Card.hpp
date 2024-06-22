#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <memory>
#include "General.hpp"

using namespace std;


class DevCard
{
    public:

        virtual string development_type() const = 0;

        virtual ~DevCard() = default;
};

class PromoCard : public DevCard
{
    private:

        string promo_type;

    public:

        PromoCard(const string promo_type):promo_type(promo_type){};

        string development_type() const override {return PROMO;}

        string get_promo_type(){return promo_type;}
}; 

class Knight : public DevCard
{
    string development_type() const override {return KNIGHT;}
};


class Victory : public DevCard
{
    string development_type() const override {return VICTORY;}
};

class Deck
{
    private:
        static shared_ptr<Deck> deck;

        vector<unique_ptr<DevCard>> cards;

        Deck();

        
    public:

        static shared_ptr<Deck> get_deck()
        {
            struct MakeSharedEnabler : public Deck {
                MakeSharedEnabler() : Deck(){}
            };
            if(!deck)
            {
                deck = make_shared<MakeSharedEnabler>();
            }
            return deck;
        }

        unique_ptr<DevCard> draw_card()
        {
            unique_ptr<DevCard> card = move(cards.back());
            cards.pop_back();
            return card;
        }        
};

#endif