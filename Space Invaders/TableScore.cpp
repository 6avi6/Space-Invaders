#include "TableScore.h"

TableScore::TableScore(sf::RenderWindow* window, std::priority_queue<std::pair<int, std::string>> scores,sf::Font* font):
	window(window),isRunning(true), font(font)
{

    //writing top scores
    int i = 0;
    while(!scores.empty() && i<10) {
        // Get the top element (the one with the highest priority)
        std::pair<int, std::string> element = scores.top();

        
        this->topScores[i] = std::to_string(element.first)+" "+ element.second  ;
        // Perform operations with the retrieved data
        

        // Remove the top element
        scores.pop();
        i++;
    }
    this-> initScores();
}

void TableScore::open()
{
    
    while (this->isRunning) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.key.code == sf::Keyboard::Escape)
                this->isRunning = false;
        }

        // Clear the window
        window->clear();

        this->displayTableScores();
        // Display the contents of the window
        window->display();
    }

}


void TableScore::initScores()
{   
    size_t length = std::distance(std::begin(topScores), std::end(topScores));
    float upDonwPadding = (window->getSize().y * 0.8) / length;
    
    titleOfWindow.setFont(*(this->font));
    titleOfWindow.setString("Top Scores");
    titleOfWindow.setCharacterSize(34);
    titleOfWindow.setFillColor(sf::Color::White);
    titleOfWindow.setOrigin(titleOfWindow.getLocalBounds().getSize().x / 2, 0);
    titleOfWindow.setPosition(window->getSize().x / 2,  1* upDonwPadding );


    for (int i=0; i < length; i++) {
        scores[i].setFont(*(this->font));
        scores[i].setString(topScores[i]);
        scores[i].setCharacterSize(24);
        scores[i].setFillColor(sf::Color::White);
        scores[i].setOrigin(scores[i].getLocalBounds().getSize().x / 2, 0);
        scores[i].setPosition(window->getSize().x/2,2*upDonwPadding+upDonwPadding*i);

    }
}

void TableScore::displayTableScores()
{
    size_t length = std::distance(std::begin(topScores), std::end(topScores));
    this->window->draw(this->titleOfWindow);
    for (int i=0; i < length; i++) {
        this->window->draw(this->scores[i]);
        
    }
}
