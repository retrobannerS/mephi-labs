#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "../Model/item.cpp"
#include "button.cpp"
#include "font.cpp"

struct TItemTile {
    float X;
    float Y;
    float Dx;
    float Dy;
    uint64_t ItemID;
    std::string ItemName;
    uint64_t Cost;
    uint32_t CurCnt;
    uint32_t MaxCnt;
    bool ShowCnt;
    TButton MinusButton;
    TButton PlusButton;
    sf::Texture PictureTexture;
    bool IsPresent;

    TItemTile() = default;

    TItemTile(const float dx, const float dy, const TItem &item, const uint32_t maxCnt, const bool showCnt) {
        X = 0;
        Y = 0;
        Dx = dx;
        Dy = dy;
        ItemID = item.ItemID;
        ItemName = item.ItemName;
        Cost = item.Cost;
        CurCnt = 0;
        MaxCnt = maxCnt;
        ShowCnt = showCnt;
        MinusButton = TButton(0, 0, 0.25 * Dx, 0.2 * Dy, "-");
        PlusButton = TButton(0, 0, 0.25 * Dx, 0.2 * Dy, "+");

        PictureTexture.loadFromImage(item.Image);

        IsPresent = false;
    }

    void UpdateButtonsPositions() {
        MinusButton.X = X + 0.1 * Dx;
        MinusButton.Y = Y + 0.7 * Dy;
        PlusButton.X = X + 0.65 * Dx;
        PlusButton.Y = Y + 0.7 * Dy;
    }

    void SetPosition(float x, float y) {
        X = x;
        Y = y;
        UpdateButtonsPositions();
    }

    void Draw(sf::RenderWindow &window) {
        sf::RectangleShape rectangle(sf::Vector2f(Dx, Dy));
        rectangle.setPosition(X, Y);
        rectangle.setFillColor(sf::Color::White);

        sf::Text nameText;
        nameText.setFont(NFont::font);
        nameText.setString(ItemName);
        nameText.setCharacterSize(18);
        nameText.setCharacterSize(std::min(1.0, Dx / nameText.getLocalBounds().width * 0.9) * 18.0);
        nameText.setFillColor(sf::Color::Black);
        sf::FloatRect nameTextRect = nameText.getLocalBounds();
        nameText.setOrigin(nameTextRect.left + nameTextRect.width / 2.0, nameTextRect.top);
        nameText.setPosition(X + 0.5 * Dx, Y + 0.54 * Dy);

        sf::Text cntText;
        cntText.setFont(NFont::font);
        cntText.setString((ShowCnt ? std::to_string(CurCnt) + " / " : "") + std::to_string(MaxCnt));
        cntText.setCharacterSize(18);
        cntText.setCharacterSize(std::min(1.0, 0.25 * Dx / cntText.getLocalBounds().width) * 18.0);
        cntText.setFillColor(sf::Color::Black);
        sf::FloatRect cntTextRect = cntText.getLocalBounds();
        cntText.setOrigin(cntTextRect.left + cntTextRect.width / 2.0, cntTextRect.top + cntTextRect.height / 2.0);
        cntText.setPosition(X + 0.5 * Dx, Y + 0.8 * Dy);

        sf::Text costText;
        costText.setFont(NFont::font);
        costText.setString(std::to_string(Cost) + " Dollars");
        costText.setCharacterSize(18);
        costText.setFillColor(sf::Color::Black);
        sf::FloatRect costTextRect = costText.getLocalBounds();
        costText.setOrigin(costTextRect.left + costTextRect.width / 2.0, costTextRect.top);
        costText.setPosition(X + 0.5 * Dx, Y + 0.5 * Dy + 35.f);

        sf::Sprite pictureSprite;
        pictureSprite.setTexture(PictureTexture);
        float pictureHeight = pictureSprite.getLocalBounds().height;
        float pictureWidth = pictureSprite.getLocalBounds().width;
        float scale = std::min(0.5f * Dy / pictureHeight, Dx / pictureWidth);
        pictureSprite.setPosition(X + 0.5 * Dx - 0.5 * pictureWidth * scale, Y + 5.f);
        pictureSprite.scale(scale, scale);

        window.draw(rectangle);
        window.draw(nameText);
        window.draw(costText);
        window.draw(cntText);
        window.draw(pictureSprite);
        MinusButton.Draw(window);
        PlusButton.Draw(window);
    }
};
