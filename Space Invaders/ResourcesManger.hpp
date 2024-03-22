#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

import <SFML/Graphics.hpp>;
import <iostream>;

class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance; // Static local instance ensures it's created once
        return instance;
    }

    sf::Font& getFont() {
        return font;
    }

private:
    ResourceManager() {
       this->font
    }
    void initFont() {
        if (!font.loadFromFile("Assets/Fonts/slkscre.ttf")) { // Replace "arialbd.ttf" with the path to your bold font file
            // Error handling: Failed to load font
            std::cout << "ERROR::RESOURCESMANAGER::INITFONT::'font SYNNova loading failure'";
        }
    }

    sf::Font font;
};
#endif // !RESOURCEMANAGER_HPP

