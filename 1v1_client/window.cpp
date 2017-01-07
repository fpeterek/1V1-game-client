//
//  window.cpp
//  1v1_client
//
//  Created by Filip Peterek on 21/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "window.hpp"

void Window::initControls() {
    
    /* I want the map to be const, just to be sure, const_cast allows me to initialize it, */
    /* modify it, while keeping it const                                                   */
    
    const std::map<sf::Keyboard::Key, std::string> & controlsRef = _controls;
    
    const_cast<std::map<sf::Keyboard::Key, std::string>&>(controlsRef) = std::map<sf::Keyboard::Key, std::string>({
        { sf::Keyboard::Key::Up    , "j" }, // Jump
        { sf::Keyboard::Key::Left  , "l" }, // Go left
        { sf::Keyboard::Key::Right , "r" }, // Go right
        { sf::Keyboard::Key::Space , "a" }, // Attack
        { sf::Keyboard::Key::R     , "d" }, // Throw a dorito
        { sf::Keyboard::Key::E     , "t" }  // Teleport behind. Nothing personnel, though.
    });
    
}

void Window::initialize() {
    
    sf::VideoMode vm = sf::VideoMode::getFullscreenModes()[0];
    
    /* 16:9 ratio */
    vm.height = vm.width / 16 * 9;
    _scale = vm.width / 800.f;
    
    create(vm, "Neckbeard 1v1", sf::Style::Fullscreen);
    
    loadTexture("background.png");
    loadTexture("ground.png");
    loadTexture("middle_platform.png");
    loadTexture("sidewalls.png");
    loadTexture("spritesheet.png");
    
    initSprites();
    initControls();
    
}

void Window::initSprites() {
    
    /* Background */ {
    
        _background.setTexture(_textures[0]);
        /* Set scale so that a 32 * 32 texture streches across the entire screen */
        _background.setScale(800.f / 32.f * _scale, 450.f / 32.f * _scale);
    
    }
    
    /* Ground */ {
        
        sf::Sprite ground;
        ground.setScale(_scale, _scale);
        ground.setTexture(_textures[1]);
        ground.setPosition(0, (450 - 64) * _scale);
        _sprites.emplace_back(ground);
        
    }
    
    /* Platform */ {
    
        sf::Sprite platform;
        platform.setScale(_scale, _scale);
        platform.setTexture(_textures[2]);
        platform.setOrigin(384 / 2, 0);
        platform.setPosition(400 * _scale, 250 * _scale);
        _sprites.emplace_back(platform);
    
    }
    
    /* Sidewalls */ {
        
        sf::Sprite sidewall;
        sidewall.setTexture(_textures[3]);
        sidewall.setScale(_scale, _scale);
        sidewall.setPosition(0, (450 - 352) * _scale);
        _sprites.emplace_back(sidewall);
        
        sf::Sprite sidewall2(sidewall);
        sidewall2.setPosition((800 - 96) * _scale, (450 - 352) * _scale);
        _sprites.emplace_back(sidewall2);
        
    }
    
}

void Window::loadTexture(const char * textureName) {
    
    sf::Texture temp;
    
    if (not temp.loadFromFile( resourcePath() + textureName )) {
        
        std::string error_message = "Error loading texture ";
        error_message += textureName;
        
        throw std::runtime_error(error_message);
        
    }
    
    _textures.emplace_back(temp);
    
}

void Window::render() {
    
    clear();
    
    draw(_background);
    
    for (auto & sprite : _sprites) {
        draw(sprite);
    }
    
    for (auto & player : _players) {
        draw(player.get());
    }
    
    display();
    
}

sf::Texture & Window::getSpritesheet() {
    
    return _textures[4];
    
}

void Window::addPlayer(Player & player) {
    
    std::reference_wrapper<Player> ref = player;
    _players.emplace_back(ref);
    
}

std::string Window::getEvents() {
    
    std::string events;
    sf::Event event;
    while (pollEvent(event)) {
        
        if (event.type == sf::Event::Closed) {
            close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            close();
        }
     
        /*
        try {
            events.insert( _controls.at(event.key.code) );
        } catch (std::out_of_range & e) {
            // Do nothing /
            continue;
        }*/
        
    }
    
    for (auto & i : _controls) {
        if (sf::Keyboard::isKeyPressed(i.first)) {
            events += i.second;
        }
    }
    
    return events;

}

bool Window::open() {
    
    return isOpen();
    
}

float Window::getScale() {
    
    return _scale;
    
}
