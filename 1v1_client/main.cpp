
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

#include "client.hpp"
#include "helperFunctions.hpp"

#define PORT_CLIENT 60002
#define PORT_SERVER 60001

/* Debugging macro so I don't have to retype 127.0.0.1 each time I run the client */
// #define AUTOCONNECT_TO_LOCALHOST

int main(int argc, const char * argv[]) {
    
    try {
        
#ifdef AUTOCONNECT_TO_LOCALHOST
        sf::IpAddress ip = "127.0.0.1";
#else
        sf::IpAddress ip = get_ip();
        
        if (ip.toString() == "0.0.0.0") {
            return 0;
        }
#endif
        Client(ip, PORT_CLIENT, PORT_SERVER);
        
    } catch (std::runtime_error & e) {
        
        try {
            
            display_error_message(e.what());
            
        } catch (std::exception) {
        
            std::cout << "An unexpected error has occured while displaying an error." << std::endl;
            std::cout << e.what() << std::endl;
            
        }
        
    }
    
}
