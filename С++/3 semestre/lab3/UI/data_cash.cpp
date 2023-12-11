#pragma once

#include <map>
#include <utility>
#include <vector>

#include "Model/box.cpp"
#include "Model/item.cpp"

#include "helper_functions.cpp"

namespace NDataCash {
    std::vector<TItem> AllItems = {{0, "TV", 20000, 1000, 2, "../assets/images/tv.jpeg"},
                                   {1, "Balloon", 100, 100, 500, "../assets/images/balloon.jpg"},
                                   {2, "Camera", 500, 50, 5, "../assets/images/camera.jpg"},
                                   {3, "Fork", 30, 2, 1000, "../assets/images/fork.jpg"},
                                   {4, "Jeans", 300, 10, 14, "../assets/images/jeans.jpg"},
                                   {5, "Pasta", 300, 100, 750, "../assets/images/pasta.jpg"},
                                   {6, "Phone", 200, 50, 3, "../assets/images/phone.png"},
                                   {7, "Pizza", 1000, 100, 1500, "../assets/images/pizza.jpg"},
                                   {8, "Plate", 100, 50, 650, "../assets/images/plate.jpg"},
                                   {9, "Stake", 500, 100, 4, "../assets/images/stake.jpg"},
                                   {10, "T-Shirt", 200, 10, 20, "../assets/images/tshirt.png"},
                                   {11, "Sushi", 750, 450, 2000, "../assets/images/sushi.jpg"}};
    std::vector<TBox> AllBoxes = {{0, "Small box", 1000, 100, 2, "../assets/images/small_box.jpg"},
                                  {1, "Medium box", 5000, 500, 10, "../assets/images/medium_box.jpg"},
                                  {2, "Big box", 10000, 1000, 30, "../assets/images/big_box.jpeg"},
                                  {3, "Enormous box", 50000, 5000, 50, "../assets/images/enormous_box.jpg"},
                                  {4, "Extra large box", 100000, 10000, 100, "../assets/images/extra_large_box.jpeg"}};

    std::vector<std::pair<TItem, uint32_t>> Items = {
        {AllItems[0], 0}, {AllItems[1], 2}, {AllItems[2], 3}, {AllItems[3], 0}, {AllItems[4], 0},  {AllItems[5], 2},
        {AllItems[6], 1}, {AllItems[7], 0}, {AllItems[8], 0}, {AllItems[9], 8}, {AllItems[10], 0}, {AllItems[11], 0}};
    std::vector<std::pair<TBox, uint32_t>> Boxes = {
        {AllBoxes[0], 0}, {AllBoxes[1], 1}, {AllBoxes[2], 0}, {AllBoxes[3], 1}, {AllBoxes[4], 0}};

    std::vector<TBox> AvailableBoxes;

    std::map<uint64_t, TItem> IdToItem;
    std::map<uint64_t, TBox> IdToBox;

    std::vector<std::pair<uint64_t, uint32_t>> OrderItems;

    void LoadOrderItems() {
        for (const auto &item : AllItems) {
            OrderItems.push_back({item.ItemID, 0});
        }
    }

    void ResetOrderItems() {
        for (auto &item : OrderItems) {
            item.second = 0;
        }
    }

    void AddNewItem(const TItem &item) {
        AllItems.push_back(item);
        Items.emplace_back(item, 0);
        IdToItem[item.ItemID] = item;
    }

    void AddNewBox(const TBox &box) {
        AllBoxes.push_back(box);
        Boxes.emplace_back(box, 0);
        IdToBox[box.BoxID] = box;
    }

    void UpdateItem(const uint64_t itemID, const int32_t amount) {
        if (amount == 0) {
            return;
        }
        for (auto &itemAndAmount : Items) {
            if (itemAndAmount.first.ItemID == itemID) {
                itemAndAmount.second += amount;
                break;
            }
        }
    }

    void UpdateBox(const uint64_t boxID, const int32_t amount) {
        if (amount == 0) {
            return;
        }
        for (auto &boxAndAvailability : Boxes) {
            if (boxAndAvailability.first.BoxID == boxID) {
                boxAndAvailability.second += amount;
                break;
            }
        }
        for (size_t i = 0; i < AvailableBoxes.size(); i++) {
            if (AvailableBoxes[i].BoxID == boxID) {
                AvailableBoxes.erase(AvailableBoxes.begin() + i);
                break;
            }
        }
    }

    bool CheckIfItemExists(const std::string &itemName) {
        for (const TItem &item : AllItems) {
            if (item.ItemName == itemName) {
                return true;
            }
        }
        return false;
    }

    bool CheckIfBoxExists(const std::string &boxName) {
        for (const TBox &box : AllBoxes) {
            if (box.BoxName == boxName) {
                return true;
            }
        }
        return false;
    }
} // namespace NDataCash
