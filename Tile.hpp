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
            return "Fors";
        }

        string get_resource() const override{
            return "Wood";
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

        string get_resource() const override{
            return "Bricks";
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

        string get_resource() const override{
            return "Wool";
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

        string get_resource() const override{
            return "Grain";
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

        string get_resource() const override{
            return "Ore";
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