#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "General.hpp"

using namespace std;

class Tile{

    public:
        virtual string land() const = 0;

        virtual string get_resource() const = 0;


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
            return FOREST;
        }

        string get_resource() const override{
            return WOOD;
        }

    private:
        Forest(){}
};

class Hills: public SingletonTile<Hills>{

    friend class SingletonTile<Hills>;

    public:

        string land() const override{
            return HILLS;
        }

        string get_resource() const override{
            return BRICKS;
        }

    private:
        Hills(){}
};

class Pasture: public SingletonTile<Pasture>{

    friend class SingletonTile<Pasture>;

    public:

        string land() const override{
            return PASTURE;
        }

        string get_resource() const override{
            return WOOL;
        }

    private:
        Pasture(){}
};

class Fields: public SingletonTile<Fields>{

    friend class SingletonTile<Fields>;

    public:

        string land() const override{
            return FIELDS;
        }

        string get_resource() const override{
            return GRAIN;
        }

    private:
        Fields(){}
};

class Mountains: public SingletonTile<Mountains>{

    friend class SingletonTile<Mountains>;

    public:

        string land() const override{
            return MOUNTAINS;
        }

        string get_resource() const override{
            return ORE;
        }

    private:
        Mountains(){}
};

class Desert: public SingletonTile<Desert>{ 

    friend class SingletonTile<Desert>;


    public:

        string land() const override{
            return DESERT;
        }

        string get_resource() const override{
            return "";
        }

    private:
        Desert(){}
};

class TileFactory {

    public:

        static shared_ptr<Tile> get_tile(const string tile);

};

#endif