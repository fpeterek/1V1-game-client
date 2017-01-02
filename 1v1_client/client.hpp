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
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "window.hpp"
#include "Player.hpp"
#include "request.hpp"
#include "response.hpp"

class Client {
    
    unsigned short _port, _serverPort;
    sf::IpAddress _ip;
    sf::UdpSocket _socket;
    
    sf::Clock _clock;
    
    /* Making this an attribute so the program doesn't have to reconstruct and allocate  */
    /* memory every time the client accepts a server response                            */
    Response _serverResponse;
    Request _request;
    
    Player _player;
    Player _player2;
    
    char _receivedData[1024];
    
    Window _window;
    
    void receiveData();
    void parseData(std::string & data);
    void update();
    
    void sendRequest(const sf::Event & event);
    
    void mainLoop();
    
public:
    
    Client(sf::IpAddress & ip, unsigned short portClient, unsigned short portServer);
    
};

#endif /* client_hpp */
