#pragma once
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include <ostream>
#include <utility>

using namespace std;
using namespace lab2;

namespace sem3 {
    class BaseGraph {
    protected:
        ArraySequence<ListSequence<int>> graph;
        void makeTombstone(int vertex) noexcept;

    public:
        virtual ~BaseGraph() noexcept = default;

        int getVertexCount() const noexcept;
        virtual int getEdgeCount() const noexcept = 0;

        ArraySequence<int> getVertexes() const noexcept;
        virtual ArraySequence<pair<int, int>> getEdges() const noexcept = 0;
        ArraySequence<int> getTombstones() const noexcept;

        void addVertex() noexcept;
        void addVertex(int vertex);
        void addVertex(ListSequence<int> neighbors) noexcept;
        void addVertex(int vertex, ListSequence<int> neighbors);
        virtual void addEdge(int from, int to) = 0;

        void removeVertex(int vertex);
        virtual void removeEdge(int from, int to) = 0;

        bool hasVertex(int vertex) const noexcept;
        bool hasEdge(int from, int to) const noexcept;
        bool isTombstone(int vertex) const noexcept;

        ArraySequence<int> achievableFrom(int vertex);

        bool isEmpty() const noexcept;

        bool operator==(const BaseGraph &other) const noexcept;
        bool operator!=(const BaseGraph &other) const noexcept;

        friend ostream &operator<<(ostream &out, const BaseGraph &graph);
    };

} // namespace sem3