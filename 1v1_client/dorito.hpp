//
//  dorito.hpp
//  1v1_client
//
//  Created by Filip Peterek on 13/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef dorito_hpp
#define dorito_hpp

#include <stdio.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

#include "response.hpp"


class Dorito : public sf::Sprite {
    
public:
    
    Dorito(sf::Texture & texture);
    Dorito();
    
    void update(const entity & newInfo);
    
};


#endif /* dorito_hpp */
