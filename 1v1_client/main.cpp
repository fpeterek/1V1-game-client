
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

#include "Client.hpp"

#define PORT_CLIENT 60001
#define PORT_SERVER 60000

sf::IpAddress get_ip() {
    
    std::string str;
    sf::IpAddress ip;
    while (true) {
        
        std::cout << "IP Address: ";
        std::cin >> str;
        
        try {
            
            ip = sf::IpAddress(str);
            break;
            
        } catch (std::runtime_error & e) {
            
            std::cout << e.what() << std::endl;
            
        }
        
    }
    
    return ip;
    
}

int main(int argc, const char * argv[]) {
    
    
    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    /*
     sf::Font font;
     if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
     return EXIT_FAILURE;
     }
     sf::Text text("Hello SFML", font, 50);
     text.setColor(sf::Color::Black);
     */
    
    try {
        
        sf::IpAddress ip = get_ip();
        Client(ip, PORT_CLIENT, PORT_SERVER);
        
    } catch (std::runtime_error & e) {
        
        std::cout << e.what() << std::endl;
        
    }
    
    /*
    
     while (window.isOpen()) {
     
         sf::Event event;
         while (window.pollEvent(event)) {
         
             if (event.type == sf::Event::Closed) {
                 window.close();
             }
             
             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                 window.close();
             }
         
         }
         
         window.clear();
         window.display();
     
     }
     
     */
    
}