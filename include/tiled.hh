#pragma once

#include <string>
#include <list>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Map;
class Layer;
class Data;
class Tileset;
class Tile;

class Map {
    private:
        json source;
    public:
        Map(std::string path);
        std::list<Layer> getLayers() const;
};

class Layer {
    private:
        json source;
    public:
        Layer(json source);
        int getId() const;
        std::string getName() const;
        int getWidth() const;
        int getHeight() const;
        Data getData() const;
};

class Data {
    private:
        json source;
    public:
        Data(json source);
        Tile getTile(int x, int y, Tileset set) const;
};

class Tileset {
    private:
        json source;
    public:
        Tileset(std::string path);
        Tileset(json source);
        std::list<Tile> getTiles();
        Tile getTile(int id) const;
};

class Tile {
    private:
        json source;
    protected:
    public:
        Tile(json source);
        int getId() const;
        std::string getImagePath() const;
        int getImageWidth() const;
        int getImageHeight() const;
};
