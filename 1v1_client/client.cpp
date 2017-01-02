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
    float scale = _window.getScale();
    
    _player = Player(_window.getSpritesheet());
    _player2 = Player(_window.getSpritesheet());
    _player.setScale(scale * 3, scale * 3);
    _player2.setScale(scale * 3, scale * 3);
    
    _window.addPlayer(_player);
    _window.addPlayer(_player2);
    
    /* Don't want a blocking socket anymore so we don't wait forever in case no packets are recieved */
    _socket.setBlocking(false);
    
    /* Reset clock before doing anything else */
    _clock.restart();
    
    mainLoop();
    
}

void Client::sleep(const unsigned int milliseconds) {
    
    int timeToSleep = milliseconds - _clock.restart().asMilliseconds();
    std::this_thread::sleep_for( std::chrono::milliseconds(timeToSleep) );
    
}

void Client::receiveData() {
    
    size_t received;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
    
    if (_socket.receive(_receivedData, 1024, received, remoteAddress, remotePort) != sf::Socket::Done) {
        /* Data not recieved, sleep and try again */
        return sleep(15);
    }

    if (remoteAddress != _ip or remotePort != _serverPort) {
        /* Received data from wrong address/port, sleep and try again */
        return sleep(15);
    }
    
    std::string data(_receivedData);
    parseData(data);
    /* Received and parsed data, sleep and repeat */
    sleep(15);
    
}

void Client::parseData(std::string & data) {
    
    _serverResponse.setResponse(data);
    _player.update(  _serverResponse.getEntity("p1") );
    _player2.update( _serverResponse.getEntity("p2") );
    
}

void Client::sendRequest(const sf::Event & event) {
    
    _request.createRequest(event);
    std::string & request = _request.getRequest();
    _socket.send(request.c_str(), request.length(), _ip, _serverPort);
    
}

void Client::mainLoop() {
    
    while (_window.open()) {
        
        _window.render();
        
        sendRequest(_window.getEvent());
        
        receiveData();
        
    }
    
}
