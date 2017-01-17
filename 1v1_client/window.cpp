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
        { sf::Keyboard::Key::Q     , "d" }, // Throw a dorito
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
    
    _rand = std::mt19937((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
    
    initText();
    
    loadTexture("background.png");
    loadTexture("ground.png");
    loadTexture("middle_platform.png");
    loadTexture("sidewalls.png");
    loadTexture("spritesheet.png");
    loadTexture("Dorito.png");
    loadTexture("Crate.png");
    loadTexture("Cloud.png");
    loadTexture("Cloud Fedora.png");
    
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
        platform.setOrigin(320 / 2, 0);
        platform.setPosition(400 * _scale, 220 * _scale);
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
    
    /* Crates */ {
        
        auto initCrate = [this](int x, int y) -> void {
            
            sf::Sprite crate;
            crate.setTexture(_textures[6]);
            crate.setScale(_scale, _scale);
            
            crate.setPosition(x * _scale, y * _scale);
            
            _sprites.emplace_back(crate);
            
        };
        
        /* Left spawn */
        initCrate(96, 354);
        initCrate(96 + 32, 354);
        initCrate(96 + 64, 354);
        initCrate(96 + 32, 354 - 32);
        initCrate(96, 354 - 32);
        initCrate(96, 354 - 64);
        
        /* Right spawn */
        initCrate(800 - 96 - 32, 354);
        initCrate(800 - 96 - 32, 354 - 64);
        initCrate(800 - 96 - 64, 354 - 32);
        initCrate(800 - 96 - 32, 354 - 32);
        initCrate(800 - 96 - 64, 354);
        initCrate(800 - 96 - 96, 354);
        
        /* Middle */
        initCrate(400 - 50 - 32, 354);
        initCrate(400 + 50, 354);
        
        /* Top */
        initCrate(400 - 32, 194);
        initCrate(400 - 64, 194);
        initCrate(400 - 64, 194 - 32);
        initCrate(400 - 96, 194);
        initCrate(400, 194);
        initCrate(400 + 32, 194);
        initCrate(400 + 32, 194 - 32);
        initCrate(400 + 64, 194);
        
    }
    
    /* Clouds */ {
        
        auto initCloud = [this](int texture) {
            
            Cloud cloud;
            cloud.setTexture(_textures[texture]);
            cloud.setScale(_scale * 2, _scale * 2);
            
            const direction directions[2] = { direction::left, direction::right };
            cloud.dir = directions[_rand() % 2];
            cloud.setPosition((_rand() % 800) * _scale, (_rand() % 200) * _scale);
            
            _clouds.emplace_back(cloud);
            
        };
        
        initCloud(7);
        initCloud(7);
        initCloud(8);
        
    }
    
}

void Window::resetCloud(Cloud & cloud) {
    
    const direction directions[2] = { direction::left, direction::right };
    cloud.dir = directions[_rand() % 2];
    
    if (cloud.dir == direction::left) {
        cloud.setPosition(800 * _scale, (_rand() % 200) * _scale);
    } else {
        cloud.setPosition(-64 * _scale * 2 , (_rand() % 200) * _scale);
    }
    
}

void Window::updateCloud(Cloud & cloud) {

    
    if ( not cloud.getGlobalBounds().intersects(_background.getGlobalBounds()) ) {
        
        resetCloud(cloud);
        
    }
    
    cloud.move(cloud.dir == direction::left ? -0.5f : 0.5f, 0);
    
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
    
    for (auto & cloud : _clouds) {
    
        updateCloud(cloud);
        draw(cloud);
    
    }
    
    for (auto & sprite : _sprites) {
        draw(sprite);
    }
    
    for (auto & player : _players) {
        draw(player.get());
    }
    
    for (auto & i : _otherSprites) {
        draw(i.get());
    }
    
    updateText();
    draw(std::get<0>(_text));
    draw(std::get<1>(_text));
    
    
    display();
    
}

sf::Texture & Window::getSpritesheet() {
    
    return _textures[4];
    
}

sf::Texture & Window::getDoritoSprite() {
    
    return _textures[5];
    
}

void Window::addPlayer(Player & player) {
    
    std::reference_wrapper<Player> ref = player;
    _players.emplace_back(ref);
    
}

void Window::addSprite(sf::Sprite & sprite) {
    
    std::reference_wrapper<sf::Sprite> ref = sprite;
    _otherSprites.emplace_back(ref);
    
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
