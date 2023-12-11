#pragma once

#include <SFML/Graphics.hpp>

namespace NFont {
    sf::Font font;

    void LoadFont() {
        bool flag = font.loadFromFile("/Users/retrobanner/Library/Fonts/JetBrainsMonoNerdFont-Thin.ttf");
        if (!flag) {
            throw std::runtime_error("Font not found");
        }
    }
}; // namespace NFont
