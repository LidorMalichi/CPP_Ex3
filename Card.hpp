#ifndef CARD_HPP
#define CARD_HPP

enum resource{
    WOOD,
    BRICKS,
    WOOL,
    GRAIN,
    ORE
};

class ResourceCard {
    
    public:
        
        virtual int resource_type() const = 0;

        virtual ~ResourceCard() = default;
};

class Wood: public ResourceCard{

    public:

        int resource_type() const override{
            return WOOD;
        }

        ~Wood() {}
};

class Bricks: public ResourceCard{

    public:

        int resource_type() const override{
            return BRICKS;
        }

        ~Bricks() {}
};

class Wool: public ResourceCard{

    public:

        int resource_type() const override{
            return WOOL;
        }

        ~Wool() {}
};

class Grain: public ResourceCard{

    public:

        int resource_type() const override{
            return GRAIN;
        }

        ~Grain() {}
};

class Ore: public ResourceCard{

    public:

        int resource_type() const override{
            return ORE;
        }

        ~Ore() {}
};
#endif