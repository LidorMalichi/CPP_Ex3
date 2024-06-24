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

class PromoCard : public DevCard
{
    private:

        string promo_type;

    public:

        PromoCard(const string& promo_type) : DevCard(PROMO), promo_type(promo_type){};

        string get_promo_type(){return promo_type;}
}; 

class Knight : public DevCard
{
    public:

        Knight() : DevCard(KNIGHT){}
};


class Victory : public DevCard
{
    public:

        Victory() : DevCard(VICTORY){}
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

        int size() const {return cards.size();}

        unique_ptr<DevCard> draw_card()
        {
            unique_ptr<DevCard> card = move(cards.back());
            cards.pop_back();
            return card;
        }        
};

#endif