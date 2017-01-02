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

#include "response.hpp"


class Player : public sf::Sprite {

    char _hp;
    
    /* This is a different scale than the one in sf::Sprite, this is sf::RenderWindow's scale and it's */
    /* used to determine the sprites position, rather than size                                        */
    float _scale;
    
public:

    Player(sf::Texture & texture);
    Player();
    
    void changeScale(float newScale);
    void update(const entity & newInfo);
    void setHp(char hp);
    char getHp();

};

#endif /* Player_hpp */
