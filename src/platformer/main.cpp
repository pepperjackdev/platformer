#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <list>

#include <cstdint>
#include <stdfloat>
#include <limits>

class Node {
    private:
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
                position(position), 
                velocity(velocity), 
                acceleration(acceleration), 
                texture(texture) {};
            
        Rectangle getRectangle() {
            return (Rectangle){
                this->position.x,
                this->position.y,
                (float)this->texture.width,
                (float)this->texture.height
            };
        };

        Vector2 getMomentum() {
            return Vector2Scale(this->velocity, this->mass);
        }

        void setMomentum(Vector2 momentum) {
            this->velocity=Vector2Scale(momentum, 1.0f/this->mass);
        }
        
        virtual void update(std::list<std::shared_ptr<Node>> nodes) {
            // Updating position
            this->position = Vector2Add(this->position, 
                Vector2Scale(this->velocity, GetFrameTime()));

            // Updating velocity
            this->velocity = Vector2Add(this->velocity,
                Vector2Scale(this->acceleration, GetFrameTime()));

            // Collisions
            for (std::shared_ptr<Node> node: nodes) {
                if (CheckCollisionRecs(this->getRectangle(), node->getRectangle())) {
                    
                }
            }
        }

        void draw() {
            DrawTextureV(this->texture, this->position, RAYWHITE);
        }
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    std::list<std::shared_ptr<Node>> nodes = {};

    nodes.push_back(std::make_shared<Node>(
        std::numeric_limits<std::float32_t>::max(),
        (Vector2){100, 800},
        (Vector2){0, 0},
        (Vector2){0, 0},
        LoadTexture("assets/platform.png")
    ));

    nodes.push_back(std::make_shared<Node>(
        1.0f,
        (Vector2){100, 100},
        (Vector2){0, 0},
        (Vector2){0, 100},
        LoadTexture("assets/player.png")
    ));

    while (!WindowShouldClose()) {
        for (std::shared_ptr<Node> node: nodes) node->update(nodes);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (std::shared_ptr<Node> node: nodes) node->draw();
        EndDrawing();
    }

    CloseWindow();
}
