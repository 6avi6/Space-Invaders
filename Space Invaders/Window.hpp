#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>


class Window {
public:
    Window(int width, int height, std::string title, sf::ContextSettings settings);
    ~Window();

    bool isOpen() const;
    void clear(const sf::Color& color = sf::Color::Black);
    void display();
    void close();

    sf::RenderWindow& getWindow();
    sf::RenderWindow window;
private:
    
};

#endif // WINDOW_HPP