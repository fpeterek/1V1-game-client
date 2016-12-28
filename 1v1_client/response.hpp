//
//  response.hpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef response_hpp
#define response_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Player.hpp"

enum class direction {
    left,
    right
};

struct entity {
    sf::Vector2i pos;
    direction dir;
    char hp;
};

/* Server's response, that contains entity info */

class Response {
    
    std::string _rawResponse;
    std::map<std::string, entity> _entities;
    
public:
    
    Response(std::string & response);
    Response(const char * response);
    
};

#endif /* response_hpp */
