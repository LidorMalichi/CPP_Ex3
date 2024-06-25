#include "Tile.hpp"

// The factory static method to make the lands shareable

shared_ptr<Tile> TileFactory::get_tile(const string tile)
{
    
    if ("Forest" == tile)
    {
        return Forest::get_instance();
    }
    if("Hills" == tile)
    {
        return Hills::get_instance();
    }
    if ("Pasture" == tile)
    {
        return Pasture::get_instance();
    }
    if ("Fields" == tile)
    {
        return Fields::get_instance();
    }
    if ("Mountains" == tile)
    {
        return Mountains::get_instance();
    }
    if("Desert" == tile)
    {
        return Desert::get_instance(); 
    }
    return nullptr;
        
}