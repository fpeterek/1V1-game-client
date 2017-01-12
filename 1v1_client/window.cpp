//
//  window.cpp
//  1v1_client
//
//  Created by Filip Peterek on 21/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "window.hpp"

void Window::initControls() {
    
    /* I want the map to be const, just to be sure, const_cast allows me to initialize and */
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

void Window::initText() {
    
    auto init = [&] (sf::Text & text) -> void {
        
        text.setFont(_font);
        // Background colors are 20, BD, FC
        text.setColor(sf::Color(~(char)0x20, ~(char)0xBD, ~(char)0xFC));
        text.setCharacterSize(18 * _scale);
        text.setString("0");
        
    };
    
    init(std::get<0>(_text));
    init(std::get<1>(_text));
    
    std::get<0>(_text).setPosition(5 * _scale, 5 * _scale);
    
    std::get<1>(_text).setOrigin(std::get<1>(_text).getLocalBounds().width, 0);
    std::get<1>(_text).setPosition( (800 - 5) * _scale, 5 * _scale);
    
}

void Window::initialize() {
    
    sf::VideoMode vm = sf::VideoMode::getFullscreenModes()[0];
    
    /* 16:9 ratio */
    vm.height = vm.width / 16 * 9;
    _scale = vm.width / 800.f;
    
    create(vm, "Neckbeard 1v1", sf::Style::Fullscreen);
    
    _text = std::make_tuple(sf::Text(), sf::Text());
    
    if (not _font.loadFromFile(resourcePath() + "Inconsolata.ttf")) {
        throw std::runtime_error("Error loading font Inconsolata.ttf. ");
    }
    
    initText();
    
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

void Window::updateText() {
    
    std::get<0>(_text).setString( std::to_string( _players[0].get().getMatchesWon() ) );
    std::get<1>(_text).setString( std::to_string( _players[1].get().getMatchesWon() ) );
    
    std::get<1>(_text).setOrigin(std::get<1>(_text).getLocalBounds().width, 0);
    std::get<1>(_text).setPosition( (800 - 5) * _scale, 5 * _scale);
    
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
    
    updateText();
    draw(std::get<0>(_text));
    draw(std::get<1>(_text));
    
    
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
