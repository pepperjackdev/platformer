#include "node.hpp"

#include <raymath.h>

Node::Node(std::string name, Vector2 relative_position):
    name(name), relative_position(relative_position) {}

std::string const& Node::get_name() {
    return this->name;
}

std::optional<std::shared_ptr<Node>> Node::get_parent() {
    return this->parent->shared_from_this();
}

void Node::set_parent(std::shared_ptr<Node> node) {
    this->parent = node;
}

bool Node::is_root() {
    return this->parent == nullptr;
}

std::shared_ptr<Node> Node::get_root() {
    for (
        auto node = this->shared_from_this();
        !node->is_root();
        node = node->parent
    ) {
        if (!node->get_parent()) {
            return node;
        }
    }

    throw std::logic_error(
        "Error: root node not found"
    );
}

void Node::add_child(std::shared_ptr<Node> node) {
    this->children[node->get_name()] = node;
    node->set_parent(this->shared_from_this());
}

std::map<std::string, std::shared_ptr<Node>> const& Node::get_children() {
    return this->children;
}

std::shared_ptr<Node>& Node::get_child(const std::string& name) {
    // If targets subchild
    auto index = name.find("/");
    if (index != std::string::npos) {
        auto childName = name.substr(0, index);
        auto subchildName = name.substr(index + 1, name.length());
        return this->get_child(childName)->get_child(subchildName);
    }

    // If targets child
    if (this->children.contains(name)) {
        return this->children[name];
    } else {
        throw std::logic_error(std::format(
            "Error: node '{}' was not found",
            name
        ));
    }
}

void Node::drop_child(const std::string& name) {
    auto node = this->get_child(name);
    node->set_parent(nullptr);
    this->children.erase(name);
}

Vector2 Node::get_relative_position() {
    return this->relative_position;
}

void Node::set_relative_position(Vector2 position) {
    this->relative_position = position;
}

Vector2 Node::get_absolute_position() {
    if (this->is_root()) {
        return this->relative_position;
    } else {
        return Vector2Add(
            this->parent->get_absolute_position(),
            this->relative_position
        );
    }
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

void Node::operator+=(std::shared_ptr<Node> node) {
    this->add_child(node);
}

std::shared_ptr<Node> Node::operator[](const std::string& name) {
    return this->get_child(name);
}

void Node::operator-=(const std::string& name) {
    this->drop_child(name);
}