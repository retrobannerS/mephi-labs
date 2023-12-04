#pragma once
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include <ostream>
#include <utility>

using namespace std;
using namespace lab2;

namespace sem3 {
    //base virtual class graph
    class Graph {
    protected:
        ArraySequence<ListSequence<int>> graph;
        void makeTombstone(int vertex) noexcept;
    public:
        virtual ~Graph() noexcept = default;

        int getVertexCount() const noexcept;
        virtual int getEdgeCount() const noexcept = 0;

        ArraySequence<int> getVertexes() const noexcept;
        virtual ArraySequence<pair<int, int>> getEdges() const noexcept = 0;
        ArraySequence<int> getTombstones() const noexcept;

        virtual void addVertex() noexcept = 0;
        virtual void addVertex(int vertex) = 0;
        virtual void addVertex(ListSequence<int> neighbors) noexcept = 0;
        virtual void addVertex(int vertex, ListSequence<int> neighbors) = 0;
        virtual void addEdge(int from, int to) = 0;

        void removeVertex(int vertex);
        virtual void removeEdge(int from, int to) = 0;

        bool hasVertex(int vertex) const noexcept;
        bool hasEdge(int from, int to) const noexcept;
        bool isTombstone(int vertex) const noexcept;

        bool isEmpty() const noexcept;
        bool isAcyclic() const noexcept;
        bool isTree() const noexcept;

        bool operator==(const Graph& other) const noexcept;
        bool operator!=(const Graph& other) const noexcept;

        friend ostream& operator<<(ostream& out, const Graph& graph);
    };


} // namespace sem3