#include "Graph.hpp"

namespace sem3 {
    Graph::Graph() noexcept { graph = ArraySequence<ListSequence<int>>(); }

    Graph::Graph(const ArraySequence<ListSequence<int>> &adjacencyList) {
        for (int i = 0; i < adjacencyList.GetSize(); ++i) {
            for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j) {
                int to = adjacencyList.Get(i).Get(j);
                try {
                    if (!adjacencyList.Get(to).TryFind(i).HasValue())
                        throw invalid_argument("Graph is not symmetric");
                } catch (const out_of_range &e) {
                    throw invalid_argument("Graph is not symmetric");
                }
            }
        }
        graph = adjacencyList;
    }

    Graph::Graph(const ArraySequence<ArraySequence<int>> &adjacencyMatrix) {
        for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
            for (int j = 0; j <= i; ++j) {
                if (adjacencyMatrix.Get(i).Get(j) != adjacencyMatrix.Get(j).Get(i))
                    throw invalid_argument("Matrix is not symmetric");
            }
        }
        for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
            for (int j = 0; j <= i; ++j) {
                if (adjacencyMatrix.Get(i).Get(j) != 0) {
                    addVertex(i);
                    addVertex(j);
                    addEdge(i, j);
                }
            }
        }
    }

    Graph::Graph(const ArraySequence<pair<int, int>> &edges) noexcept {
        for(int i = 0; i < edges.GetSize(); ++i){
            addVertex(edges.Get(i).first);
            addVertex(edges.Get(i).second);
            addEdge(edges.Get(i).first, edges.Get(i).second);
        }
    }

    Graph::Graph(const Graph &other) noexcept { graph = other.graph; }

    Graph::Graph(Graph &&other) noexcept { 
        graph = other.graph;
        other.graph = ArraySequence<ListSequence<int>>(); 
    }

    Graph &Graph::operator=(const Graph &other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = other.graph;
        return *this;
    }

    Graph &Graph::operator=(Graph &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        graph = other.graph;
        other.graph = ArraySequence<ListSequence<int>>();
        return *this;
    }

    int Graph::getEdgeCount() const noexcept {
        int result = 0;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if(!isTombstone(i))
                result += graph.Get(i).GetSize();
        }
        return result / 2;
    }

    ArraySequence<pair<int, int>> Graph::getEdges() const noexcept {
        ArraySequence<pair<int, int>> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if(!isTombstone(i))
                for (int j = 0; j < graph.Get(i).GetSize(); ++j) {
                    if (graph.Get(i).Get(j) > i) {
                        result.PushBack(make_pair(i, graph.Get(i).Get(j)));
                    }
                }
        }
        return result;
    }

    void Graph::addEdge(int from, int to) {
        if (from < 0 or to < 0 or from >= graph.GetSize() or to >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        } else if (isTombstone(from) or isTombstone(to)) {
            throw invalid_argument("Vertex is tombstone");
        } else if (hasEdge(from, to)) {
            return;
        } else {
            graph[from].PushBack(to);
            if(from != to) graph[to].PushBack(from);
        }
    }

    void Graph::removeEdge(int from, int to) {
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
            for (int i = 0; i < graph[to].GetSize(); ++i) {
                if (graph[to].Get(i) == from) {
                    graph[to].PopFrom(i);
                    break;
                }
            }
        }
    }

    int Graph::getDegree(int vertex) const {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        return graph.Get(vertex).GetSize();
    }

    ArraySequence<int> Graph::getNeighbors(int vertex) const {
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