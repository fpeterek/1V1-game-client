//
//  request.cpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "request.hpp"

const std::map<sf::Keyboard::Key, std::string> Request::controls = {
    {sf::Keyboard::Key::Up,     "j"}, // jump
    {sf::Keyboard::Key::Left,   "l"}, // go left
    {sf::Keyboard::Key::Right,  "r"}, // go right
    {sf::Keyboard::Key::Space,  "a"}, // attack
    {sf::Keyboard::Key::R,      "d"}, // throw a dorito
    {sf::Keyboard::Key::E,      "t"}  // teleport
};

Request::Request() {
    _rawRequest = "{}";
}

Request::Request(const sf::Event & event) {
    createRequest(event);
}

void Request::createRequest(const sf::Event & event) {
    
    try {
        _rawRequest = "{" + Request::controls.at(event.key.code) + "}";
    } catch (std::out_of_range & e) {
        _rawRequest = "{}";
    }
    
}

const char * Request::getRequest() {
    return _rawRequest.c_str();
}
