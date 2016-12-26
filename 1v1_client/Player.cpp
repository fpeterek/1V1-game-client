//
//  Player.cpp
//  1v1_client
//
//  Created by Filip Peterek on 24/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Player.hpp"


void Player::setHp(char hp) {
    _hp = hp;
}

char Player::getHp() {
    return _hp;
}

Player::Player() {
    
}

Player::Player(sf::Texture & texture) {
    
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 48, 32));
    
}
