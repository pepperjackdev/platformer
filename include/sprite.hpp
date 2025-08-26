#pragma once

#include "node.hpp"

#include <raylib.h>

class Sprite:
    public Node {

    protected:
        Texture2D texture;

    public: 
        Sprite(std::string name, Vector2 position, Texture2D texture);

        virtual void draw() override;

};