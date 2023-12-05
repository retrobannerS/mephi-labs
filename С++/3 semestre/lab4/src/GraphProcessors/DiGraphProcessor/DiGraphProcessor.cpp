#include "DiGraphProcessor.hpp"
#include "Collections/Stack.hpp"
#include "QuickSorter.hpp"
#include "SmartArraySequence.hpp"

namespace sem3 {
    void DiGraphProcessor::reset() {
        tin = ArraySequence<int>(graph->getVertexCount(), -1);
        tout = ArraySequence<int>(graph->getVertexCount(), -1);
        color = ArraySequence<string>(graph->getVertexCount(), "white");
        parent = ArraySequence<int>(graph->getVertexCount(), -1);
        cycles.Clear();
        timer = 0;
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

    DiGraphProcessor::DiGraphProcessor(SharedPtr<DiGraph> graph) : graph(graph) {}

    SharedPtr<DiGraph> DiGraphProcessor::getGraph() const { return graph; }

    void DiGraphProcessor::SetGraph(SharedPtr<DiGraph> graph) { this->graph = graph; }

    void DiGraphProcessor::DFS(int vertex) {
        reset();
        DFS_(vertex);
    }

    void DiGraphProcessor::DFS_all() {
        reset();
        for (int i = 0; i < graph->getVertexCount(); ++i) {
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
        reset();

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

} // namespace sem3
