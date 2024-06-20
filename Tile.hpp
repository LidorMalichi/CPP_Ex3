#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include "Card.hpp"

using namespace std;

enum resource{
    WOOD,
    BRICKS,
    WOOL,
    GRAIN,
    ORE
};

class Tile{

    public:
        virtual string land() const = 0;

        virtual int get_resource() const = 0;


};

template <typename T>
class SingletonTile : public Tile {
public:
    static shared_ptr<Tile> get_instance() {

        struct MakeSharedEnabler : public T {
            MakeSharedEnabler() : T(){}
        };


        static shared_ptr<T> instance = make_shared<MakeSharedEnabler>();;
            
        return instance;
    }

protected:
    SingletonTile() {}
};

class Forest: public SingletonTile<Forest>{

    friend class SingletonTile<Forest>;

    public:

        string land() const override{
            return "Fors";
        }

        int get_resource() const override{
            return WOOD;
        }

    private:
        Forest(){}
};

class Hills: public SingletonTile<Hills>{

    friend class SingletonTile<Hills>;

    public:

        string land() const override{
            return "Hils";
        }

        int get_resource() const override{
            return BRICKS;
        }

    private:
        Hills(){}
};

class Pasture: public SingletonTile<Pasture>{

    friend class SingletonTile<Pasture>;

    public:

        string land() const override{
            return "Past";
        }

        int get_resource() const override{
            return WOOL;
        }

    private:
        Pasture(){}
};

class Fields: public SingletonTile<Fields>{

    friend class SingletonTile<Fields>;

    public:

        string land() const override{
            return "Flds";
        }

        int get_resource() const override{
            return GRAIN;
        }

    private:
        Fields(){}
};

class Mountains: public SingletonTile<Mountains>{

    friend class SingletonTile<Mountains>;

    public:

        string land() const override{
            return "Mout";
        }

        int get_resource() const override{
            return ORE;
        }

    private:
        Mountains(){}
};

class Desert: public SingletonTile<Desert>{ 

    friend class SingletonTile<Desert>;


    public:

        string land() const override{
            return "Dsrt";
        }

        int get_resource() const override{
            return -1;
        }

    private:
        Desert(){}
};

class TileFactory {

    public:

        static shared_ptr<Tile> get_tile(const string tile);

};

#endif