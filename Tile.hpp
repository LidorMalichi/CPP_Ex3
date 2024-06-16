#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include "Card.hpp"

using namespace std;

class Tile{

    public:
        virtual string land() const = 0;

        virtual ResourceCard* get_resource() const = 0;


};

class Forest: public Tile{

    public:

        string land() const override{
            return "Fors";
        }

        ResourceCard* get_resource() const override{
            return new Wood();
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Forest {
                MakeSharedEnabler() : Forest(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Forest(){}

        static shared_ptr<Tile> instance;
};

class Hills: public Tile{

    public:

        string land() const override{
            return "Hils";
        }

        ResourceCard* get_resource() const override{
            return new Bricks();
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Hills {
                MakeSharedEnabler() : Hills(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Hills(){}

        static shared_ptr<Tile> instance;
};

class Pasture: public Tile{

    public:

        string land() const override{
            return "Past";
        }

        ResourceCard* get_resource() const override{
            return new Wool();
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Pasture {
                MakeSharedEnabler() : Pasture(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Pasture(){}

        static shared_ptr<Tile> instance;
};

class Fields: public Tile{

    public:

        string land() const override{
            return "Flds";
        }

        ResourceCard* get_resource() const override{
            return new Grain();
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Fields {
                MakeSharedEnabler() : Fields(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Fields(){}

        static shared_ptr<Tile> instance;
};

class Mountains: public Tile{

    public:

        string land() const override{
            return "Mout";
        }

        ResourceCard* get_resource() const override{
            return new Ore();
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Mountains {
                MakeSharedEnabler() : Mountains(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Mountains(){}

        static shared_ptr<Tile> instance;
};

class Desert: public Tile{ 

    public:

        string land() const override{
            return "Dsrt";
        }

        ResourceCard* get_resource() const override{
            return nullptr;
        }

        static shared_ptr<Tile> get_instance()
        {
            struct MakeSharedEnabler : public Desert {
                MakeSharedEnabler() : Desert(){}
            };

            if(!instance)
            {
                instance = make_shared<MakeSharedEnabler>();
            }
            return instance;
        }

    private:
        Desert(){}

        static shared_ptr<Tile> instance;
};

class TileFactory {

    public:

        static shared_ptr<Tile> get_tile(const string tile);

};

#endif