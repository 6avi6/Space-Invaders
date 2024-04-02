#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Window.hpp"

#include "Game.hpp"
#include "ResourcesManger.hpp"
#include "TableScore.h"
#include "TextInput.hpp"
class TitleScreen {
public:
    TitleScreen();
    ~TitleScreen();

    // Method to display the title screen
    void display();
    void openGame();

    
private:
    ResourceManager &resources;
   

    // Method to handle user input
    void handleInput();

    //Methods init variables
    void initTitleScreen(std::string wallpaperPath);
    
    void initWindow();
    Window* GameWindow;
    sf::RenderWindow* window;


    sf::Texture titleTexture;
    sf::Sprite titleSprite;
    
    // Play button
    void initMenu();

    sf::RectangleShape playButton;
    sf::RectangleShape scoresButton;
    sf::RectangleShape quitButton;

    sf::Font font;
    sf::Text playButtonText;
    sf::Text scoresButtonText;
    sf::Text quitButtonText;
   
    void initButtons();
    bool isInside(const sf::Vector2f& point, const sf::RectangleShape& rectangle);
      
    Game* game;
    void initGame();
};

#endif // TITLE_SCREEN_HPP

