#pragma once
#include "ArraySequence.hpp"
#include "Graphs/BaseGraph/BaseGraph.hpp"
#include "ListSequence.hpp"
#include <ostream>
#include <utility>

using namespace std;
using namespace lab2;

namespace sem3 {
    class DiGraph : public BaseGraph {
    private:
        using BaseGraph::graph;

    public:
        DiGraph() noexcept;
        DiGraph(const ArraySequence<ListSequence<int>> &adjacencyList) noexcept;
        DiGraph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix) noexcept;
        DiGraph(const ArraySequence<pair<int, int>> &edges) noexcept;

        DiGraph(const DiGraph &other) noexcept;
        DiGraph(DiGraph &&other) noexcept;

        DiGraph &operator=(const DiGraph &other) noexcept;
        DiGraph &operator=(DiGraph &&other) noexcept;

        ~DiGraph() noexcept override = default;

        int getEdgeCount() const noexcept override;

        ArraySequence<pair<int, int>> getEdges() const noexcept override;

        void addEdge(int from, int to) override;

        void removeEdge(int from, int to) override;

        int getInDegree(int vertex) const;
        int getOutDegree(int vertex) const;

        ArraySequence<int> getInNeighbors(int vertex) const;
        ArraySequence<int> getOutNeighbors(int vertex) const;

        DiGraph transpose() const noexcept;
    };

} // namespace sem3