#include "node.hpp"

Node::Node(std::string name, Vector2 position):
    name(name), position(position) {}

std::string& Node::getName() {
    return this->name;
}

void Node::setName(std::string name) {
    this->name = name;
}

void Node::addChild(std::shared_ptr<Node> node) {
    this->children[node->getName()] = node;
}

std::shared_ptr<Node> Node::newChild(std::shared_ptr<Node> node) {
    this->addChild(node);
    return node;
}

std::map<std::string, std::shared_ptr<Node>>& Node::getChildren() {
    return this->children;
}

std::shared_ptr<Node> Node::getChild(std::string name) {
    // If targets subchild
    auto index = name.find("/");
    if (index != std::string::npos) {
        auto childName = name.substr(0, index);
        auto subchildName = name.substr(index + 1, name.length());
        return this->getChild(childName)->getChild(subchildName);
    }

    // If targets child
    if (this->children.contains(name)) {
        return this->children.at(name);
    } else {
        throw std::logic_error(std::format(
            "Error: node '{}' was not found",
            name
        ));
    }
}

void Node::dropChild(std::string& name) {
    this->children.erase(name);
}

Vector2 Node::getPosition() {
    return this->position;
}

void Node::setPosition(Vector2 position) {
    this->position = position;
}

void Node::update() {
    for (const auto& [_, node]: this->children) {
        node->update();
    }
}

void Node::draw() {
    for (const auto& [_, node]: this->children) {
        node->draw();
    }
}
