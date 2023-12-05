#pragma once
#include "Graphs/Graph/Graph.hpp"
#include "SharedPtr.hpp"

namespace sem3 {
    class GraphProcessor {
    private:
        SharedPtr<Graph> graph;
        ArraySequence<string> color;
        ArraySequence<int> parent;
        ArraySequence<ArraySequence<int>> cycles;

        void DFS_(int vertex);
        ArraySequence<pair<int, int>> DFS_edges(int vertex);
        void resetDFS();

        ArraySequence<int> dist;
        void BFS_(int vertex);
        int doubleBFS(int vertex1, int vertex2);
        void resetBFS();

    public:
        GraphProcessor(SharedPtr<Graph> graph);
        SharedPtr<Graph> getGraph() const;
        void SetGraph(SharedPtr<Graph> graph);

        void DFS(int vertex);
        void DFS_all();
        ArraySequence<string> getColor() const;
        ArraySequence<int> getParent() const;

        ArraySequence<int> achievableFrom(int vertex);

        bool isConnected();

        bool isAcyclic();
        ArraySequence<ArraySequence<int>> getCycles();

        bool isTree();

        ArraySequence<string> colorGraph();
        ArraySequence<ArraySequence<pair<int, int>>> getSpanningTrees();

        ArraySequence<int> getDist() const;
        ArraySequence<int> BFS(int vertex);
        int distance(int vertex1, int vertex2);
    };

} // namespace sem3