#pragma once
#include "ArraySequence.hpp"
#include "Graph.hpp"
#include "ListSequence.hpp"
#include <ostream>
#include <utility>

using namespace std;
using namespace lab2;

namespace sem3 {
    class DirectedGraph : public Graph {
    private:
        using Graph::graph;

    public:
        DirectedGraph() noexcept;
        DirectedGraph(const ArraySequence<ListSequence<int>> &adjacencyList) noexcept;
        DirectedGraph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix) noexcept;
        DirectedGraph(const ArraySequence<pair<int, int>> &edges) noexcept;

        DirectedGraph(const DirectedGraph &other) noexcept;
        DirectedGraph(DirectedGraph &&other) noexcept;

        DirectedGraph &operator=(const DirectedGraph &other) noexcept;
        DirectedGraph &operator=(DirectedGraph &&other) noexcept;

        ~DirectedGraph() noexcept override = default;

        int getEdgeCount() const noexcept override;

        ArraySequence<pair<int, int>> getEdges() const noexcept override;

        void addVertex() noexcept override;
        void addVertex(int vertex) override;
        void addVertex(ListSequence<int> neighbors) noexcept override;
        void addVertex(int vertex, ListSequence<int> neighbors) override;
        void addEdge(int from, int to) override;

        void removeEdge(int from, int to) override;

        bool isStronglyConnected() const noexcept;

        int getInDegree(int vertex) const;
        int getOutDegree(int vertex) const;

        ArraySequence<int> getInNeighbors(int vertex) const;
        ArraySequence<int> getOutNeighbors(int vertex) const;
    };

} // namespace sem3