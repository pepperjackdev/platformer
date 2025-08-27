#pragma once

#include "node.hpp"

class Body:
    public Node {

    protected:
        Rectangle shape;

    public:
        Body(
            std::string name,
            Vector2 relative_position,
            Rectangle shape
        );

        
};
