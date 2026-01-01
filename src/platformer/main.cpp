#include <raylib.h>
#include <raymath.h>

#include <memory>

#include <list>

class Node {
    protected:
        Rectangle rectangle;
        Texture2D texture;

    public:
        Node(Rectangle rectangle, Texture2D texture): 
            rectangle(rectangle), texture(texture) {};

        virtual void update(std::list<std::shared_ptr<Node>> nodes) {}

        void draw() {
            DrawTexture(
                this->texture, 
                this->rectangle.x, 
                this->rectangle.y, 
                RAYWHITE
            );
        }
};

class Platform: public Node {
    public:
        Platform(Rectangle rectangle, Texture2D texture):
            Node(rectangle, texture) {};
};

class Entity: public Node {
    protected:
        Vector2 velocity;
        Vector2 acceleration;

    public:
        Entity(Rectangle rectangle, Vector2 acceleration, Vector2 size, Texture2D texture):
            Node(rectangle, texture), velocity(velocity), acceleration(acceleration) {};

        void update(std::list<std::shared_ptr<Node>> nodes) override {
            // Along X-Axis
            
            // Along Y-Axis

        }
};

class Player: public Entity {
    public:
        Player(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, Texture2D texture):
            Entity(position, velocity, acceleration, size, texture) {};
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::list<std::shared_ptr<Node>> nodes = {};

    nodes.push_back(std::make_shared<Platform>(
        (Rectangle){100, 500, 100, 100}, LoadTexture("assets/dirt_block.png"))
    );

    nodes.push_back(std::make_shared<Player>(
        (Vector2){100, 300}, (Vector2){0, 0}, (Vector2){0, 100}, (Vector2){100, 100}, LoadTexture("assets/player.png"))
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
