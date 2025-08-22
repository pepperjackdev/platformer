#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <vector>

class Node {
    protected:
        Rectangle rectangle;
        Texture2D texture;
        Vector2 velocity;
        float mass;

    public:
        Node(Rectangle rectangle, 
            Texture2D texture,
            Vector2 velocity,
            float mass):
                rectangle(rectangle), 
                texture(texture),
                velocity(velocity),
                mass(mass) {}

        Rectangle const& getRectangle() {
            return this->rectangle;
        }

        Texture2D const& getTexture() {
            return this->texture;
        }

        Vector2 getVelocity() {
            return this->velocity;   
        }

        float getMass() {
            return this->mass;
        }

        Vector2 getResultantForce() {
            return (Vector2){0, 10};
        }

        Vector2 getMomentum() {
            return Vector2Scale(
                this->velocity,
                this->mass
            );
        }

        void setMomentum(Vector2 momentum) {
            this->velocity = Vector2Scale(
                momentum,
                1.0f / this->mass
            );
        }

        virtual void update() {
            // updating momentum
            if (this->getResultantForce() != (Vector2){0, 0}) {
                Vector2 momentum = Vector2Scale(
                    this->getResultantForce(),
                    GetFrameTime()
                );
                this->setMomentum(this->getMomentum() + momentum);
            }


            // updating position
            Vector2 position = Vector2Add(
                (Vector2){this->rectangle.x, this->rectangle.y},
                Vector2Scale(
                    this->getVelocity(),
                    GetFrameTime()
                )
            );
            this->rectangle.x = position.x;
            this->rectangle.y = position.y;
        }

        void draw() {
            DrawTexture(
                this->texture,
                this->rectangle.x,
                this->rectangle.y,
                WHITE
            );
        }
};

class Block:
    public Node {
    
    public:
        Block(Rectangle rectangle, Texture2D texture, Vector2 velocity, float mass): 
            Node(rectangle, texture, velocity, mass) {}
};

class Player:
    public Node {
    
    protected:
        Camera2D camera;
    
    public:
        Player(Rectangle rectangle, Texture2D texture): 
            Node(rectangle, texture, (Vector2){0, 0}, 0) {
                this->camera = (Camera2D){
                    (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
                    (Vector2){rectangle.x, rectangle.y},
                    0,
                    4.0f
                };
            }

        Camera2D& getCamera() {
            return this->camera;
        }

        void update() override {
            // Updating position
            if (IsKeyDown(KEY_D)) {
                this->rectangle.x += 1;
            }
            
            if (IsKeyDown(KEY_A)) {
                this->rectangle.x -= 1;
            }
            
            // Updating camera
            this->camera.target = (Vector2){
                this->rectangle.x + this->rectangle.width / 2, 
                this->rectangle.y + this->rectangle.height / 2
            };
        }
};


int main_leg() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    Texture2D blockTexture = LoadTexture("assets/tiles/block.png");
    Texture2D playerTexture = LoadTexture("assets/tiles/player.png");

    std::vector<std::shared_ptr<Node>> nodes{};
    nodes.push_back(std::make_shared<Block>(
        (Rectangle){100, 800, 32, 32},
        blockTexture,
        (Vector2){0, -100},
        1
    ));

    auto player = std::make_shared<Player>(
        (Rectangle){100, 100, 32, 32},
        playerTexture
    );

    nodes.push_back(player);

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Drawing nodes
            for (std::shared_ptr node: nodes) {
                node->draw();
            }

            // Updating nodes
            for (std::shared_ptr node: nodes) {
                node->update();
                }
        EndDrawing();
    }

    CloseWindow();
}
