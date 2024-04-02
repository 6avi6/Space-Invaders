#include "TitleScreen.hpp"

TitleScreen::TitleScreen():
resources(ResourceManager::getInstance())
{
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
    this->window->draw(this->playButtonText);
    
    this->window->draw(this->scoresButton);
    this->window->draw(this->scoresButtonText);

    this->window->draw(this->quitButton);
    this->window->draw(this->quitButtonText);


   
}

void TitleScreen::openGame()
{
    // Main loop
    while (this->GameWindow->isOpen()) {
       
        this->handleInput();
        this->GameWindow->clear();
        
        
        

        this->display();
       
        // Display everything
        this->GameWindow->display();


    }
}

void TitleScreen::handleInput() {
    // Check for keyboard input to start the game
    sf::Event event;
    while (this->window->pollEvent(event)) {
        //if ESC or window cross is clicked it closed window
        if ( event.type == sf::Event::Closed /* || event.key.code == sf::Keyboard::Escape */ ) {
            this->window->close();
        }
        
        // Check for mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
           
            // Check if the mouse click is inside the play button
            sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (this->isInside(mousePosition, this->playButton)) {
                
                this->initGame();
                game->run();

                if (game->getScore() > this->resources.getLastScore()) {
                    TextInput writeNewScoreWindow(this->window, &font);
                    writeNewScoreWindow.run();
                    if(writeNewScoreWindow.getText()!="")
                    this->resources.addNewScore(game->getScore(), writeNewScoreWindow.getText());
                    
                }

                delete game;
            }
            if (isInside(mousePosition, this->quitButton)) {
                this->window->close();
            }
            if (isInside(mousePosition, this->scoresButton)) {
                TableScore tableScore(this->window,this->resources.getTopScores(),&font);
                tableScore.open();
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
        std::cout << "TITLESCREEN::initTitleScreen(std::string wallpaperPath)::'Failed to load title screen texture!' " << wallpaperPath << std::endl;
    }
    else {

        // Set title screen sprite texture
        this->titleSprite.setTexture(this->titleTexture);

        //Setting wallpaper on full screen
        this->titleSprite.scale(this->window->getSize().x / this->titleTexture.getSize().x, this->window->getSize().y / this->titleTexture.getSize().y);
        this->titleSprite.setPosition(0,-120);
    }
}

void TitleScreen::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
     this->GameWindow = new Window(800, 600, "Space Invaders" ,settings);
    this->window=&(this->GameWindow->window);
   

    //setting window icon
    
     // Load the icon image
    sf::Image icon;
    if (!icon.loadFromFile("Assets/Texture/windowIcon.png")) {
        // Handle error if loading fails
        // For now, let's just print an error message
        std::cout << "TITLESCREEN::initWindow()::'Failed to load icon image!'" << std::endl;
    }
    else
    this->GameWindow->getWindow().setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
   
}



void TitleScreen::initMenu()
{
    this->initButtons();

}

void TitleScreen::initButtons()
{
    if (!this->font.loadFromFile("Assets/Fonts/slkscre.ttf")) { // Replace "arialbd.ttf" with the path to your bold font file
        // Error handling: Failed to load font
        std::cout << "ERROR::TITLESCREEN::CREATEPLAYBUTTONTEXT()::'font SYNNova loading failure'"<<std::endl;
    }
    // Configure play button
    this->playButton.setSize(sf::Vector2f(400.f , 100.f ));
    //setting center of button
    this->playButton.setOrigin(this->playButton.getLocalBounds().getSize().x / 2, this->playButton.getLocalBounds().getSize().y / 2);
    //setting position of button
    this->playButton.setPosition((this->window->getSize().x / 2), (this->window->getSize().y / 2)  );
    this->playButton.setFillColor(sf::Color(25, 1, 1, 220));
    this->playButtonText.setPosition((this->window->getSize().x / 2), (this->window->getSize().y / 2) - 12);

    this->playButtonText.setFont(this->font);
    this->playButtonText.setString("Play");
    this->playButtonText.setFillColor(sf::Color::White);
    this->playButtonText.setCharacterSize(30);
    this->playButtonText.setOrigin(playButtonText.getLocalBounds().getSize().x / 2, this->playButtonText.getLocalBounds().getSize().y / 2);

    //init scores
    this->scoresButton.setSize(sf::Vector2f(190,50 )); // Adjust the size as needed
    this->scoresButton.setFillColor(sf::Color::Green); // Adjust color as needed
    this->scoresButton.setOrigin(this->scoresButton.getLocalBounds().getSize().x, 0);
    this->scoresButton.setPosition(this->window->getSize().x/2 +(this->playButton.getLocalBounds().getSize().x/2),( this->window->getSize().y*0.5) + this->playButton.getLocalBounds().getSize().y * 0.6);
 
    this->scoresButtonText.setFont(this->font);
    this->scoresButtonText.setString("Scores");
    this->scoresButtonText.setCharacterSize(24);
    this->scoresButtonText.setFillColor(sf::Color::White);
    this->scoresButtonText.setOrigin(scoresButtonText.getLocalBounds().getSize().x / 2, this->scoresButtonText.getLocalBounds().getSize().y / 2);
    
    this->scoresButtonText.setPosition(this->scoresButton.getPosition().x- this->scoresButton.getLocalBounds().getSize().x / 2, this->scoresButton.getPosition().y+10+this->scoresButtonText.getLocalBounds().getSize().y / 2);


   

    // Initialize quit button
    this->quitButton.setSize(sf::Vector2f(190, 50)); // Adjust the size as needed
    this->quitButton.setFillColor(sf::Color::Red); // Adjust color as needed
    this->quitButton.setOrigin(0, 0);
    this->quitButton.setPosition(this->window->getSize().x / 2 - (this->playButton.getLocalBounds().getSize().x / 2), (this->window->getSize().y * 0.5) + this->playButton.getLocalBounds().getSize().y * 0.6);

    this->quitButtonText.setFont(this->font);
    this->quitButtonText.setString("Quit");
    this->quitButtonText.setCharacterSize(24);
    this->quitButtonText.setFillColor(sf::Color::White);
    this->quitButtonText.setOrigin(this->quitButtonText.getLocalBounds().getSize().x / 2, this->quitButtonText.getLocalBounds().getSize().y / 2);
    this->quitButtonText.setPosition(this->quitButton.getPosition().x + (this->quitButton.getLocalBounds().getSize().x / 2), this->quitButton.getPosition().y + 10 + (this->quitButtonText.getLocalBounds().getSize().y / 2));

}

bool TitleScreen::isInside(const sf::Vector2f& point, const sf::RectangleShape& rectangle) {
    sf::FloatRect rect = rectangle.getGlobalBounds();
    return rect.contains(point);
}

void TitleScreen::initGame()
{
    this->game = new Game(this->window);
}
