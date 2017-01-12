//
//  request.hpp
//  1v1_client
//
//  Created by Filip Peterek on 27/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef request_hpp
#define request_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Player.hpp"

/* Client's request, that is sent to the server */

class Request {
    
    std::string _rawRequest;
    
public:
    
    Request();
    Request(const std::string & events);
    void createRequest(const std::string & events);
    std::string & getRequest();
    
};




#endif /* request_hpp */
