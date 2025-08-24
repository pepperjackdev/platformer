#pragma once

#include <fstream>

#include "node.hpp"

class Parser {
    private:
        std::ifstream source;

    public:
        Parser(std::string path);
        std::shared_ptr<Node> parse();
};