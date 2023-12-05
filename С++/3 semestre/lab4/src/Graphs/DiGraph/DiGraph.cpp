#include "DiGraph.hpp"
#include <string>

using namespace std;
using namespace lab2;

namespace sem3 {
    DiGraph::DiGraph() noexcept { graph = ArraySequence<ListSequence<int>>(); }

    DiGraph::DiGraph(const ArraySequence<ListSequence<int>> &adjacencyList) noexcept { graph = adjacencyList; }

    DiGraph::DiGraph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix) noexcept {
        for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
            graph.PushBack(ListSequence<int>());
            for (int j = 0; j < adjacencyMatrix.Get(i).GetSize(); ++j) {
                if (adjacencyMatrix.Get(i)[j] != 0) {
                    graph[i].PushBack(j);
                }
            }
        }
    }

    DiGraph::DiGraph(const ArraySequence<pair<int, int>> &edges) noexcept {
        for (int i = 0; i < edges.GetSize(); ++i) {
            addVertex(edges.Get(i).first);
            addVertex(edges.Get(i).second);
            addEdge(edges.Get(i).first, edges.Get(i).second);
        }
    }

    DiGraph::DiGraph(const DiGraph &other) noexcept { graph = other.graph; }

    DiGraph::DiGraph(DiGraph &&other) noexcept {
        graph = other.graph;
        other.graph = ArraySequence<ListSequence<int>>();
    }

    DiGraph &DiGraph::operator=(const DiGraph &other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = other.graph;
        return *this;
    }

    DiGraph &DiGraph::operator=(DiGraph &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = other.graph;
        other.graph = ArraySequence<ListSequence<int>>();
        return *this;
    }

    int DiGraph::getEdgeCount() const noexcept {
        int result = 0;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (!isTombstone(i))
                result += graph.Get(i).GetSize();
        }
        return result;
    }

    ArraySequence<pair<int, int>> DiGraph::getEdges() const noexcept {
        ArraySequence<pair<int, int>> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (!isTombstone(i))
                for (int j = 0; j < graph.Get(i).GetSize(); ++j) {
                    result.PushBack(make_pair(i, graph.Get(i).Get(j)));
                }
        }
        return result;
    }

    void DiGraph::addEdge(int from, int to) {
        if (from < 0 or to < 0 or from >= graph.GetSize() or to >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        } else if (isTombstone(from) or isTombstone(to)) {
            throw invalid_argument("Vertex is tombstone");
        } else if (hasEdge(from, to)) {
            return;
        } else {
            graph[from].PushBack(to);
        }
    }

    void DiGraph::removeEdge(int from, int to) {
        if (from < 0 or to < 0 or from >= graph.GetSize() or to >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        } else if (isTombstone(from) or isTombstone(to)) {
            throw invalid_argument("Vertex is tombstone");
        } else if (!hasEdge(from, to)) {
            return;
        } else {
            for (int i = 0; i < graph[from].GetSize(); ++i) {
                if (graph[from].Get(i) == to) {
                    graph[from].PopFrom(i);
                    break;
                }
            }
        }
    }

    int DiGraph::getInDegree(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        int result = 0;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (hasEdge(i, vertex)) {
                ++result;
            }
        }
        return result;
    }

    int DiGraph::getOutDegree(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        return graph.Get(vertex).GetSize();
    }

    ArraySequence<int> DiGraph::getInNeighbors(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        ArraySequence<int> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (hasEdge(i, vertex)) {
                result.PushBack(i);
            }
        }
        return result;
    }

    ArraySequence<int> DiGraph::getOutNeighbors(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        ArraySequence<int> result;
        for (int i = 0; i < graph.Get(vertex).GetSize(); ++i) {
            result.PushBack(graph.Get(vertex).Get(i));
        }
        return result;
    }

    DiGraph DiGraph::transpose() const noexcept { 
        ArraySequence<ListSequence<int>> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            result.PushBack(ListSequence<int>());
            for (int j = 0; j < graph.GetSize(); ++j) {
                if (hasEdge(j, i)) {
                    result[i].PushBack(j);
                }
            }
        }
        return DiGraph(result);
    }
} // namespace sem3