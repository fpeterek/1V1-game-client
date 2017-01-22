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
        /* Set text color to the opposite color of the background color */
        /* Background color is 0x20, 0xBD, 0xFC                         */
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
    
    if (not _font.loadFromFile(resourcePath() + "LCD_Solid.ttf")) {
        throw std::runtime_error("Error loading font LCD_Solid.ttf. ");
    }
    
    _rand = std::mt19937((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
    
    initText();
    
    loadTexture( "ground.png"          , "ground"       );
    loadTexture( "middle_platform.png" , "platform"     );
    loadTexture( "sidewall2.png"       , "sidewall"     );
    loadTexture( "spritesheet.png"     , "spritesheet"  );
    loadTexture( "Dorito.png"          , "dorito"       );
    loadTexture( "Crate.png"           , "crate"        );
    loadTexture( "Metal Box.png"       , "mdbox"        );
    loadTexture( "Metal Box Dorito.png", "dbox"         );
    loadTexture( "Cloud.png"           , "cloud"        );
    loadTexture( "Cloud Fedora.png"    , "cloud_fedora" );
    loadTexture( "Bush 2.png"          , "bush"        );
    loadTexture( "Tree.png"            , "tree"         );
    loadTexture( "Tree 2.png"           , "tree2"        );
    loadTexture( "Big Tree 2.png"      , "big_tree"     );
    
    initSprites();
    initControls();
    
}

void Window::initSprites() {
    
    auto initSprite = [this](int x, int y, std::string && textureName) -> void {
        
        sf::Sprite sprite;
        sprite.setTexture(_textures[textureName]);
        sprite.setScale(_scale, _scale);
        
        sprite.setPosition(x * _scale, y * _scale);
        
        _sprites.emplace_back(sprite);
        
    };
    
    /* Background */ {
        
        _background.setSize( sf::Vector2f(800, 450) );
        _background.setScale(_scale, _scale);
        _background.setFillColor( sf::Color(0x20, 0xBD, 0xFC) );
    
    }
    
    /* Ground */ {
        initSprite(0, 450 - 64, "ground");
    }
    
    /* Sidewalls */ {
        
        sf::Sprite sidewall;
        sidewall.setTexture(_textures["sidewall"]);
        sidewall.setScale(_scale, _scale);
        sidewall.setPosition(0, (450 - 352) * _scale);
        _sprites.emplace_back(sidewall);
        
        sf::Sprite sidewall2(sidewall);
        sidewall2.setTextureRect(sf::IntRect( 96, 0, -96, 352 ));
        sidewall2.setPosition((800 - 96) * _scale, (450 - 352) * _scale);
        _sprites.emplace_back(sidewall2);
        
    }
    
    /* Trees */ {
        
        auto initTree = initSprite;
        
        initTree(225, 258, "tree");
        initTree(450, 258, "tree2");
        initTree(40, 66, "big_tree");
        
    }
    
    /* Platform */ {
        
        sf::Sprite platform;
        platform.setScale(_scale, _scale);
        platform.setTexture(_textures["platform"]);
        platform.setOrigin(320 / 2, 0);
        platform.setPosition(400 * _scale, 220 * _scale);
        _sprites.emplace_back(platform);
        
    }
    
    /* Bushes */ {
        
        auto initBush = initSprite;
        
        initBush(100, 340 - 16 - 40, "bush");
        initBush(120, 340 - 16 - 20, "bush");
        
        initBush(200, 340 - 16, "bush");
        initBush(340, 340 - 16, "bush");
        initBush(396, 340 - 16, "bush");
        initBush(550, 340 - 16, "bush");
        
        initBush(470, 175 - 16, "bush");
        initBush(250, 175 - 16, "bush");
        initBush(350, 170 - 25, "bush" );
        
    }
    
    /* Crates */ {
        
        auto initCrate = initSprite;
        
        /* Left spawn */
        initCrate(96, 360,           "mdbox");
        initCrate(96 + 32, 360,      "crate");
        initCrate(96 + 64, 360,      "crate");
        initCrate(96 + 32, 360 - 32, "mdbox");
        initCrate(96, 360 - 32,      "dbox");
        initCrate(96, 360 - 64,      "crate");
        
        /* Right spawn */
        initCrate(800 - 96 - 32, 360,      "mdbox");
        initCrate(800 - 96 - 32, 360 - 64, "crate");
        initCrate(800 - 96 - 64, 360 - 32, "crate");
        initCrate(800 - 96 - 32, 360 - 32, "dbox");
        initCrate(800 - 96 - 64, 360,      "crate");
        initCrate(800 - 96 - 96, 360,      "mdbox");
        
        /* Middle */
        initCrate(400 - 50 - 32, 360, "mdbox");
        initCrate(400 + 50, 360,      "crate");
        
        /* Top */
        initCrate(400 - 32, 194,      "mdbox");
        initCrate(400 - 64, 194,      "dbox");
        initCrate(400 - 64, 194 - 32, "dbox");
        initCrate(400 - 96, 194,      "crate");
        initCrate(400, 194,           "crate");
        initCrate(400 + 32, 194,      "dbox");
        initCrate(400 + 32, 194 - 32, "mdbox");
        initCrate(400 + 64, 194,      "crate");
        
    }
    
    /* Clouds */ {
        
        auto initCloud = [this](std::string && texture) {
            
            Cloud cloud;
            cloud.setTexture(_textures[texture]);
            cloud.setScale(_scale * 2, _scale * 2);
            
            const direction directions[2] = { direction::left, direction::right };
            cloud.dir = directions[_rand() % 2];
            cloud.setPosition((_rand() % 800) * _scale, (_rand() % 200) * _scale);
            
            _clouds.emplace_back(cloud);
            
        };
        
        initCloud("cloud");
        initCloud("cloud");
        initCloud("cloud");
        initCloud("cloud_fedora");
        initCloud("cloud_fedora");
        
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

void Window::loadTexture( std::string && textureName, std::string && dictionaryName) {
    
    sf::Texture temp;
    
    if (not temp.loadFromFile( resourcePath() + textureName )) {
        
        std::string error_message = "Error loading texture ";
        error_message += textureName;
        
        throw std::runtime_error(error_message);
        
    }
    
    _textures.emplace(dictionaryName, temp);
    
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
    
    return _textures["spritesheet"];
    
}

sf::Texture & Window::getDoritoSprite() {
    
    return _textures["dorito"];
    
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
