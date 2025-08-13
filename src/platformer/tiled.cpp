#include <tiled.hh>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using json = nlohmann::json;

Map::Map(std::string path) {
    std::ifstream f(path);
    this->source = json::parse(f);
}

std::list<Layer> Map::getLayers() const {
    std::list<Layer> layers = std::list<Layer>();
    // FIXME: gets ONE layer, not all nor none
    Layer layer = Layer(this->source["layers"][0]);
    layers.push_front(layer);
    return layers;
}

Layer::Layer(json source) {
    this->source = source;
}

int Layer::getId() const {
    return this->source["id"];
}

int Layer::getWidth() const {
    return this->source["width"];
}

int Layer::getHeight() const {
    return this->source["height"];
}

Data Layer::getData() const {
    return Data(this->source["data"]);
}

Data::Data(json source) {
    this->source = source;
}

Tile Data::getTile(int x, int y, Tileset set) const { // FIXME: Too many args; Tileset should became member
    return set.getTile(this->source[x + y * 30]); // FIXME: Hardcoded size of tile
}

Tileset::Tileset(json source) {
    this->source = source;
}

Tileset::Tileset(std::string path) {
    std::ifstream f(path);
    this->source = json::parse(f);
}

Tile Tileset::getTile(int id) const {
    return Tile(this->source["tiles"][id]);
}

Tile::Tile(json source) {
    this->source = source;
}

std::string Tile::getImagePath() const {
    return this->source["image"];
}