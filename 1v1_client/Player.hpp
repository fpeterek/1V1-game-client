//
//  Player.hpp
//  1v1_client
//
//  Created by Filip Peterek on 24/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"


class Player : public sf::Sprite {

    char _hp;
    sf::Texture _spriteSheet;
    
public:
    
    Player(std::string & spriteSheet);
    Player();
    
    void setHp(char hp);
    char getHp();

};

#endif /* Player_hpp */
