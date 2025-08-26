#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

#include "node.hpp"
#include "sprite.hpp"

#include <raylib.h>

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    // Creating a basic game structure
    //  - root:
    //      - game:
    //          - level:
    //              - layer:
    //                  - tile

    // The root node
    auto root = std::make_shared<Node>("root");
    
    // The game node
    auto game = root->newChild(std::make_shared<Node>(
        "game"
    ));

    // Adding a level node
    auto level = game->newChild(std::make_shared<Node>(
        "level"
    )); 

    // Adding a layer node
    auto layer = level->newChild(std::make_shared<Node>(
        "layer"
    ));

    // Adding a tile node
    Texture2D texture = LoadTexture("assets/grass.png");
    auto tile = layer->newChild(std::make_shared<Sprite>(
        "tile",
        (Vector2){0, 0},
        texture
    ));

    while (!WindowShouldClose()) {
        // Updating
        root->update();

        // Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            root->draw();
        EndDrawing();
    }

    CloseWindow();
}