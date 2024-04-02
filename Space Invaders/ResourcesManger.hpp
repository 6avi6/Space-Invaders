#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP
#include <queue>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <iostream>

class ResourceManager {
public:

    static ResourceManager& getInstance() {
        static ResourceManager instance; // Static local instance ensures it's created once
        return instance;
    }

    sf::Font& getFont() {
        return font;
    }
    void readTopScores(std::string path) {
        std::ifstream file(path); // Open the file for reading

        if (!file.is_open()) {
            std::cerr << "RESOURCESMANAGER::readTopScores(std::string path)::Error: 'Could not open the file.'" << std::endl;
            
        }
        else {
            
            std::string name;
            int score;
            while (file >> score >> name) {

                this->topScores.push(std::make_pair( score, name));
                
            }

            file.close();
        }


    }
    void addNewScore(int score, std::string playerName) {
        this->topScores.push(std::make_pair(score, playerName));
    }
    void writeScore(std::string path) {
        std::ofstream outFile(path);
        if (!outFile.is_open()) {
            std::cout << "ERROR::RESOURCESMANAGER::writeScore(std::string path)::'cant open the file' "<< path<<std::endl;
            
        }
        else {
            // Write the contents of the priority queue to the file
            int counter{ 0 };
            while (!this->topScores.empty() && counter<10) {
                outFile << this->topScores.top().first << " " << this->topScores.top().second << std::endl;
                this->topScores.pop();
                counter++;
            }


            outFile.close();
        }
    }

    void displayOnConsoleScores() {
        
        std::priority_queue<std::pair<int, std::string>> pqCopy = topScores;
        while (!pqCopy.empty()) {
             std::cout<< pqCopy.top().first << " " << pqCopy.top().second << std::endl;
             pqCopy.pop();
        }
    }
    std::priority_queue<std::pair<int, std::string>> getTopScores() {
       return this->topScores;
    }
   
    const int getLastScore() {
        int lastScore=0;
        std::priority_queue<std::pair<int, std::string>> pqCopy = topScores;

        if(pqCopy.size()<10)
        while (!pqCopy.empty()) {
            lastScore = pqCopy.top().first;
            pqCopy.pop();
        }

        return lastScore;
    }
private:
    std::priority_queue<std::pair<int, std::string>> topScores;

    ResourceManager() {
        
        this->readTopScores("Game Data/topScores.txt");
        //this->displayOnConsoleScores();
        this->initFont();
    }
    void initFont() {
        if (!font.loadFromFile("Assets/Fonts/slkscre.ttf")) { // Replace "arialbd.ttf" with the path to your bold font file
            // Error handling: Failed to load font
            std::cout << "ERROR::RESOURCESMANAGER::INITFONT::'font SYNNova loading failure'" << std::endl;
        }
    }
    ~ResourceManager() {
        this->writeScore("Game Data/topScores.txt");
    }

    sf::Font font;
};
#endif // !RESOURCEMANAGER_HPP

