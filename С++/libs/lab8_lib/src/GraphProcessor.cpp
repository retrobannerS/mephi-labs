#include "GraphProcessor.hpp"
#include "Collections/Queue.hpp"
#include "Collections/Stack.hpp"
#include <climits>

namespace sem3 {
    void GraphProcessor::DFS_(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }

        lab3::Stack<int> s;
        s.push(vertex);

        while (!s.empty()) {
            int v = s.pop();

            if (color[v] == "black") {
                continue;
            }
            color[v] = "black";

            auto children = graph->getNeighbors(v);
            for (int i = 0; i < children.GetSize(); ++i) {
                int child = children[i];
                if (color[child] == "white") {
                    parent[child] = v;
                    s.push(child);
                } else if (color[child] == "black" && parent[v] != child) {
                    ArraySequence<int> cycle;
                    cycle.PushBack(v);
                    int cur = parent[v];
                    while (cur != child) {
                        cycle.PushBack(cur);
                        cur = parent[cur];
                    }
                    cycle.PushBack(child);
                    cycles.PushBack(cycle);
                }
            }
        }
    }

    ArraySequence<pair<int, int>> GraphProcessor::DFS_edges(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }

        ArraySequence<pair<int, int>> result;
        lab3::Stack<int> s;
        s.push(vertex);

        while (!s.empty()) {
            int v = s.pop();

            if (color[v] == "black") {
                continue;
            }
            color[v] = "black";
            result.PushBack({parent[v], v});

            auto children = graph->getNeighbors(v);
            for (int i = 0; i < children.GetSize(); ++i) {
                int child = children[i];
                if (color[child] == "white") {
                    parent[child] = v;
                    s.push(child);
                } else if (color[child] == "black") {
                    continue;
                }
            }
        }
        return result;
    }

    void GraphProcessor::resetDFS() {
        color = ArraySequence<string>(graph->getVertexCount(), "white");
        parent = ArraySequence<int>(graph->getVertexCount(), -1);
        cycles.Clear();
    }

    void GraphProcessor::BFS_(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        dist[vertex] = 0;
        lab3::Queue<int> q;
        q.push(vertex);

        while (!q.empty()) {
            int v = q.pop();
            auto children = graph->getNeighbors(v);
            for (int i = 0; i < children.GetSize(); ++i) {
                int child = children[i];
                if (dist[child] == INT_MAX) {
                    dist[child] = dist[v] + 1;
                    q.push(child);
                }
            }
        }
    }

    int GraphProcessor::doubleBFS(int vertex1, int vertex2) {
        if (vertex1 < 0 or vertex1 >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (vertex2 < 0 or vertex2 >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex1)) {
            throw invalid_argument("Vertex is tombstone");
        }
        if (graph->isTombstone(vertex2)) {
            throw invalid_argument("Vertex is tombstone");
        }
        if (vertex1 == vertex2) {
            return 0;
        }

        ArraySequence<int> visited1(graph->getVertexCount(), INT_MAX);
        ArraySequence<int> visited2(graph->getVertexCount(), INT_MAX);
        lab3::Queue<int> q1;
        lab3::Queue<int> q2;
        visited1[vertex1] = 0;
        visited2[vertex2] = 0;
        q1.push(vertex1);
        q2.push(vertex2);

        while (!q1.empty() && !q2.empty()) {
            int v1 = q1.pop();

            auto children1 = graph->getNeighbors(v1);
            for (int i = 0; i < children1.GetSize(); ++i) {
                int child1 = children1[i];
                if (visited1[child1] == INT_MAX) {
                    visited1[child1] = visited1[v1] + 1;
                    q1.push(child1);
                }
                if (visited2[child1] != INT_MAX) {
                    return visited1[child1] + visited2[child1];
                }
            }

            int v2 = q2.pop();

            auto children2 = graph->getNeighbors(v2);
            for (int i = 0; i < children2.GetSize(); ++i) {
                int child2 = children2[i];
                if (visited2[child2] == INT_MAX) {
                    visited2[child2] = visited2[v2] + 1;
                    q2.push(child2);
                }
                if (visited1[child2] != INT_MAX) {
                    return visited1[child2] + visited2[child2];
                }
            }
        }

        return INT_MAX;
    }

    void GraphProcessor::resetBFS() { dist = ArraySequence<int>(graph->getVertexCount(), INT_MAX); }

    sem3::GraphProcessor::GraphProcessor(SharedPtr<Graph> graph) : graph(graph) {
        resetDFS();
        resetBFS();
    }

    SharedPtr<Graph> GraphProcessor::getGraph() const { return graph; }

    void GraphProcessor::SetGraph(SharedPtr<Graph> graph) { this->graph = graph; }

    void GraphProcessor::DFS(int vertex) {
        resetDFS();
        DFS_(vertex);
    }

    void GraphProcessor::DFS_all() {
        resetDFS();
        for (int i = 0; i <= graph->getVertexes().GetLast(); ++i) {
            if (graph->isTombstone(i)) {
                continue;
            }
            if (color[i] == "white") {
                DFS_(i);
            }
        }
    }

    ArraySequence<string> GraphProcessor::getColor() const { return color; }

    ArraySequence<int> GraphProcessor::getParent() const { return parent; }

    ArraySequence<int> GraphProcessor::achievableFrom(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }

        ArraySequence<int> result;
        DFS(vertex);
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            if (color[i] == "black") {
                result.PushBack(i);
            }
        }
        return result;
    }

    bool GraphProcessor::isConnected() {
        DFS(0);
        for (int i = 0; i <= graph->getVertexes().GetLast(); ++i) {
            if (color[i] == "white" && !graph->isTombstone(i)) {
                return false;
            }
        }
        return true;
    }

    bool GraphProcessor::isAcyclic() {
        DFS_all();
        return cycles.GetSize() == 0;
    }

    ArraySequence<ArraySequence<int>> GraphProcessor::getCycles() {
        DFS_all();
        return cycles;
    }

    bool GraphProcessor::isTree() { return isConnected() && isAcyclic(); }

    ArraySequence<string> GraphProcessor::colorGraph() {
        int vCount = graph->getVertexCount();

        ArraySequence<int> result(vCount, -1);
        result[0] = 0;

        ArraySequence<bool> available(vCount, true);

        for (int u = 1; u < vCount; u++) {
            for (int i = 0; i < graph->getNeighbors(u).GetSize(); i++) {
                int adj = graph->getNeighbors(u).Get(i);
                if (result[adj] != -1)
                    available[result[adj]] = false;
            }

            int cr;
            for (cr = 0; cr < vCount; cr++)
                if (available[cr])
                    break;

            result[u] = cr;

            available = ArraySequence<bool>(vCount, true);
        }

        for (int u = 0; u < vCount; u++)
            switch (result[u]) {
            case 0:
                color[u] = "red";
                break;
            case 1:
                color[u] = "green";
                break;
            case 2:
                color[u] = "blue";
                break;
            case 3:
                color[u] = "yellow";
                break;
            case 4:
                color[u] = "orange";
                break;
            case 5:
                color[u] = "purple";
                break;
            case 6:
                color[u] = "pink";
                break;
            case 7:
                color[u] = "brown";
                break;
            case 8:
                color[u] = "gray";
                break;
            case 9:
                color[u] = "black";
                break;
            default:
                color[u] = "white";
                break;
            }
        return color;
    }

    ArraySequence<ArraySequence<pair<int, int>>> GraphProcessor::getSpanningTrees() {
        resetDFS();
        ArraySequence<ArraySequence<pair<int, int>>> result;
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            if (graph->isTombstone(i)) {
                continue;
            }
            if (color[i] == "white") {
                ArraySequence<pair<int, int>> spanningTree = DFS_edges(i);
                spanningTree.PopFront();
                result.PushBack(spanningTree);
            }
        }
        return result;
    }

    ArraySequence<int> GraphProcessor::getDist() const { return dist; }

    ArraySequence<int> GraphProcessor::BFS(int vertex) {
        resetBFS();
        BFS_(vertex);
        return dist;
    }

    int GraphProcessor::distance(int vertex1, int vertex2) {
        resetBFS();
        return doubleBFS(vertex1, vertex2);
    }

} // namespace sem3