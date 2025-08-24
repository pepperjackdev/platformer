#pragma once

#include <string>
#include <format>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>

class Node {
    protected:
        std::string name;
        std::vector<std::shared_ptr<Node>> children;

    public:
        Node(std::string name);

        std::string& getName();
        void setName(std::string name);

        std::vector<std::shared_ptr<Node>>& getChildren();
        std::shared_ptr<Node> getChild(std::string name);
        std::optional<std::shared_ptr<Node>> getOptionalChild(std::string name);
        void addChild(std::shared_ptr<Node> node);
        void dropChild(const std::string& name);

        virtual void update();
        virtual void draw();
};