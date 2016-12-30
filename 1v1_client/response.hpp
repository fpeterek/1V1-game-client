//
//  response.hpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef response_hpp
#define response_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

std::array<std::string, 4> splitResponse(const std::string & response);

std::vector<std::string> splitString(const std::string & string, std::string delimiter);

enum class direction {
    left,
    right
};

struct entity {
    
    sf::Vector2i pos;
    direction dir;
    char hp;
    bool isValid;
    
    entity(std::string & serverData);
    
};

/* Server's response, that contains entity info */

class Response {
    
    std::string _rawResponse;
    std::map<std::string, entity> _entities;
    void parseResponse();
    
public:
    
    Response();
    Response(std::string & serverResponse);
    Response(const char * serverResponse);
    
    void setResponse(std::string & serverResponse);
    void setResponse(const char * serverResponse);
    
    const entity & getEntity(std::string & entityName);
    const entity & getEntity(const char * entityName);
    
};

#endif /* response_hpp */
