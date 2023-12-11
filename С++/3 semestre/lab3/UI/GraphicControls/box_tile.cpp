#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "button.cpp"
#include "font.cpp"

struct TBoxTile {
    float X;
    float Y;
    float Dx;
    float Dy;
    uint64_t BoxID;
    std::string BoxName;
    bool Available;
    TButton AvailableButton;
    sf::Texture PictureTexture;
    bool IsPresent;

    TBoxTile() = default;

    TBoxTile(const float dx, const float dy, const uint64_t boxID, const std::string& boxName, const bool available, const sf::Image& img) {
        X = 0;
        Y = 0;
        Dx = dx;
        Dy = dy;
        BoxID = boxID;
        BoxName = boxName;
        Available = available;
        AvailableButton = TButton(0, 0, 0.8 * Dx, 0.2 * Dy, "");

        PictureTexture.loadFromImage(img);

        IsPresent = false;
    }

    void UpdateButtonsPositions() {
        AvailableButton.X = X + 0.1 * Dx;
        AvailableButton.Y = Y + 0.7 * Dy;
    }

    void SetPosition(float x, float y) {
        X = x;
        Y = y;
     
        UpdateButtonsPositions();
    }

    void Draw(sf::RenderWindow& window) {
        sf::RectangleShape rectangle(sf::Vector2f(Dx, Dy));
        rectangle.setPosition(X, Y);
        rectangle.setFillColor(sf::Color::White);

        sf::Text nameText;
        nameText.setFont(NFont::font);
        nameText.setString(BoxName);
        nameText.setCharacterSize(18);
        nameText.setCharacterSize(std::min(1.0, Dx / nameText.getLocalBounds().width * 0.9) * 18.0);
        nameText.setFillColor(sf::Color::Black);
        sf::FloatRect nameTextRect = nameText.getLocalBounds();
        nameText.setOrigin(nameTextRect.left + nameTextRect.width / 2.0, nameTextRect.top);
        nameText.setPosition(X + 0.5 * Dx, Y + 0.54 * Dy);

        sf::Sprite pictureSprite;
        pictureSprite.setTexture(PictureTexture);
        float pictureHeight = pictureSprite.getLocalBounds().height;
        float pictureWidth = pictureSprite.getLocalBounds().width;
        float scale = std::min(0.5f * Dy / pictureHeight, Dx / pictureWidth);
        pictureSprite.setPosition(X + 0.5 * Dx - 0.5 * pictureWidth * scale, Y + 5.f);
        pictureSprite.scale(scale, scale);

        AvailableButton.Label = (Available ? "Available" : "Unavailable");
        
        window.draw(rectangle);
        window.draw(nameText);
        window.draw(pictureSprite);
        AvailableButton.Draw(window);
    }
};

