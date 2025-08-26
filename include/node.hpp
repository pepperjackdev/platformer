#pragma once

#include <string>
#include <format>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <optional>

#include <raylib.h>

class Node {
    protected:
        std::string name;
        std::map<std::string, std::shared_ptr<Node>> children;
        Vector2 position;

    public:
        Node(std::string name, Vector2 position = (Vector2){0, 0});

        std::string& getName();
        void setName(std::string name);

        void addChild(std::shared_ptr<Node> node);
        std::shared_ptr<Node> newChild(std::shared_ptr<Node> node);
        std::map<std::string, std::shared_ptr<Node>>& getChildren();
        std::shared_ptr<Node> getChild(std::string name);
        void dropChild(std::string& name);

        Vector2 getPosition();
        void setPosition(Vector2 position);

        virtual void update();
        virtual void draw();
};