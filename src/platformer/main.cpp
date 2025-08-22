#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <vector>

#include <iostream>

#define LOG(message) std::cout << message <<  std::endl;

class Node {
        protected:
            std::vector<std::shared_ptr<Node>> children;

        public:
            virtual ~Node() = default;

            std::vector<std::shared_ptr<Node>> getChildren() {
                return this->children;
            }

            std::shared_ptr<Node> getChild(int index) {
                return this->children.at(index);
            }

            void addChild(std::shared_ptr<Node> child) {
                this->children.push_back(child);
            }

            virtual void dropChild(int index) {
                this->children.erase(this->children.begin() + index);
            }

            virtual void update() {
                for (auto node: this->children) {
                    node.get()->update();
                }
            }

            virtual void draw() {
                for (auto node: this->children) {
                    node.get()->draw();
                }
            }
};

class Sprite:
    public Node {

    protected:
        Vector2 position;
        Texture2D& texture;

    public:
        Sprite(Vector2 position, 
            Texture2D& texture):
            position(position), texture(texture) {}

        virtual void draw() override {
            // LOG("Drawing Sprite!")

            // Drawing the texture
            DrawTexture(
                this->texture,
                this->position.x,
                this->position.y,
                WHITE
            );

            // Drawing the children
            Node::draw();
        }
};

class Body:
    public Sprite {

    protected:
        Rectangle shape;

    public:
        Body(Vector2 position, 
            Texture2D texture,
            Rectangle shape):
                Sprite(position, texture), shape(shape) {}

};

class PhysicBody:
    public Body {

    protected:
        Vector2 velocity;
        float mass;
    
    public:
        PhysicBody(Vector2 position, 
            Texture2D texture,
            Rectangle shape,
            Vector2 velocity,
            float mass):
                Body(position, texture, shape), velocity(velocity), mass(mass) {}

};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    Texture2D texture = LoadTexture("assets/block.png");

    Node scene{};

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Updating
            scene.update();
            
            // Drawing
            // scene.draw();

        EndDrawing();
    }

    CloseWindow();
}