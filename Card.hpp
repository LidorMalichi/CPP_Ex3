#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <memory>

using namespace std;

enum dev_type{
    PROMO,
    KNIGHT,
    VICTORY
};

class DevCard
{
    public:

        virtual int development_type() const = 0;

        virtual ~DevCard() = default;
};

class PromoCard : public DevCard
{
    private:

        string promo_type;

    public:

        int develoopment_type(){return PROMO;}

        string get_promo_type(){return promo_type;}
}; 

class Knight : public DevCard
{
    int develoopment_type(){return KNIGHT;}
};


class Victory : public DevCard
{
    int develoopment_type(){return VICTORY;}
};

class Deck
{
    private:
        static unique_ptr<Deck> deck;

        vector<unique_ptr<DevCard>> cards;

        Deck();

        
    public:

        static unique_ptr<Deck> get_deck()
        {
            struct MakeUniqueEnabler : public Deck {
                MakeUniqueEnabler() : Deck(){}
            };
            if(!deck)
            {
                deck = make_unique<MakeUniqueEnabler>();
            }
            return move(deck);
        }

        unique_ptr<DevCard> draw_card()
        {
            unique_ptr<DevCard> card = move(cards.back());
            cards.pop_back();
            return card;
        }        
};

#endif