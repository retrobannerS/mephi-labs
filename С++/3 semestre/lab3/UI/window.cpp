#include "GraphicControls/box_tile.cpp"
#include "GraphicControls/button.cpp"
#include "GraphicControls/filled_box_tile.cpp"
#include "GraphicControls/font.cpp"
#include "GraphicControls/item_tile.cpp"
#include "GraphicControls/text_field.cpp"
#include "Model/filled_box.cpp"
#include "helper_functions.cpp"
#include "processing.cpp"

void AddTitle(sf::RenderWindow &window, const std::string &title, const float px = 50.f, const float py = 20.f,
              const int charSize = 24) {
    sf::Text text;
    text.setFont(NFont::font);
    text.setString(title);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(px, py);
    window.draw(text);
}

void ShowOrder(sf::RenderWindow &window, const std::vector<TFilledBox> &filledBoxes, std::string title = "") {
    if (title.empty()) {
        title = "You finished your purchase successfully. Thank you for using our shop. \nYour order will come to you in "
                "the following form:";
    }
    std::vector<TFilledBoxTile> filledTBoxTiles;

    for (size_t i = 0; i < filledBoxes.size(); i++) {
        TBox curBox = NDataCash::AllBoxes[filledBoxes[i].BoxID];
        filledTBoxTiles.push_back(TFilledBoxTile(250.f, 550.f, curBox.BoxID, curBox.Image, filledBoxes[i].ItemIDs));
    }

    uint64_t orderTotalCost = 0;
    for (const TFilledBox &filledBox : filledBoxes) {
        orderTotalCost += NDataCash::AllBoxes[filledBox.BoxID].Cost;
        for (const uint64_t &itemID : filledBox.ItemIDs) {
            orderTotalCost += NDataCash::AllItems[itemID].Cost;
        }
    }

    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Go Back");
    TButton leftButton(50.f, 100.f, 25.f, 25.f, "<");
    TButton rightButton(1200.f, 100.f, 25.f, 25.f, ">");

    size_t pageIndex = 0;
    const size_t columns = 3;

    bool quit = false;
    while (window.isOpen() && !quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (goBackButton.IsIn(px, py)) {
                    return;
                } else if (leftButton.IsIn(px, py)) {
                    if (pageIndex > 0) {
                        pageIndex--;
                    }
                } else if (rightButton.IsIn(px, py)) {
                    if ((pageIndex + 1) * columns < filledTBoxTiles.size()) {
                        pageIndex++;
                    }
                }
            }
        }

        window.clear();
        AddTitle(window, title);
        goBackButton.Draw(window);
        if (pageIndex != 0) {
            leftButton.Draw(window);
        }
        size_t curIndex = 0;
        for (size_t i = 0; i < filledTBoxTiles.size(); i++) {
            filledTBoxTiles[i].IsPresent = false;
            if (curIndex / columns == pageIndex) {
                size_t innerIndex = curIndex % columns;
                filledTBoxTiles[i].SetPosition(250.f + innerIndex * 265.f, 110.f);
                filledTBoxTiles[i].IsPresent = true;
            }
            curIndex++;
        }
        if ((pageIndex + 1) * columns < curIndex) {
            rightButton.Draw(window);
        }
        for (TFilledBoxTile &filledTBoxTile : filledTBoxTiles) {
            if (filledTBoxTile.IsPresent) {
                filledTBoxTile.Draw(window);
            }
        }

        sf::Text totalCostText;
        totalCostText.setFont(NFont::font);
        totalCostText.setString("Order Cost:\n" + std::to_string(orderTotalCost) + " Dollars");
        totalCostText.setCharacterSize(24);
        totalCostText.setFillColor(sf::Color::White);
        totalCostText.setPosition(50.f, 100.f);

        window.draw(totalCostText);

        window.display();
    }
}

void PrintBoxes(sf::RenderWindow &window, const std::vector<TFilledBox> &filledBoxes) {
    if (filledBoxes.size() == 0) {
        TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Go Back");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    float px = event.mouseButton.x;
                    float py = event.mouseButton.y;
                    if (goBackButton.IsIn(px, py)) {
                        return;
                    }
                }
            }

            window.clear();
            AddTitle(
                window,
                "Your order can't be packed because one of your items doesn't fit in any of our boxes. We are sorry.");
            goBackButton.Draw(window);
            window.display();
        }
    } else {
        ShowOrder(window, filledBoxes);
    }
}

void DidntBuyAnything(sf::RenderWindow &window) {
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Go Back");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;
                if (goBackButton.IsIn(px, py)) {
                    return;
                }
            }
        }
        window.clear();
        AddTitle(window, "You didn't buy anything. We hope you'll like something next time!");
        goBackButton.Draw(window);
        window.display();
    }
}

void UserMode(sf::RenderWindow &window) {
    const std::vector<TBox> &availableBoxes = NDataCash::AvailableBoxes;
    const std::vector<std::pair<TItem, uint32_t>> &items = NDataCash::Items;
    NDataCash::LoadOrderItems();

    std::vector<TItemTile> itemTiles;
    for (size_t i = 0; i < items.size(); i++) {
        itemTiles.push_back(TItemTile(250.f, 250.f, items[i].first, items[i].second, true));
    }
    TButton finishButton(1100.f, 600.f, 100.f, 50.f, "Finish Order");
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Go Back");
    TButton leftButton(50.f, 100.f, 25.f, 25.f, "<");
    TButton rightButton(1200.f, 100.f, 25.f, 25.f, ">");

    TTextField searchField(550.f, 50.f, 300.f, 50.f, "Search");

    size_t pageIndex = 0;
    const size_t rows = 1, columns = 4;
    const size_t pageSize = rows * columns;

    bool quit = false;
    while (window.isOpen() && !quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                searchField.PopChar();
                pageIndex = 0;
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    searchField.AddChar(c);
                    pageIndex = 0;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (goBackButton.IsIn(px, py)) {
                    return;
                } else if (finishButton.IsIn(px, py)) {
                    quit = true;
                    break;
                } else if (leftButton.IsIn(px, py)) {
                    if (pageIndex > 0) {
                        pageIndex--;
                    }
                } else if (rightButton.IsIn(px, py)) {
                    if ((pageIndex + 1) * pageSize < itemTiles.size()) {
                        pageIndex++;
                    }
                } else {
                    for (size_t i = 0; i < items.size(); i++) {
                        if (itemTiles[i].IsPresent) {
                            if (itemTiles[i].MinusButton.IsIn(px, py)) {
                                if (itemTiles[i].CurCnt > 0) {
                                    itemTiles[i].CurCnt--;
                                    //NDataCash::UpdateItem(items[i].first.ItemID, -1);
                                    NDataCash::OrderItems[itemTiles[i].ItemID].second--;
                                }
                            } else if (itemTiles[i].PlusButton.IsIn(px, py)) {
                                if (itemTiles[i].CurCnt < itemTiles[i].MaxCnt) {
                                    itemTiles[i].CurCnt++;
                                    //NDataCash::UpdateItem(items[i].first.ItemID, 1);
                                    NDataCash::OrderItems[itemTiles[i].ItemID].second++;
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        AddTitle(window, "Select Items you want to buy:");
        finishButton.Draw(window);
        searchField.Draw(window);
        goBackButton.Draw(window);
        if (pageIndex != 0) {
            leftButton.Draw(window);
        }
        size_t curIndex = 0;
        for (size_t i = 0; i < itemTiles.size(); i++) {
            itemTiles[i].IsPresent = false;
            if (itemTiles[i].MaxCnt == 0 || !StartsWith(itemTiles[i].ItemName, searchField.Label)) {
                continue;
            }
            if (curIndex / pageSize == pageIndex) {
                size_t innerIndex = curIndex % pageSize;
                itemTiles[i].SetPosition(150.f + (innerIndex % columns) * 265.f,
                                         250.f + (innerIndex / columns) * 265.f);
                itemTiles[i].IsPresent = true;
            }
            curIndex++;
        }
        if ((pageIndex + 1) * pageSize < curIndex) {
            rightButton.Draw(window);
        }
        for (TItemTile &itemTile : itemTiles) {
            if (itemTile.IsPresent) {
                itemTile.Draw(window);
            }
        }
        window.display();
    }

    bool flag = false;
    for(const auto pair : NDataCash::OrderItems) {
        int amount = pair.second;
        if (amount > 0) {flag = true; break;}
    }
    if (!flag) {
        DidntBuyAnything(window);
    } else {
        std::pair<int, std::vector<TFilledBox>> result = NProcess::ShopBuy();
        int totalCost = result.first;
        std::vector<TFilledBox> filledBoxes = result.second;

        PrintBoxes(window, filledBoxes);
    }
}


void AdminAddDeleteItem(sf::RenderWindow &window) {
    const std::vector<std::pair<TItem, uint32_t>> &items = NDataCash::Items;
    std::vector<std::pair<uint64_t, int32_t>> newItems(items.size());
    for (size_t i = 0; i < items.size(); i++) {
        newItems[i] = {items[i].first.ItemID, 0};
    }

    std::vector<TItemTile> itemTiles;
    for (size_t i = 0; i < items.size(); i++) {
        itemTiles.push_back(TItemTile(250.f, 250.f, items[i].first, items[i].second, false));
    }
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Finish And Go Back");
    TButton leftButton(50.f, 100.f, 25.f, 25.f, "<");
    TButton rightButton(1200.f, 100.f, 25.f, 25.f, ">");

    TTextField searchField(550.f, 50.f, 300.f, 50.f, "Search");

    size_t pageIndex = 0;
    const size_t rows = 1, columns = 4;
    const size_t pageSize = rows * columns;

    bool quit = false;
    while (window.isOpen() && !quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                searchField.PopChar();
                pageIndex = 0;
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    searchField.AddChar(c);
                    pageIndex = 0;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (goBackButton.IsIn(px, py)) {
                    quit = true;
                    break;
                } else if (leftButton.IsIn(px, py)) {
                    if (pageIndex > 0) {
                        pageIndex--;
                    }
                } else if (rightButton.IsIn(px, py)) {
                    if ((pageIndex + 1) * pageSize < itemTiles.size()) {
                        pageIndex++;
                    }
                } else {
                    for (size_t i = 0; i < items.size(); i++) {
                        if (itemTiles[i].IsPresent) {
                            if (itemTiles[i].MinusButton.IsIn(px, py)) {
                                if (itemTiles[i].MaxCnt > 0) {
                                    itemTiles[i].MaxCnt--;
                                    newItems[i].second--;
                                }
                            } else if (itemTiles[i].PlusButton.IsIn(px, py)) {
                                itemTiles[i].MaxCnt++;
                                newItems[i].second++;
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        AddTitle(window, "Change items amounts:");
        goBackButton.Draw(window);
        searchField.Draw(window);
        if (pageIndex != 0) {
            leftButton.Draw(window);
        }
        size_t curIndex = 0;
        for (size_t i = 0; i < itemTiles.size(); i++) {
            itemTiles[i].IsPresent = false;
            if (!StartsWith(itemTiles[i].ItemName, searchField.Label)) {
                continue;
            }
            if (curIndex / pageSize == pageIndex) {
                size_t innerIndex = curIndex % pageSize;
                itemTiles[i].SetPosition(150.f + (innerIndex % columns) * 265.f,
                                         250.f + (innerIndex / columns) * 265.f);
                itemTiles[i].IsPresent = true;
            }
            curIndex++;
        }
        if ((pageIndex + 1) * pageSize < curIndex) {
            rightButton.Draw(window);
        }
        for (TItemTile &itemTile : itemTiles) {
            if (itemTile.IsPresent) {
                itemTile.Draw(window);
            }
        }
        window.display();
    }

    for (const auto [itemID, amount] : newItems) {
        NDataCash::UpdateItem(itemID, amount);
    }
}

void AdminAddDeleteBox(sf::RenderWindow &window) {
    const std::vector<std::pair<TBox, uint32_t>> &boxes = NDataCash::Boxes;
    std::vector<std::pair<uint64_t, int32_t>> newBoxes(boxes.size());
    for (size_t i = 0; i < boxes.size(); i++) {
        newBoxes[i] = {boxes[i].first.BoxID, 0};
    }

    std::vector<TBoxTile> boxTiles;
    for (size_t i = 0; i < boxes.size(); i++) {
        boxTiles.push_back(TBoxTile(250.f, 250.f, boxes[i].first.BoxID, boxes[i].first.BoxName, boxes[i].second,
                                    boxes[i].first.Image));
    }
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Finish And Go Back");
    TButton leftButton(25.f, 75.f, 25.f, 25.f, "<");
    TButton rightButton(1200.f, 75.f, 25.f, 25.f, ">");

    TTextField searchField(550.f, 50.f, 300.f, 50.f, "Search");

    size_t pageIndex = 0;
    const size_t rows = 1, columns = 4;
    const size_t pageSize = rows * columns;

    bool quit = false;
    while (window.isOpen() && !quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                searchField.PopChar();
                pageIndex = 0;
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    searchField.AddChar(c);
                    pageIndex = 0;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (goBackButton.IsIn(px, py)) {
                    quit = true;
                    break;
                } else if (leftButton.IsIn(px, py)) {
                    if (pageIndex > 0) {
                        pageIndex--;
                    }
                } else if (rightButton.IsIn(px, py)) {
                    if ((pageIndex + 1) * pageSize < boxTiles.size()) {
                        pageIndex++;
                    }
                } else {
                    for (size_t i = 0; i < boxes.size(); i++) {
                        if (boxTiles[i].IsPresent) {
                            if (boxTiles[i].AvailableButton.IsIn(px, py)) {
                                if (boxTiles[i].Available) {
                                    boxTiles[i].Available = false;
                                    newBoxes[i].second--;
                                } else {
                                    boxTiles[i].Available = true;
                                    newBoxes[i].second++;
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        AddTitle(window, "Change Boxes Availability:");
        goBackButton.Draw(window);
        searchField.Draw(window);
        if (pageIndex != 0) {
            leftButton.Draw(window);
        }
        size_t curIndex = 0;
        for (size_t i = 0; i < boxTiles.size(); i++) {
            boxTiles[i].IsPresent = false;
            if (!StartsWith(boxTiles[i].BoxName, searchField.Label)) {
                continue;
            }
            if (curIndex / pageSize == pageIndex) {
                size_t innerIndex = curIndex % pageSize;
                boxTiles[i].SetPosition(150.f + (innerIndex % columns) * 265.f, 250.f + (innerIndex / columns) * 265.f);
                boxTiles[i].IsPresent = true;
            }
            curIndex++;
        }
        if ((pageIndex + 1) * pageSize < curIndex) {
            rightButton.Draw(window);
        }
        for (TBoxTile &boxTile : boxTiles) {
            if (boxTile.IsPresent) {
                boxTile.Draw(window);
            }
        }
        window.display();
    }

    for (auto [boxID, amount] : newBoxes) {
        NDataCash::UpdateBox(boxID, amount);
    }
}

void AdminMode(sf::RenderWindow &window) {
    TButton addItemButton(350.f, 350.f, 200.f, 100.f, "Add/Delete Items");
    TButton addBoxButton(850.f, 350.f, 200.f, 100.f, "Add/Delete Boxes");
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Go Back");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (addItemButton.IsIn(px, py)) {
                    AdminAddDeleteItem(window);
                } else if (addBoxButton.IsIn(px, py)) {
                    AdminAddDeleteBox(window);
                } else if (goBackButton.IsIn(px, py)) {
                    return;
                }
            }
        }

        window.clear();
        AddTitle(window, "Choose action:");
        addItemButton.Draw(window);
        addBoxButton.Draw(window);
        goBackButton.Draw(window);
        window.display();
    }
}

void ChooseMode(sf::RenderWindow &window) {
    TButton adminButton(200.f, 350.f, 200.f, 100.f, "Admin");
    TButton userButton(600.f, 350.f, 200.f, 100.f, "Buy");
    TButton historyButton(1000.f, 350.f, 200.f, 100.f, "See History");
    TButton goBackButton(50.f, 600.f, 100.f, 50.f, "Close The App");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                float px = event.mouseButton.x;
                float py = event.mouseButton.y;

                if (adminButton.IsIn(px, py)) {
                    AdminMode(window);
                } else if (userButton.IsIn(px, py)) {
                    UserMode(window);
                } else if (historyButton.IsIn(px, py)) {
                    // ShowHistory(window);
                } else if (goBackButton.IsIn(px, py)) {
                    return;
                }
            }
        }
        window.clear();
        AddTitle(window, "Choose mode:");
        adminButton.Draw(window);
        userButton.Draw(window);
        historyButton.Draw(window);
        goBackButton.Draw(window);
        window.display();
    }
}