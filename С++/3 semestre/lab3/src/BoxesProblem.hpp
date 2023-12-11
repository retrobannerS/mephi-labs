#pragma once
#include <utility>
#include "ArraySequence.hpp"

namespace sem3 {
    std::pair<int, lab2::ArraySequence<std::pair<int, lab2::ArraySequence<int>>>>
    BoxesProblem(lab2::ArraySequence<int> items, lab2::ArraySequence<int> iWeights, lab2::ArraySequence<int> iVolumes,
                 lab2::ArraySequence<int> iCosts, lab2::ArraySequence<int> Boxes, lab2::ArraySequence<int> bWeight,
                 lab2::ArraySequence<int> bVolume, lab2::ArraySequence<int> bCost);
}
