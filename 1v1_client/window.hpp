//
//  window.hpp
//  1v1_client
//
//  Created by Filip Peterek on 21/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef window_hpp
#define window_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "ResourcePath.hpp"

#include "Player.hpp"

/* Don't want to expose any sf::RenderWindow methods, so I'm keeping them private   */
/* This class serves as an interface for sf::RenderWindow that simplifies           */
/* rendering in the rest of the code by hiding loops, scaling, etc.                 */

class Window : sf::RenderWindow {
    
    std::vector<sf::Texture> _textures;
    sf::Sprite _background;
    std::vector<sf::Sprite> _sprites;
    std::vector<Player> _players;
    
    /* Base resolution is 800 * 450, just for reference, so everything can be scaled accordingly */
    float _scale;
    
    void loadTexture(const char * textureName);
    void initSprites();
    
public:
    
    float getScale();
    bool open();
    void handleEvents();
    void initialize();
    void render();
    void addPlayer(Player & player);
    void Display();
    
};


#endif /* window_hpp */
