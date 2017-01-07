//
//  request.cpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "request.hpp"

Request::Request() {
    _rawRequest = "{}";
}

Request::Request(const std::string & events) {
    createRequest(events);
}

void Request::createRequest(const std::string & events) {
    
    _rawRequest = "{" + events + "}";
    
}

std::string & Request::getRequest() {
    return _rawRequest;
}
