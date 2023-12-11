#include "ArraySequence.hpp"
#include <climits>
#include <cmath>
#include <utility>

using namespace lab2;

namespace sem3 {
    std::pair<int, ArraySequence<std::pair<int, ArraySequence<int>>>>
    BoxesProblem(ArraySequence<int> items, ArraySequence<int> iWeights, ArraySequence<int> iVolumes,
                 ArraySequence<int> iCosts, ArraySequence<int> Boxes, ArraySequence<int> bWeight,
                 ArraySequence<int> bVolume, ArraySequence<int> bCost) {
        int n = pow(2, items.GetSize());
        ArraySequence<int> totalWeight(n);
        ArraySequence<int> totalVolume(n);
        ArraySequence<int> minCost(n, INT_MAX);
        ArraySequence<std::pair<int, int>> lastBox(n);
        minCost[0] = 0;

        for (int mask; mask < n; mask++) {
            for (size_t bit = 0; bit < items.GetSize(); bit++) {
                if ((mask >> bit) & 1) {
                    totalWeight[mask] += iWeights[bit];
                    totalVolume[mask] += iVolumes[bit];
                }
            }
            for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
                for (int BoxIndex = 0; BoxIndex < Boxes.GetSize(); BoxIndex++) {
                    int MaxWeight = bWeight.Get(BoxIndex);
                    int MaxVolume = bVolume.Get(BoxIndex);
                    int BoxCost = bCost.Get(BoxIndex);
                    if (totalWeight[subMask] <= MaxWeight && totalVolume[subMask] <= MaxVolume &&
                        minCost[mask ^ subMask] != INT_MAX) {
                        int newCost = minCost[mask ^ subMask] + BoxCost;
                        if (minCost[mask] > newCost) {
                            minCost[mask] = newCost;
                            lastBox[mask] = {subMask, Boxes[BoxIndex]};
                        }
                    }
                }
            }
        }

        ArraySequence<std::pair<int, ArraySequence<int>>> result;
        int currentMask = n - 1;
        int cost = minCost[currentMask];

        if (cost == INT_MAX) { // какой-то товар не влез ни в одну коробку
            return {cost, result};
        }

        while (currentMask != 0) {
            const int boxMask = lastBox[currentMask].first;
            const int currentBoxID = lastBox[currentMask].second;
            ArraySequence<int> currentBoxItemIDs;
            for (size_t bit = 0; bit < items.GetSize(); bit++) {
                if ((boxMask >> bit) & 1) {
                    currentBoxItemIDs.PushBack(items[bit]);
                }
            }
            result.PushBack({currentBoxID, currentBoxItemIDs});
            currentMask ^= boxMask;
        }
        return {cost, result};
    }
} // namespace sem3