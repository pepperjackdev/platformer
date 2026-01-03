#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <cstdint>

#include <list>
#include <optional>

enum class Collision: uint8_t {
    RIGHTSIDE=0b11111011,
    LEFTSIDE=0b11110111,
    UPSIDE=0b01111111,
    DOWNSIDE=0b10111111,
};

uint8_t inline CheckCollisionAlpha(Rectangle rec0, Rectangle rec1) {
    return rec0.y + rec0.height <= rec1.y;
};

uint8_t inline CheckCollisionBeta(Rectangle rec0, Rectangle rec1) {
    return rec0.y >= rec1.y + rec1.height;
};

uint8_t inline CheckCollisionGamma(Rectangle rec0, Rectangle rec1) {
    return rec0.x + rec0.width >= rec1.x;
}

uint8_t inline CheckCollisionDelta(Rectangle rec0, Rectangle rec1) {
    return rec0.x <= rec1.x + rec1.width;
}

uint8_t inline CheckCollision(Rectangle rec0, Rectangle rec1) {
    return 0;
}

std::optional<Collision> CheckSideCollision(Rectangle rec0a, Rectangle rec0b, Rectangle rec1a, Rectangle rec1b) {
    if (CheckCollisionAlpha(rec0b, rec1b) && CheckCollisionBeta(rec0b, rec1b) &&
            !CheckCollisionGamma(rec0a, rec1a) && CheckCollisionGamma(rec0b, rec1b)) {
        return std::optional(Collision::RIGHTSIDE);
    } else if (CheckCollisionAlpha(rec0b, rec1b) && CheckCollisionBeta(rec0b, rec1b) &&
            !CheckCollisionDelta(rec0a, rec1a) && CheckCollisionDelta(rec0b, rec1b)) {
        return std::optional(Collision::LEFTSIDE);
    } else if (CheckCollisionGamma(rec0b, rec1b) && CheckCollisionDelta(rec0b, rec1b) &&
            !CheckCollisionAlpha(rec0a, rec1a) && CheckCollisionAlpha(rec0b, rec1b)) {
        return std::optional(Collision::UPSIDE);
    } else if (CheckCollisionGamma(rec0b, rec1b) && CheckCollisionDelta(rec0b, rec1b) &&
            !CheckCollisionBeta(rec0a, rec1a) && CheckCollisionBeta(rec0b, rec1b)) {
        return std::optional(Collision::DOWNSIDE);
    } else {
        std::nullopt;
    }
};

class Node {
    protected:
        Vector2 position;
        Texture2D texture;

    public:
        Node(
            Vector2 position, 
            Texture2D texture): 
                position(position), 
                texture(texture) {};

        virtual void update(std::list<std::shared_ptr<Node>> nodes) {}

        void draw() {
            DrawTextureV(
                this->texture, 
                this->position,
                RAYWHITE
            );
        }
};

class Platform: public Node {
    public:
        Platform(
            Vector2 position, 
            Texture2D texture):
                Node(position, texture) {};
};

class Entity: public Node {
    protected:
        Vector2 velocity;
        Vector2 acceleration;

    public:
        Entity(
            Vector2 position, 
            Vector2 velocity, 
            Vector2 acceleration, 
            Texture2D texture
        ):
            Node(position, texture), 
                velocity(velocity), 
                acceleration(acceleration) {};

        void update(std::list<std::shared_ptr<Node>> nodes) override {

        }
};

class Player: public Entity {
    public:
        Player(
            Vector2 position, 
            Vector2 velocity, 
            Vector2 acceleration, 
            Texture2D texture):
                Entity(position, velocity, acceleration, texture) {};
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::list<std::shared_ptr<Node>> nodes = {};

    nodes.push_back(std::make_shared<Platform>(
        (Vector2){100, 500}, 
        LoadTexture("assets/dirt_block.png"))
    );

    nodes.push_back(std::make_shared<Player>(
        (Vector2){100, 100},
        (Vector2){0, 0},
        (Vector2){0, 100},
        LoadTexture("assets/player.png"))
    );

    while (!WindowShouldClose()) {
        for (std::shared_ptr<Node> n: nodes) n->update(nodes);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (std::shared_ptr<Node> n: nodes) n->draw();
        EndDrawing();
    }

    CloseWindow();
}
