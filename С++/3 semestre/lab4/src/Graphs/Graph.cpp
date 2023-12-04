#include "Graph.hpp"

namespace sem3 {
    bool Graph::isTombstone(int vertex) const noexcept {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            return true;
        }
        return graph.Get(vertex).GetSize() == 1 && graph.Get(vertex).Get(0) == -1;
    }

    void Graph::makeTombstone(int vertex) noexcept {
        if (isTombstone(vertex)) {
            return;
        }
        if (vertex == graph.GetSize()) {
            graph.PopBack();
            return;
        }
        graph[vertex].Clear();
        graph[vertex].PushBack(-1);
    }

    int Graph::getVertexCount() const noexcept {
        int tombstones = getTombstones().GetSize();
        return graph.GetSize() - tombstones;
    }

    ArraySequence<int> Graph::getVertexes() const noexcept {
        ArraySequence<int> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (!isTombstone(i)) {
                result.PushBack(i);
            }
        }
        return result;
    }

    ArraySequence<int> Graph::getTombstones() const noexcept {
        ArraySequence<int> result;
        for (int i = 0; i < graph.GetSize(); ++i) {
            if (isTombstone(i)) {
                result.PushBack(i);
            }
        }
        return result;
    }

    void Graph::removeVertex(int vertex) {
        if (vertex < 0 or vertex >= graph.GetSize()) {
            throw out_of_range("Vertex index is out of range");
        }
        makeTombstone(vertex);
    }

    bool Graph::hasVertex(int vertex) const noexcept { return !isTombstone(vertex); }

    bool Graph::hasEdge(int from, int to) const noexcept {
        if (hasVertex(from) && hasVertex(to)) {
            for (int i = 0; i < graph.Get(from).GetSize(); ++i) {
                if (graph.Get(from).Get(i) == to) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::isEmpty() const noexcept { return getVertexCount() == 0; }

    bool Graph::operator==(const Graph &other) const noexcept {
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

    bool Graph::operator!=(const Graph &other) const noexcept { return !(*this == other); }

    ostream &operator<<(ostream &out, const Graph &graph) {
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
