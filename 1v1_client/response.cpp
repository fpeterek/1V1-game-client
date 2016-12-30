//
//  response.cpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "response.hpp"

std::array<std::string, 4> splitResponse(const std::string & response) {
    
    std::array<std::string, 4> data;
    
    size_t start = 0;
    size_t end = 0;
    
    for (char i = 0; i < 4; ++i) {
        
        end = response.find("}", start) + 1;
        if (end == std::string::npos) {
            data[i] = "{}";
        }
        data[i] = response.substr(start, end - start);
        start = end;
        
    }
    
    return data;
    
}

std::vector<std::string> splitString(const std::string & string, std::string delimiter) {
    
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = 0;
    
    while ((end = string.find(delimiter, start)) != std::string::npos) {
        
        token = string.substr(start, end - start);
        tokens.emplace_back(token);
        start = ++end;
        
    }
    
    tokens.emplace_back(string.substr(start));
    
    return tokens;
    
}

entity::entity(std::string & serverData) {
    
    serverData = serverData.substr(1, serverData.size());
    serverData.erase(0, 1);
    serverData.pop_back();
    
    isValid = true;

    if (serverData == "") {
        isValid = false;
        return;
    }
    
    std::vector<std::string> values = splitString(serverData, ",");
    
    if (values.size() != 4) {
        isValid = false;
        return;
    }
    
    try {
        pos.x = std::stoi(values[0]);
        pos.y = std::stoi(values[1]);
    } catch (std::runtime_error & e) {
        isValid = false;
        return;
    }
    
    if (values[2] == "l") {
        dir = direction::left;
    } else if (values[2] == "r") {
        dir = direction::right;
    } else {
        isValid = false;
        return;
    }
    
    try {
        hp = std::stoi(values[3]);
    } catch (std::runtime_error & e) {
        isValid = false;
        return;
    }
    
}

Response::Response() {}

void Response::parseResponse() {
    
    _entities = std::map<std::string, entity>();
    std::array<std::string, 4> data = splitResponse(_rawResponse);
    
    _entities.emplace("p1", entity(data[0]));
    _entities.emplace("p2", entity(data[1]));
    _entities.emplace("d1", entity(data[2]));
    _entities.emplace("d2", entity(data[3]));
    
}

const entity & Response::getEntity(const char * entityName) {
    
    std::string name = entityName;
    return _entities.at(name);
    
}

const entity & Response::getEntity(std::string & entityName) {
    
    return _entities.at(entityName);
    
}

Response::Response(const char * serverResponse) {
    
    setResponse(serverResponse);
    
}

Response::Response(std::string & serverResponse) {
    
    setResponse(serverResponse);
    
}

void Response::setResponse(std::string & serverResponse) {
    
    _rawResponse = serverResponse;
    parseResponse();

}

void Response::setResponse(const char * serverResponse) {
    
    _rawResponse = serverResponse;
    parseResponse();

}
