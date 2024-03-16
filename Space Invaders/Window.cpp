#include "Window.hpp"

Window::Window(int width, int height,  std::string title) : window(sf::VideoMode(width, height), title) {}

Window::~Window() {}

//getter
bool Window::isOpen() const {
    return window.isOpen();
}

void Window::clear(const sf::Color& color) {
    window.clear(color);
}

void Window::display() {
    window.display();
}

void Window::close() {
    window.close();
}

//modifficator
sf::RenderWindow& Window::getWindow() {
    return window;
}
