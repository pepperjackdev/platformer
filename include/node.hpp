#pragma once

#include <string>
#include <format>
#include <memory>
#include <vector>
#include <map>
#include <optional>

#include <raylib.h>

class Node:
    public std::enable_shared_from_this<Node> {

    protected:
        const std::string name;
        std::shared_ptr<Node> parent;
        std::map<std::string, std::shared_ptr<Node>> children;
        Vector2 relative_position;

    public:
        Node(
            std::string name, 
            Vector2 relative_position = (Vector2){0, 0}
        );

        std::string const& get_name();

        std::optional<std::shared_ptr<Node>> get_parent();
        void set_parent(std::shared_ptr<Node> node);

        bool is_root();
        std::shared_ptr<Node> get_root();

        void add_child(std::shared_ptr<Node> node);
        std::map<std::string, std::shared_ptr<Node>> const& get_children();
        std::shared_ptr<Node>& get_child(const std::string& name);
        void drop_child(const std::string& name);

        Vector2 get_relative_position();
        void set_relative_position(Vector2 relative_position);
        Vector2 get_absolute_position();

        virtual void update();
        virtual void draw();

        void operator+=(std::shared_ptr<Node> node);
        std::shared_ptr<Node> operator[](const std::string& name);
        void operator-=(const std::string& name);
};