#include <raylib.h>
#include <raymath.h>

#include <memory>

#include <list>

class Node {
    protected:
        Rectangle rectangle;
        Texture2D texture;

    public:
        Node(
            Rectangle rectangle, 
            Texture2D texture): 
                rectangle(rectangle), 
                texture(texture) {};

        virtual void update(std::list<std::shared_ptr<Node>> nodes) {
            
        }

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
        Platform(
            Rectangle rectangle, 
            Texture2D texture):
                Node(rectangle, texture) {};
};

class Entity: public Node {
    protected:
        Vector2 velocity;
        Vector2 acceleration;

    public:
        Entity(
            Rectangle rectangle, 
            Vector2 velocity, 
            Vector2 acceleration, 
            Texture2D texture
        ):
            Node(rectangle, texture), 
                velocity(velocity), 
                acceleration(acceleration) {};

        void update(std::list<std::shared_ptr<Node>> nodes) override {
            
        }
};

class Player: public Entity {
    public:
        Player(
            Rectangle rectangle, 
            Vector2 velocity, 
            Vector2 acceleration, 
            Texture2D texture):
                Entity(rectangle, velocity, acceleration, texture) {};
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::list<std::shared_ptr<Node>> nodes = {};

    nodes.push_back(std::make_shared<Platform>(
        (Rectangle){100, 500, 100, 100}, 
        LoadTexture("assets/dirt_block.png"))
    );

    nodes.push_back(std::make_shared<Player>(
        (Rectangle){100, 100, 32, 32},
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
