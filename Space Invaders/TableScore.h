#ifndef TABLESCORE_H
#define TABLESCORE_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>
class TableScore {
public:
	TableScore(sf::RenderWindow* window,std::priority_queue<std::pair<int, std::string>> scores,sf::Font *font);
	void open();
private:
	sf::Text titleOfWindow;
	sf::Font* font;
	std::string topScores[10];
	sf::Text scores[10];

	void initScores();

	void displayTableScores();
	sf::RenderWindow* window;
	bool isRunning;
};

#endif // !TABLESCORE_H
