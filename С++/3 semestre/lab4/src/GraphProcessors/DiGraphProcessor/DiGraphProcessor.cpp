#include "DiGraphProcessor.hpp"
#include "Collections/Queue.hpp"
#include "Collections/Stack.hpp"
#include "QuickSorter.hpp"
#include "SmartArraySequence.hpp"

namespace sem3 {
    void DiGraphProcessor::resetDFS() {
        tin = ArraySequence<int>(graph->getVertexCount(), -1);
        tout = ArraySequence<int>(graph->getVertexCount(), -1);
        color = ArraySequence<string>(graph->getVertexCount(), "white");
        parent = ArraySequence<int>(graph->getVertexCount(), -1);
        cycles.Clear();
        timer = 0;
    }

    void DiGraphProcessor::BFS_(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }

        lab3::Queue<int> q;
        q.push(vertex);
        dist[vertex] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            auto children = graph->getOutNeighbors(v);

            for (int i = 0; i < children.GetSize(); ++i) {
                int child = children[i];
                if (dist[child] == INT_MAX) {
                    dist[child] = dist[v] + 1;
                    q.push(child);
                }
            }
        }
    }

    int DiGraphProcessor::doubleBFS(int vertex1, int vertex2) {
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

        if(vertex1 == vertex2)
            return 0;

        ArraySequence<int> dist1(graph->getVertexCount(), INT_MAX);
        ArraySequence<int> dist2(graph->getVertexCount(), INT_MAX);
        lab3::Queue<int> q1;
        lab3::Queue<int> q2;
        q1.push(vertex1);
        q2.push(vertex2);
        dist1[vertex1] = 0;
        dist2[vertex2] = 0;

        while (!q1.empty() && !q2.empty()) {
            int v1 = q1.front();
            int v2 = q2.front();
            q1.pop();
            q2.pop();

            auto children1 = graph->getOutNeighbors(v1);
            auto children2 = graph->getOutNeighbors(v2);

            for (int i = 0; i < children1.GetSize(); ++i) {
                int child = children1[i];
                if (dist1[child] == INT_MAX) {
                    dist1[child] = dist1[v1] + 1;
                    q1.push(child);
                }
                if (dist2[child] != INT_MAX) {
                    return dist1[child] + dist2[child];
                }
            }

            for (int i = 0; i < children2.GetSize(); ++i) {
                int child = children2[i];
                if (dist2[child] == INT_MAX) {
                    dist2[child] = dist2[v2] + 1;
                    q2.push(child);
                }
                if (dist1[child] != INT_MAX) {
                    return dist1[child] + dist2[child];
                }
            }
        }
        return INT_MAX;
    }

    void DiGraphProcessor::resetBFS() {
        dist = ArraySequence<int>(graph->getVertexCount(), INT_MAX);
    }

    void DiGraphProcessor::DFS_(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }

        lab3::Stack<int> s;
        s.push(vertex);

        while (!s.empty()) {
            int v = s.peek();

            if (color[v] == "white") {
                tin[v] = timer++;
                color[v] = "gray";

                auto children = graph->getOutNeighbors(v);

                for (int i = 0; i < children.GetSize(); ++i) {
                    int child = children[i];
                    if (color[child] == "white") {
                        parent[child] = v;
                        s.push(child);
                    } else if (color[child] == "gray") {
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
            } else {
                tout[v] = timer++;
                color[v] = "black";
                s.pop();
            }
        }
    }

    ArraySequence<pair<int, int>> DiGraphProcessor::DFS_edges(int vertex) {
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
            int v = s.peek();

            if (color[v] == "white") {
                tin[v] = timer++;
                color[v] = "gray";
                result.PushBack(make_pair(parent[v], v));

                auto children = graph->getOutNeighbors(v);

                for (int i = 0; i < children.GetSize(); ++i) {
                    int child = children[i];
                    if (color[child] == "white") {
                        parent[child] = v;
                        s.push(child);
                    }
                }
            } else {
                tout[v] = timer++;
                color[v] = "black";
                s.pop();
            }
        }
        return result;
    }

    DiGraphProcessor::DiGraphProcessor(SharedPtr<DiGraph> graph) : graph(graph) {
        resetDFS();
        resetBFS();
    }

    SharedPtr<DiGraph> DiGraphProcessor::getGraph() const { return graph; }

    void DiGraphProcessor::SetGraph(SharedPtr<DiGraph> graph) { this->graph = graph; }

    void DiGraphProcessor::DFS(int vertex) {
        resetDFS();
        DFS_(vertex);
    }

    void DiGraphProcessor::DFS_all() {
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

    ArraySequence<int> DiGraphProcessor::getTin() const { return tin; }

    ArraySequence<int> DiGraphProcessor::getTout() const { return tout; }

    ArraySequence<string> DiGraphProcessor::getColor() const { return color; }

    ArraySequence<int> DiGraphProcessor::getParent() const { return parent; }

    ArraySequence<int> DiGraphProcessor::achievableFrom(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        DFS(vertex);
        ArraySequence<int> result;
        for (int i = 0; i < graph->getVertexCount(); ++i)
            if (color[i] == "black")
                result.PushBack(i);
        return result;
    }

    bool DiGraphProcessor::isStronglyConnected() { return getStronglyConnectedComponents().GetSize() == 1; }

    ArraySequence<ArraySequence<int>> DiGraphProcessor::getStronglyConnectedComponents() {
        ArraySequence<ArraySequence<int>> result;
        DFS_all();
        DiGraphProcessor transposed(make_shared<DiGraph>(graph->transpose()));

        ArraySequence<int> order;
        for (int i = 0; i < tout.GetSize(); ++i) {
            int max = 0;
            int max_index = 0;
            for (int j = 0; j < tout.GetSize(); ++j) {
                if (tout[j] > max) {
                    max = tout[j];
                    max_index = j;
                }
            }
            order.PushBack(max_index);
            tout[max_index] = -1;
        }
        resetDFS();

        for (int i = 0; i < order.GetSize(); ++i) {
            if (color[i] != "white")
                continue;
            transposed.DFS(order[i]);
            ArraySequence<string> component = transposed.getColor();
            ArraySequence<int> component_vertices;
            for (int j = 0; j < component.GetSize(); ++j) {
                if (component[j] == "black" && color[j] == "white") {
                    component_vertices.PushBack(j);
                    color[j] = "black";
                }
            }
            result.PushBack(component_vertices);
        }
        return result;
    }

    bool DiGraphProcessor::isAcyclic() {
        DFS_all();
        return cycles.GetSize() == 0;
    }

    ArraySequence<ArraySequence<int>> DiGraphProcessor::getCycles() {
        DFS_all();
        return cycles;
    }

    ArraySequence<int> DiGraphProcessor::topSort() {
        if (!isAcyclic())
            throw logic_error("Graph is not acyclic");
        ArraySequence<int> result;
        for (int i = 0; i < tout.GetSize(); ++i) {
            int max = 0;
            int max_index = 0;
            for (int j = 0; j < tout.GetSize(); ++j) {
                if (tout[j] > max) {
                    max = tout[j];
                    max_index = j;
                }
            }
            result.PushBack(max_index);
            tout[max_index] = -1;
        }
        return result;
    }

    int DiGraphProcessor::DAGPathsCount(int vertex) {
        if (vertex < 0 or vertex >= graph->getVertexCount()) {
            throw out_of_range("Vertex index is out of range");
        }
        if (graph->isTombstone(vertex)) {
            throw invalid_argument("Vertex is tombstone");
        }
        if (!isAcyclic())
            throw logic_error("Graph is not acyclic");

        int size = graph->getVertexCount();
        ArraySequence<int> top_sorted = topSort();
        ArraySequence<int> paths_count(size, 1);

        int i = size;
        do {
            --i;
            int v = top_sorted[i];
            auto children = graph->getOutNeighbors(v);
            for (int j = 0; j < children.GetSize(); ++j) {
                int child = children[j];
                paths_count[v] += paths_count[child];
            }
        } while (top_sorted[i] != vertex);

        return paths_count[vertex];
    }

    bool DiGraphProcessor::isTree() {
        if (!isAcyclic())
            return false;
        DFS_all();
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            if (color[i] != "black")
                return false;
        }
        return true;
    }

    ArraySequence<ArraySequence<pair<int, int>>> DiGraphProcessor::getSpanningTrees() {
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

    ArraySequence<int> DiGraphProcessor::getDist() const { return dist; }

    ArraySequence<int> DiGraphProcessor::BFS(int vertex) {
        resetBFS();
        BFS_(vertex);
        return dist;
    }

    int DiGraphProcessor::distance(int vertex1, int vertex2) {
        resetBFS();
        return doubleBFS(vertex1, vertex2);
    }
} // namespace sem3
