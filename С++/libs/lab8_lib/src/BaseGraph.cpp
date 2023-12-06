#include "BaseGraph.hpp"

namespace sem3 {
    bool BaseGraph::isTombstone(int vertex) const noexcept {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            return true;
        }
        return graph.Get(vertex).GetSize() == 1 && graph.Get(vertex).Get(0) == -1;
    }

    void BaseGraph::makeTombstone(int vertex) noexcept {
        if (isTombstone(vertex)) {
            return;
        }
        if (vertex == graph.GetSize()) {
            graph.PopBack();
            return;
        }
        for (int i = 0; i < getVertexCount(); ++i) {
            if (hasEdge(i, vertex)) {
                removeEdge(i, vertex);
            }
        }
        graph[vertex].Clear();
        graph[vertex].PushBack(-1);
    }

    int BaseGraph::getVertexCount() const noexcept {
        int tombstones = getTombstones().GetSize();
        return graph.GetSize() - tombstones;
    }

    ArraySequence<int> BaseGraph::getVertexes() const noexcept {
        ArraySequence<int> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (!isTombstone(i)) {
                result.PushBack(i);
            }
        }
        return result;
    }

    ArraySequence<int> BaseGraph::getTombstones() const noexcept {
        ArraySequence<int> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (isTombstone(i)) {
                result.PushBack(i);
            }
        }
        return result;
    }

    void BaseGraph::addVertex() noexcept { addVertex(graph.GetSize()); }

    void BaseGraph::addVertex(int vertex) {
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
        }
    }

    void BaseGraph::addVertex(ListSequence<int> neighbors) noexcept { addVertex(graph.GetSize(), neighbors); }

    void BaseGraph::addVertex(int vertex, ListSequence<int> neighbors) {
        addVertex(vertex);
        graph[vertex].Clear();
        for (int i = 0; i < neighbors.GetSize(); ++i) {
            addEdge(vertex, neighbors.Get(i));
        }
    }

    void BaseGraph::removeVertex(int vertex) {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        makeTombstone(vertex);
    }

    bool BaseGraph::hasVertex(int vertex) const noexcept { return !isTombstone(vertex); }

    bool BaseGraph::hasEdge(int from, int to) const noexcept {
        if (hasVertex(from) && hasVertex(to)) {
            for (int i = 0; i < graph.Get(from).GetSize(); ++i) {
                if (graph.Get(from).Get(i) == to) {
                    return true;
                }
            }
        }
        return false;
    }

    bool BaseGraph::isEmpty() const noexcept { return getVertexCount() == 0; }

    bool BaseGraph::operator==(const BaseGraph &other) const noexcept {
        if (getVertexCount() != other.getVertexCount()) {
            return false;
        }
        for (int i = 0, j = 0; i < graph.GetSize() && j < other.graph.GetSize(); ++i, ++j) {
            if (isTombstone(i)) {
                i++;
            }
            if (other.isTombstone(j)) {
                j++;
            }
            for (int k = 0; k < graph.Get(i).GetSize(); ++k) {
                if (graph.Get(i).Get(k) != other.graph.Get(j).Get(k)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool BaseGraph::operator!=(const BaseGraph &other) const noexcept { return !(*this == other); }

    ostream &operator<<(ostream &out, const BaseGraph &graph) {
        for (int i = 0; i < graph.graph.GetSize(); ++i) {
            if (graph.isTombstone(i)) {
                continue;
            }
            out << i << ": ";
            for (int j = 0; j < graph.graph.Get(i).GetSize(); ++j) {
                out << graph.graph.Get(i).Get(j) << " ";
            }
            out << endl;
        }
        return out;
    }

} // namespace sem3
