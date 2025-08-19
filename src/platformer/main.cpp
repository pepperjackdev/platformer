#include <raylib.h>
#include <raymath.h>

#include <list>
#include <memory>

class Node {
    private:
        std::list<std::unique_ptr<Node>> children;
    public:
        void addChild(std::unique_ptr<Node> node) {
            this->children.push_back(std::move(node));
        }

        virtual void update() {
            for (std::unique_ptr<Node> &child: this->children) {
                child.get()->update();
            }
        }

        virtual void draw() {
            for (std::unique_ptr<Node> &child: this->children) {
                child.get()->draw();
            }
        }

};

class PhysicNode:
    public Node {

    private:
        Vector2 position;
        Vector2 momentum;
        float mass;
        Texture2D texture;

    public:
        PhysicNode(Vector2 position, Vector2 momentum, float mass, Texture2D texture): 
            position(position), momentum(momentum), mass(mass), texture(texture) {
            }

        Vector2 getPosition() {
            return this->position;
        }

        Vector2 getMomentum() {
            return this->momentum;
        }

        Vector2 getVelocity() {
            return Vector2Scale(this->momentum, 1.0f / this->mass);
        }

        int getMass() {
            return this->mass;
        }

        void update() override {
            this->position = Vector2Add(
                this->position,
                Vector2Scale(
                    this->getVelocity(),
                    GetFrameTime()
                )
            );
        }

        void draw() override {
            DrawTexture(
                texture, 
                this->position.x, 
                this->position.y, 
                WHITE
            );
        }
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    Texture2D texture = LoadTexture("assets/block.png");
    Node scene = Node();
    scene.addChild(std::make_unique<PhysicNode>(
        (Vector2){10, 10},
        (Vector2){1000, 1000},
        1,
        texture
    ));

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Drawing
            scene.draw();

            // Updating
            scene.update();
        EndDrawing();
    }
    CloseWindow();
}
