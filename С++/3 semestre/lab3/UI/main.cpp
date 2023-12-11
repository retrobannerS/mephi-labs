#include "window.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(int argc, char *argv[]) {
    NFont::LoadFont();

    sf::RenderWindow window(sf::VideoMode(1400, 800), "Shop");
    ChooseMode(window);
    window.close();
    return 0;
}