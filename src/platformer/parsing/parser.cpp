#include "parsing/parser.hpp"

#include <fstream>

Parser::Parser(std::string path):
    source(path) {}

std::shared_ptr<Node> Parser::parse() {
    
}