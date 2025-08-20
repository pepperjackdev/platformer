#include <raylib.h>

#include <memory>
#include <vector>

class Node {
    protected:
        Rectangle rectangle;
        Texture2D texture;

    public:
        Node(Rectangle rectangle, Texture2D texture):
            rectangle(rectangle), texture(texture) {}

        Rectangle& getRectangle() {
            return this->rectangle;
        }

        Texture2D& getTexture() {
            return this->texture;
        }

        // Override me!
        virtual void update() {}

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
        Block(Rectangle rectangle, Texture2D texture): 
            Node(rectangle, texture) {}
};

class Player:
    public Node {
    
    protected:
        Camera2D camera;
    
    public:
        Player(Rectangle rectangle, Texture2D texture): 
            Node(rectangle, texture) {
                this->camera = (Camera2D){
                    (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2},
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


int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    Texture2D blockTexture = LoadTexture("assets/tiles/block.png");
    Texture2D playerTexture = LoadTexture("assets/tiles/player.png");

    std::vector<std::shared_ptr<Node>> nodes{};
    nodes.push_back(std::make_shared<Block>(
        (Rectangle){100, 100, 32, 32},
        blockTexture
    ));

    auto player = std::make_shared<Player>(
        (Rectangle){100, 100, 32, 32},
        playerTexture
    );

    nodes.push_back(player);

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(player->getCamera());

                // Drawing nodes
                for (std::shared_ptr node: nodes) {
                    node->draw();
                }

                // Updating nodes
                for (std::shared_ptr node: nodes) {
                    node->update();
                }

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();
}
