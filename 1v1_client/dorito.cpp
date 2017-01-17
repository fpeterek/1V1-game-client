//
//  dorito.cpp
//  1v1_client
//
//  Created by Filip Peterek on 13/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "dorito.hpp"

Dorito::Dorito() {
    setPosition(0, -100);
}

Dorito::Dorito(sf::Texture & texture) {
    
    setPosition(0, -100);
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 16, 16));
    
}

void Dorito::update(const entity & newInfo) {
    
    if (not newInfo.isValid) { return; }
    
    setPosition(newInfo.pos.x * getScale().x, newInfo.pos.y * getScale().y);
    
    if (newInfo.dir == direction::left) {
        
        setTextureRect(sf::IntRect( 16, 0, -16, 16 ));
        
    } else {
        
        setTextureRect(sf::IntRect( 0, 0, 16, 16 ));
        
    }
    
}
