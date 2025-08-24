#include "node.hpp"

Node::Node(std::string name):
    name(name) {}

std::string& Node::getName() {
    return this->name;
}

void Node::setName(std::string name) {
    this->name = name;
}

std::vector<std::shared_ptr<Node>>& Node::getChildren() {
    return this->children;
}

std::optional<std::shared_ptr<Node>> Node::getOptionalChild(std::string name) {
    for (auto node: this->children) {
        if (name == node->getName()) {
            return std::make_optional(node);
        }
    }
    return std::nullopt;
}

std::shared_ptr<Node> Node::getChild(std::string name) {
    for (auto node: this->children) {
        if (name == node->getName()) {
            return node;
        }
    }
    throw std::logic_error(std::format(
        "node with name '{}' not found",
        name
    ));
}

void Node::addChild(std::shared_ptr<Node> node) {
    this->children.push_back(node);
}

void Node::dropChild(const std::string& name) {
    this->children.erase(
        std::remove_if(
            this->children.begin(),
            this->children.end(),
            [&name](const std::shared_ptr<Node>& child) {
                return child->getName() == name;
            }
        ),
        this->children.end()
    );
}

void Node::update() {
    // Updating children
    for (auto node: this->children) {
        node->update();
    }
}

void Node::draw() {
    // Drawing children
    for (auto node: this->children) {
        node->draw();
    }
}