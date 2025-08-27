#include "sprite.hpp"

Sprite::Sprite(std::string name, Vector2 position, Texture2D texture):
    Node(name, position), texture(texture) {}

void Sprite::draw() {
    // Drawing the texture
    DrawTexture(
        this->texture,
        this->get_absolute_position().x,
        this->get_absolute_position().y,
        RAYWHITE
    );

    // Drawing the childrens
    Node::draw();
}