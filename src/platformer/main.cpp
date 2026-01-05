#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <deque>

#include <cstdint>
#include <stdfloat>
#include <limits>

class Node {
    public:
        std::float32_t mass;
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        Texture2D texture;

    public:
        Node(uint32_t mass,
            Vector2 position, 
            Vector2 velocity, 
            Vector2 acceleration, 
            Texture2D texture): 
                mass(mass),
                position(position), 
                velocity(velocity), 
                acceleration(acceleration), 
                texture(texture) {}
            
        Rectangle getRectangle() {
            return (Rectangle){
                this->position.x,
                this->position.y,
                (float)this->texture.width,
                (float)this->texture.height
            };
        }
        
        virtual void update() {
            // Updating position
            this->position = Vector2Add(this->position, 
                Vector2Scale(this->velocity, GetFrameTime()));

            // Updating velocity
            this->velocity = Vector2Add(this->velocity,
                Vector2Scale(this->acceleration, GetFrameTime()));
        }

        void draw() {
            DrawTextureV(this->texture, this->position, RAYWHITE);
        }
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::deque<std::shared_ptr<Node>> nodes;

    nodes.push_back(std::make_shared<Node>(
        1.0e10f32,
        (Vector2){100, 300},
        (Vector2){0, 0},
        (Vector2){0, 0},
        LoadTexture("assets/platform.png")
    ));

    nodes.push_back(std::make_shared<Node>(
        1.0f32,
        (Vector2){100, 100},
        (Vector2){0, 0},
        (Vector2){0, 100},
        LoadTexture("assets/player.png")
    ));

    while (!WindowShouldClose()) {
        // Updating nodes
        for (std::shared_ptr<Node> node: nodes) node->update();

        // Collisions
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                std::shared_ptr<Node> node1 = nodes[i];
                std::shared_ptr<Node> node2 = nodes[j];
                if (CheckCollisionRecs(node1->getRectangle(), node2->getRectangle())) {
                    Vector2 velocity1 = Vector2Scale(
                        Vector2Add(
                            Vector2Scale(node2->velocity, 2*node2->mass), 
                            Vector2Scale(node1->velocity, node1->mass - node2->mass)), 
                        1.0f32/(node1->mass + node2->mass));
                    Vector2 velocity2 = Vector2Scale(
                        Vector2Add(
                            Vector2Scale(node1->velocity, 2*node1->mass), 
                            Vector2Scale(node2->velocity, node2->mass - node1->mass)), 
                        1.0f32/(node1->mass + node2->mass));
                    node1->velocity = velocity1;
                    node2->velocity = velocity2;
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (std::shared_ptr<Node> node: nodes) node->draw();
        EndDrawing();
    }

    CloseWindow();
}
