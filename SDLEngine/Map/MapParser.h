#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser
{
    public:
        bool Load();
        void Clean();

        inline GameMap* GetMaps();

        inline static MapParser* GetInstances(){ return s_Instance = (s_Instance !=nullptr)? s_Instance : new MapParser();}

    private:
        bool Parse(std::string id, std::string source);
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer,TilesetList tilesets, int tilesize, int rowcount, int colcount)

        MapParser(){}
        static MapParser* s_Instatnce;
        std::map<std::string, GameMap*>m_MapDict;
};

#endif // MAPPARSER_H
