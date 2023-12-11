#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <ostream>
#include <string>

struct TBox {
    uint64_t BoxID;
    std::string BoxName;
    uint64_t MaxWeight;
    uint64_t MaxVolume;
    uint64_t Cost;
    sf::Image Image;

    TBox(const uint64_t &boxID, const std::string &boxName, const uint64_t maxWeight, const uint64_t maxVolume,
         const uint64_t cost, const std::string &image = "")
        : BoxID(boxID), BoxName(boxName), MaxWeight(maxWeight), MaxVolume(maxVolume), Cost(cost) {
        Image.loadFromFile(image);
    }

    TBox() = default;

    bool operator==(const TBox &other) const { return BoxID == other.BoxID; }
};

std::ostream &operator<<(std::ostream &out, TBox box) {
    out << box.BoxName;
    return out;
}
