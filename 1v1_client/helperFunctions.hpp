//
//  helperFunctions.hpp
//  1v1_client
//
//  Created by Filip Peterek on 22/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef helperFunctions_hpp
#define helperFunctions_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcePath.hpp"

sf::IpAddress get_ip();
void display_error_message(const std::string & message);

#endif /* helperFunctions_hpp */
