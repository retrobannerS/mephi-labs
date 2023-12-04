#include "DirectedGraph.hpp"

using namespace std;
using namespace lab2;

namespace sem3 {
    DirectedGraph::DirectedGraph() noexcept { graph = ArraySequence<ListSequence<int>>(); }

    DirectedGraph::DirectedGraph(const ArraySequence<ListSequence<int>> &adjacencyList) noexcept {
        graph = adjacencyList;
    }

    DirectedGraph::DirectedGraph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix) noexcept {
        for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
            graph.PushBack(ListSequence<int>());
            for (int j = 0; j < adjacencyMatrix.Get(i).GetSize(); ++j) {
                if (adjacencyMatrix.Get(i)[j] != 0) {
                    graph[i].PushBack(j);
                }
            }
        }
    }

    DirectedGraph::DirectedGraph(const ArraySequence<pair<int, int>> &edges) noexcept {
        int maxVertex = 0;
        for (int i = 0; i < edges.GetSize(); ++i) {
            if (edges.Get(i).first > maxVertex) {
                maxVertex = edges.Get(i).first;
            }
            if (edges.Get(i).second > maxVertex) {
                maxVertex = edges.Get(i).second;
            }
        }
        for (int i = 0; i <= maxVertex; ++i) {
            graph.PushBack(ListSequence<int>());
        }
        for (int i = 0; i < edges.GetSize(); ++i) {
            addEdge(edges.Get(i).first, edges.Get(i).second);
        }
    }

    DirectedGraph::DirectedGraph(const DirectedGraph &other) noexcept { graph = other.graph; }

    DirectedGraph::DirectedGraph(DirectedGraph &&other) noexcept { graph = std::move(other.graph); }

    DirectedGraph &DirectedGraph::operator=(const DirectedGraph &other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = other.graph;
        return *this;
    }

    DirectedGraph &DirectedGraph::operator=(DirectedGraph &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = std::move(other.graph);
        return *this;
    }

    int DirectedGraph::getEdgeCount() const noexcept {
        int result = 0;
        for (int i = 0; i < graph.GetSize(); ++i) {
            result += graph.Get(i).GetSize();
        }
        return result;
    }

    ArraySequence<pair<int, int>> DirectedGraph::getEdges() const noexcept {
        ArraySequence<pair<int, int>> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            for (int j = 0; j < graph.Get(i).GetSize(); ++j) {
                result.PushBack(make_pair(i, graph.Get(i).Get(j)));
            }
        }
        return result;
    }

    void DirectedGraph::addVertex() noexcept { addVertex(graph.GetSize()); }

    void DirectedGraph::addVertex(int vertex) {
        if (vertex < 0) {
            throw out_of_range("Vertex index is out of range");
        } else if (isTombstone(vertex) && vertex < graph.GetSize()) {
            graph[vertex] = ListSequence<int>();
        } else if (vertex >= graph.GetSize()) {
            for (int i = graph.GetSize(); i < vertex; ++i) {
                graph.PushBack(ListSequence<int>());
                makeTombstone(i);
            }
            graph.PushBack(ListSequence<int>());
        } else {
            throw invalid_argument("Vertex already exists");
        }
    }

    void DirectedGraph::addVertex(ListSequence<int> neighbors) noexcept { addVertex(graph.GetSize(), neighbors); }

    void DirectedGraph::addVertex(int vertex, ListSequence<int> neighbors) {
        addVertex(vertex);
        graph[vertex] = neighbors;
    }

    void DirectedGraph::addEdge(int from, int to) {
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

    void DirectedGraph::removeEdge(int from, int to) {
        if (from < 0 or to < 0) {
            throw out_of_range("Vertex index is out of range");
        } else if (isTombstone(from) or isTombstone(to)) {
            throw invalid_argument("Vertex is tombstone");
        } else if (!hasEdge(from, to)) {
            throw invalid_argument("Edge doesn't exist");
        } else {
            for (int i = 0; i < graph[from].GetSize(); ++i) {
                if (graph[from].Get(i) == to) {
                    graph[from].PopFrom(i);
                    break;
                }
            }
        }
    }

    int DirectedGraph::getInDegree(int vertex) const {
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

    int DirectedGraph::getOutDegree(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        return graph.Get(vertex).GetSize();
    }

    ArraySequence<int> DirectedGraph::getInNeighbors(int vertex) const {
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

    ArraySequence<int> DirectedGraph::getOutNeighbors(int vertex) const {
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

} // namespace sem3