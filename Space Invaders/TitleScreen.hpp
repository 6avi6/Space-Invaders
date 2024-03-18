#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "Window.hpp"

#include "Game.hpp"
#include "iostream"
class TitleScreen {
public:
    TitleScreen();
    ~TitleScreen();

    // Method to display the title screen
    void display();
    void openGame();

    
private:
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
    bool isInside(const sf::Vector2f& point, const sf::RectangleShape& rectangle);
      
    Game* game;
    void initGame();
};

#endif // TITLE_SCREEN_HPP

