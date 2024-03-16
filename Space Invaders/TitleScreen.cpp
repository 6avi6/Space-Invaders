#include "TitleScreen.hpp"

TitleScreen::TitleScreen() {
    this->initWindow();
    this->initTitleScreen("Assets/Texture/titleScreen.png");
    this->initMenu();
}

TitleScreen::~TitleScreen() {}

void TitleScreen::display() {
    // Clear the window
    this->window->clear();

    // Draw the title screen sprite
    this->window->draw(this->titleSprite);
    //Drawing menu
    this->window->draw(this->playButton);

    // Display everything
    this->window->display();
}

void TitleScreen::openGame()
{
    // Main loop
    while (this->GameWindow->isOpen()) {
       
        this->handleInput();
        this->GameWindow->clear();
        
        
        this->window->draw(titleSprite);

        this->window->draw(this->playButton);

        // Display everything
        this->GameWindow->display();


    }
}

void TitleScreen::handleInput() {
    // Check for keyboard input to start the game
    sf::Event event;
    while (this->window->pollEvent(event)) {
        //if ESC or window cross is clicked it closed window
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed) {
            this->window->close();
        }

        // Check for mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
           
            // Check if the mouse click is inside the play button
            sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (this->isInside(mousePosition, this->playButton)) {
                std::cout << "Play" << std::endl;
            }
        }
    }
}

void TitleScreen::initTitleScreen(std::string wallpaperPath)
{
    // Load title screen texture
    if (!titleTexture.loadFromFile(wallpaperPath)) {
        // Handle error if texture loading fails
        // For now, let's just print an error message
        std::cout << "Failed to load title screen texture! "<< wallpaperPath << std::endl;
    }
    
    
    // Set title screen sprite texture
    this->titleSprite.setTexture(this->titleTexture);

    //Setting wallpaper on full screen
    this->titleSprite.scale(this->window->getSize().x/ this->titleTexture.getSize().x, this->window->getSize().y / this->titleTexture.getSize().y);
}

void TitleScreen::initWindow()
{
     this->GameWindow = new Window(800, 600, "Space Invaders");
    this->window=&(this->GameWindow->window);
}



void TitleScreen::initMenu()
{
    // Configure play button
    this->playButton.setSize(sf::Vector2f(200.f, 50.f));
    //setting center of button
    this->playButton.setOrigin(this->playButton.getSize().x/2, this->playButton.getSize().y / 2);
   //setting position of button
    this->playButton.setPosition((this->window->getSize().x / 2), (this->window->getSize().y / 2) +80);
    this->playButton.setFillColor(sf::Color(17, 92, 19));
}

bool TitleScreen::isInside(const sf::Vector2f& point, const sf::RectangleShape& rectangle) {
    sf::FloatRect rect = rectangle.getGlobalBounds();
    return rect.contains(point);
}