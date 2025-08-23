#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <vector>
#include <optional>

#include <iostream>
#define LOG(string) std::cout << string << std::endl

class Node {
        protected:
            std::shared_ptr<Node> parent;
            std::vector<std::shared_ptr<Node>> children;
            Vector2 position;

        public:
            Node(std::shared_ptr<Node> parent,
                Vector2 position):
                    parent(parent), 
                    position(position) {}

            std::optional<std::shared_ptr<Node>> getParent() {
                return std::make_optional(this->parent);
            }

            std::optional<std::vector<std::shared_ptr<Node>>> getSiblings() {
                if (this->getParent()) {
                    return this->parent->getChildren();
                } else {
                    return std::nullopt;
                }
            }

            std::vector<std::shared_ptr<Node>> getChildren() {
                return this->children;
            }

            std::shared_ptr<Node> getChild(int index) {
                return this->children.at(index);
            }

            void addChild(std::shared_ptr<Node> child) {
                this->children.push_back(child);
            }

            void dropChild(int index) {
                this->children.erase(this->children.begin() + index);
            }

            virtual void update() {
                for (auto node: this->children) {
                    node->update();
                }
            }

            virtual void draw() {
                for (auto node: this->children) {
                    node->draw();
                }
            }
};

class Sprite:
    public Node {

    protected:
        Texture2D texture;

    public:
        Sprite(std::shared_ptr<Node> parent,
            Vector2 position, 
            Texture2D texture):
                Node(parent, position), texture(texture) {}

        virtual void draw() override {
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
        Body(std::shared_ptr<Node> parent,
            Vector2 position, 
            Texture2D texture,
            Rectangle shape):
                Sprite(parent, position, texture), shape(shape) {}

};

class PhysicBody:
    public Body {

    protected:
        Vector2 velocity;
        Vector2 acceleration;
        float mass;
    
    public:
        PhysicBody(std::shared_ptr<Node> parent,
            Vector2 position, 
            Texture2D texture,
            Rectangle shape,
            Vector2 velocity,
            Vector2 acceleration,
            float mass):
                Body(parent, position, texture, shape), 
                velocity(velocity), 
                acceleration(acceleration), 
                mass(mass) {}

        virtual void update() override {
            // TODO: handle collisions

            // Updating velocity
            this->velocity = Vector2Add(
                this->velocity,
                Vector2Scale(
                    this->acceleration,
                    GetFrameTime()
                )
            );

            // Updating position
            this->position = Vector2Add(
                this->position,
                Vector2Scale(
                    this->velocity,
                    GetFrameTime()
                )
            );

            // Updating children
            Body::update();
        }
};

class Entity:
    public PhysicBody {

    public:
        Entity(std::shared_ptr<Node> parent,
            Vector2 position, 
            Texture2D texture,
            Rectangle shape,
            Vector2 velocity,
            Vector2 acceleration,
            float mass):
                PhysicBody(parent,
                    position, 
                    texture, 
                    shape, 
                    velocity, 
                    acceleration, 
                    mass) {}
};

class Player:
    public Entity {

    public:
        Player(std::shared_ptr<Node> parent,
            Vector2 position, 
            Texture2D texture,
            Rectangle shape,
            Vector2 velocity,
            Vector2 acceleration,
            float mass):
                Entity(parent, position, 
                    texture, 
                    shape, 
                    velocity, 
                    acceleration, 
                    mass) {}

        void update() override {
            // Entity update
            Entity::update();
        }
};

int main() {
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 900, "Platformer");

    // Creating main scene
    Node scene(nullptr, (Vector2){0, 0});

    // Adding a child
    Texture2D texture = LoadTexture("assets/block.png");
    scene.addChild(std::make_shared<Player>(
        nullptr,                    // Parent
        (Vector2){100, 100},        // Position
        texture,                    // Texture
        (Rectangle){0, 0, 0, 0},    // Shape
        (Vector2){0, 0},            // Velocity
        (Vector2){0, 0},            // Acceleration
        1                           // Mass
    ));

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Updating
            scene.update();
            
            // Drawing
            scene.draw();

        EndDrawing();
    }

    CloseWindow();
}