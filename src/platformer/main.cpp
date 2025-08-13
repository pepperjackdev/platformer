#include <raylib.h>
#include "tiled.hh"

int main() {
    // SetTargetFPS(60);
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // InitWindow(900, 900, "Platformer");

    Map map = Map("assets/maps/level.json");
    Layer layer = *map.getLayers().begin();

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //         ClearBackground(RAYWHITE);
    //     EndDrawing();
    // }
    // 
    // CloseWindow();
}
