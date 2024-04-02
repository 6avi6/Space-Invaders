#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextInput {
private:
    std::string text;
    sf::Text sfText;
    sf::Font* font;
    sf::Text titleOfWindow;
    void initText();
    int maxChars = 5;
    sf::RectangleShape background;
    sf::RectangleShape okButton;
    bool isInputComplete = false;
    sf::RenderWindow* window;
public:

    TextInput(sf::RenderWindow* window,sf::Font* font);
    void draw(sf::RenderWindow* window);
    void handleEvent(sf::Event event);
    bool inputComplete() const;
    const std::string& getText() const;
    void run();
};

#endif // TEXTINPUT_HPP
