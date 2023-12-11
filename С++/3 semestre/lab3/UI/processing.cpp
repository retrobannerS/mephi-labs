#include "../src/BoxesProblem.cpp"
#include "Model/filled_box.cpp"
#include "data_cash.cpp"
#include <random>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NProcess {

    std::pair<int, std::vector<TFilledBox>> ShopBuy() {
        std::vector<TItem> items;
        for (auto pair : NDataCash::OrderItems) {
            int itemID = pair.first;
            int amount = pair.second;
            for (uint32_t ind = 0; ind < amount; ind++) {
                TItem item = NDataCash::AllItems[itemID];
                items.push_back(item);
            }
            
        }
        NDataCash::ResetOrderItems();

        ArraySequence<int> itemsIDs;
        ArraySequence<int> itemsWeights;
        ArraySequence<int> itemsVolumes;
        ArraySequence<int> itemsCosts;
        ArraySequence<int> BoxesIDs;
        ArraySequence<int> BoxesWeights;
        ArraySequence<int> BoxesVolumes;

        for (auto &item : items) {
            itemsIDs.PushBack(item.ItemID);
            itemsWeights.PushBack(item.Weight);
            itemsVolumes.PushBack(item.Volume);
            itemsCosts.PushBack(item.Cost);
        }
        for (auto pair : NDataCash::Boxes) {
            TBox box = pair.first;
            int amount = pair.second;
            if (amount > 0) {
                BoxesIDs.PushBack(box.BoxID);
                BoxesWeights.PushBack(box.MaxWeight);
                BoxesVolumes.PushBack(box.MaxVolume);
            }
        }
        std::pair<int, ArraySequence<std::pair<int, ArraySequence<int>>>> result = sem3::BoxesProblem(
            itemsIDs, itemsWeights, itemsVolumes, itemsCosts, BoxesIDs, BoxesWeights, BoxesVolumes, BoxesWeights);

        std::vector<TFilledBox> bestFilledBoxes;
        for (int i = 0; i < result.second.GetSize(); i++) {
            int boxID = result.second[i].first;
            ArraySequence<int> itemIDs = result.second[i].second;

            std::vector<TItem> items;
            for (int j = 0; j < itemIDs.GetSize(); j++) {
                TItem item = NDataCash::AllItems[itemIDs[j]];
                items.push_back(item);
            }
            TBox box = NDataCash::AllBoxes[boxID];
            bestFilledBoxes.push_back(TFilledBox(box, items));
        }

        return {result.first, bestFilledBoxes};
    }

} // namespace NProcess