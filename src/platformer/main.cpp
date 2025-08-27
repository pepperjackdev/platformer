#include <memory>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include <format>

#include "node.hpp"
#include "body.hpp"
#include "sprite.hpp"

#include <raylib.h>

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    // The root node
    auto root = std::make_shared<Node>(
        "root",
        (Vector2){100, 100}
    );

    Texture2D texture = LoadTexture("assets/grass.png");
    (*root) += std::make_shared<Sprite>(
        "image",
        (Vector2){100, 100},
        texture
    );

    while (!WindowShouldClose()) {
        // Updating
        (*root).update();

        // Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            (*root).draw();
        EndDrawing();
    }

    CloseWindow();
}