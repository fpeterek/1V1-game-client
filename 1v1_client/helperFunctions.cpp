//
//  helperFunctions.cpp
//  1v1_client
//
//  Created by Filip Peterek on 22/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "helperFunctions.hpp"



void handle_text_input(sf::Event & event, std::string & str) {
    
    if ( ((event.text.unicode >= 48 and event.text.unicode <= 57) or event.text.unicode == 46) and str.length() < 15) {
        str += event.text.unicode;
    }
    
    /* Delete last letter when backspace is pressed */
    
    else if (event.key.code == 8 and str.length()) {
        str = str.substr(0, str.length() - 1);
    }
    
}

bool check_ip(std::string & str) {
    
    /* Tokenization */
    
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = 0;
    
    while ((end = str.find(".", start)) != std::string::npos) {
        
        token = str.substr(start, end - start);
        tokens.emplace_back(token);
        start = ++end;
        
    }
    
    tokens.emplace_back(str.substr(start));
    
    /* Validation */
    
    if (tokens.size() != 4) {
        return false;
    }
    for (auto & tok : tokens) {
        
        try {
            
            int x = std::stoi(tok);
            if (x < 0 or x > 255) {
                return false;
            }
            
        } catch (const std::out_of_range & e) {
            /* Doesn't fit in int */
            return false;
        } catch (const std::invalid_argument & e) {
            /* Isn't a number */
            return false;
        }
        
    }
    
    return true;
    
}

sf::IpAddress get_ip() {
    
    std::string str;
    sf::IpAddress ip;
    
    sf::Event event;
    
    sf::Font font;
    sf::RectangleShape background;
    background.setSize( sf::Vector2f(600, 100) );
    background.setFillColor( sf::Color::White );
    
    sf::Text text;
    
    text.setPosition(0, 15);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
    text.setCharacterSize(30);
    
    sf::Text text2(text);
    text2.setPosition(0, 55);
    
    if (not font.loadFromFile("Resources/LCD_Solid.ttf")) {
        throw std::runtime_error("Error loading font LCD_Solid.ttf. ");
    }
    
    do {
        
        sf::RenderWindow window( sf::VideoMode(600, 100), "IP Address" );
        
        while ( window.isOpen() ) {
            
            while (window.pollEvent(event)) {
                
                if (event.type == sf::Event::Closed) {
                    return sf::IpAddress("0.0.0.0");
                }
                
                if (event.type == sf::Event::TextEntered) {
                    handle_text_input(event, str);
                }
                
                if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Return) {
                    window.close();
                }
                
            }
            
            text.setString("IP Address: " + str);
            
            window.clear();
            window.draw(background);
            window.draw(text);
            window.draw(text2);
            window.display();
            
        }
        
        ip = check_ip(str) ? sf::IpAddress(str) : "0.0.0.0";
        
        /* Set text2 to "Invalid IP Address." If the address was invalid,                     */
        /* program will ask again and display the string                                      */
        /* If the address was valid, the program won't ask again and the string won't display */
        text2.setString("Invalid IP Address.");
        
        str = "";
        
    } while (ip.toString() == "0.0.0.0");
    
    return ip;
    
}

void display_error_message(const std::string & message) {
    
    sf::RenderWindow window( sf::VideoMode(700, 150), "An Error Has Occured" );
    
    sf::Font font;
    sf::RectangleShape background;
    background.setSize( sf::Vector2f(700, 150) );
    background.setFillColor( sf::Color::White );
    
    sf::Text text;
    
    text.setPosition(0, 15);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
    text.setCharacterSize(30);
    
    sf::Text text2(text);
    text2.setPosition(0, 55);
    
    sf::Text text3(text);
    text3.setPosition(0, 95);
    
    if (not font.loadFromFile("Resources/LCD_Solid.ttf")) {
        throw std::runtime_error("Error loading font LCD_Solid.ttf. ");
    }
    
    text.setString("An error has occured...");
    text2.setString(message);
    text3.setString("Press enter to exit.");
    
    sf::Event event;
    
    while ( window.isOpen() ) {
        
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Return) {
                window.close();
            }
            
        }
        
        window.clear();
        window.draw(background);
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.display();
        
    }
    
}
