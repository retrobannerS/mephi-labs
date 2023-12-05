#pragma once
#include "Graphs/BaseGraph/BaseGraph.hpp"

namespace sem3 {
    class Graph : public BaseGraph {
    private:
        using BaseGraph::graph;

    public:
        Graph() noexcept;
        Graph(const ArraySequence<ListSequence<int>> &adjacencyList);
        Graph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix);
        Graph(const ArraySequence<pair<int, int>> &edges) noexcept;

        Graph(const Graph &other) noexcept;
        Graph(Graph &&other) noexcept;

        Graph &operator=(const Graph &other) noexcept;
        Graph &operator=(Graph &&other) noexcept;

        ~Graph() noexcept override = default;

        int getEdgeCount() const noexcept override;
        ArraySequence<pair<int, int>> getEdges() const noexcept override;

        void addEdge(int from, int to) override;
        void removeEdge(int from, int to) override;

        int getDegree(int vertex) const;
        ArraySequence<int> getNeighbors(int vertex) const;
    };
} // namespace sem3