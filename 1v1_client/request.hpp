//
//  request.hpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef request_hpp
#define request_hpp

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
};

class Request {
    
    std::string _raw_request;
    
    
};


#endif /* request_hpp */
