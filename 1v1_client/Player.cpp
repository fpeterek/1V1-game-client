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

void Player::changeScale(float newScale) {
    _scale = newScale;
}

char Player::getHp() {
    return _hp;
}

Player::Player() {}

Player::Player(sf::Texture & texture) {
    
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, 48, 32));
    
}

void Player::update(const entity & newInfo) {
    
    if (not newInfo.isValid) { return; }
    
    setPosition(newInfo.pos.x * _scale, newInfo.pos.y * _scale);
    if (newInfo.dir == direction::left) {
        setTextureRect(sf::IntRect(48, 0, -48, 32));
    } else {
        setTextureRect(sf::IntRect(0, 0, 48, 32));
    }
    setHp(newInfo.hp);
}
