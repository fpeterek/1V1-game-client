//
//  client.cpp
//  1v1_client
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "client.hpp"


Client::Client(sf::IpAddress & ip, unsigned short port, unsigned short portServer) {
    
    _port = port;
    _serverPort = portServer;
    _ip = ip;
    
    /* If you send a request to your own local ip address, your computer receives it as a request  */
    /* from 127.0.0.1, comparing 127.0.0.1 to eg. 192.168.0.69 would yield the result of false and */
    /* cause bugs even though the request came from the same device                                */
    if (_ip == sf::IpAddress::getLocalAddress()) {
        _ip = sf::IpAddress("127.0.0.1");
    }
    
    if (_socket.bind(_port) != sf::Socket::Done) {
        
        throw std::runtime_error("Error binding UDP socket to port " + std::to_string(port));
        
    }
    
    if (_socket.send("connect", 8, _ip, _serverPort) != sf::Socket::Done) {
        
        throw std::runtime_error("Error establishing connection");
        
    }
    
    char data[10];
    size_t received;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
    
    if (_socket.receive(data, 10, received, remoteAddress, remotePort) != sf::Socket::Done) {
        throw std::runtime_error("Error establishing connection");
    }
    
    std::cout << "Received " << received << " bytes from " << remoteAddress.toString() << ":" << remotePort << " - " <<
                 data << std::endl;
    
    /* strcmp returns 0 if strings are equal */
    if (strcmp(data, "connected") or remotePort != _serverPort or remoteAddress != _ip) {
        throw std::runtime_error("Error establishing connection");
    }
    
    std::cout << "Connected" << std::endl;
    
    _window.initialize();
    mainLoop();
    
}

void Client::mainLoop() {
    
    while (true) {
        
        _window.render();
        
    }
    
}
