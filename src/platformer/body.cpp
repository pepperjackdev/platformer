#include "body.hpp"

typedef Rectangle Shape;

Body::Body(
    std::string name, 
    Vector2 relative_position, 
    Rectangle shape
): 

Node(name, relative_position), shape(shape) {}