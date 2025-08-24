#include <memory>
#include <vector>
#include <optional>
#include <algorithm>

#include "node.hpp"

#include <raylib.h>

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    //
    Node game = Node("game");

    // Adding the level node
    game.addChild(std::make_shared<Node>(
        "level0"
    ));

    // Adding a tiles node to level
    game.getChild("level0")->addChild(
        std::make_shared<Node>(
            "tiles"
        )
    );

    while (!WindowShouldClose()) {
        // Updating
        game.update();

        // Drawing
        BeginDrawing();
            ClearBackground(RAYWHITE);
            game.draw();
        EndDrawing();
    }

    CloseWindow();
}