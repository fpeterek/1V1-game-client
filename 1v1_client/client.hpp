//
//  client.hpp
//  1v1_client
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef client_hpp
#define client_hpp

#include <stdio.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Client {
    
    unsigned short _port, _serverPort;
    sf::IpAddress _ip;
    sf::UdpSocket _socket;
    
public:
    
    Client(sf::IpAddress & ip, unsigned short portClient, unsigned short portServer);
    
};

#endif /* client_hpp */
