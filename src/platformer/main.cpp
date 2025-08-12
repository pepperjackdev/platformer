#include <raylib.h>
#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::fstream mapStream("assets/maps/map.json");
    json map = json::parse(mapStream);
    json layer = map["layers"][0];
    json data = layer["data"];

    Image tile = LoadImage("assets/images/block.png");
    Texture2D texture = LoadTextureFromImage(tile);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Drawing level
            for (int row = 0; row < layer["height"]; row++) {
                for (int col = 0; col < layer["width"]; col++) {
                    // Drawing a tile from tileset...
                    if (data[row * 30 + col] == 1) {
                        DrawTexture(texture, col * 32, row * 32, RAYWHITE);
                    }
                }
            }
    
        EndDrawing();
    }
    CloseWindow();
}
