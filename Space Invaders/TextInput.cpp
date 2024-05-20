#include "TextInput.hpp"
#include <iostream>

TextInput::TextInput(sf::RenderWindow *window,sf::Font* font,int score) :
    window(window),font(font),score(score)
{
    if (!font) {
        std::cerr << "Null pointer to font." << std::endl;
        return;
    }
    initText();
}

void TextInput::draw(sf::RenderWindow* window) {
    window->draw(titleOfWindow);
    window->draw(gameover);
    window->draw(tscore);
    window->draw(background);
    window->draw(okButton);
    window->draw(sfText);
   
    
}

void TextInput::handleEvent(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (!isInputComplete) {
            if (event.text.unicode == 8 && !text.empty()) { // Backspace
                text.pop_back();
            }
            else if (event.text.unicode >32 && event.text.unicode < 128 && text.length() < maxChars) {
               
                text += static_cast<char>(event.text.unicode);

            }
            sfText.setString(text);
            sfText.setOrigin(sfText.getLocalBounds().getSize().x / 2, sfText.getLocalBounds().getSize().y / 2);

            sfText.setPosition(window->getSize().x / 2, window->getSize().y / 2);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (okButton.getGlobalBounds().contains(mousePos)) {
                isInputComplete = true;
               
            }
        }
    }
}

void TextInput::initText() {
    titleOfWindow.setFont(*(this->font));
    titleOfWindow.setString("Write name of player:");
    titleOfWindow.setCharacterSize(26);
    titleOfWindow.setFillColor(sf::Color::White);
    titleOfWindow.setOrigin(titleOfWindow.getLocalBounds().getSize().x / 2, 0);
    titleOfWindow.setPosition(window->getSize().x / 2,  (window->getSize().y / 2)-80);
    
    gameover.setFont(*(this->font));
    gameover.setString("GAME OVER");
    gameover.setCharacterSize(36);
    gameover.setFillColor(sf::Color::White);
    gameover.setOrigin(gameover.getLocalBounds().getSize().x / 2, 0);
    gameover.setPosition(window->getSize().x / 2, (window->getSize().y *0.1) );

    tscore.setFont(*(this->font));
    tscore.setString("Your Score: "+std::to_string(score));
    tscore.setCharacterSize(26);
    tscore.setFillColor(sf::Color::White);
    tscore.setOrigin(tscore.getLocalBounds().getSize().x / 2, 0);
    tscore.setPosition(window->getSize().x / 2, (window->getSize().y * 0.25));
    
    sfText.setFont(*font);
    sfText.setCharacterSize(24);
    sfText.setFillColor(sf::Color::White);
    sfText.setString("OK");
    sfText.setOrigin(sfText.getLocalBounds().getSize().x / 2, (sfText.getLocalBounds().getSize().y/ 2)+10);
    sfText.setPosition(400.f, 400.f); // Adjust position as needed


  


    // Setting up the background rectangle
    background.setSize(sf::Vector2f(300.f, 50.f));
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);
    background.setOrigin(150.f, 25.f); // Center origin
    background.setPosition(400.f, 300.f); // Adjust position as needed

    // Setting up the "OK" button
    okButton.setSize(sf::Vector2f(100.f, 50.f));
    okButton.setFillColor(sf::Color(7, 125, 19, 100));
    okButton.setOutlineThickness(2.f);
    okButton.setOutlineColor(sf::Color::White);
    okButton.setOrigin(50.f, 25.f); // Center origin
    okButton.setPosition(400.f, 400.f); // Adjust position as needed

}

bool TextInput::inputComplete() const {
    return isInputComplete;
}

const std::string& TextInput::getText() const {
    return text;
}

void TextInput::run()
{
    while (window->isOpen() && !this->isInputComplete) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            this->handleEvent(event);
        }

        

        window->clear();
        
        this->draw(window);
        window->display();
    }
}
