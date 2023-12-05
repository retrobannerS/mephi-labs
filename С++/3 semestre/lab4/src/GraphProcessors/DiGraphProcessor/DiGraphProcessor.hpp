#pragma once
#include "Graphs/DiGraph/DiGraph.hpp"
#include "SharedPtr.hpp"

namespace sem3 {
    class DiGraphProcessor {
    private:
        SharedPtr<DiGraph> graph;
        ArraySequence<int> tin;
        ArraySequence<int> tout;
        ArraySequence<string> color;
        ArraySequence<int> parent;
        ArraySequence<ArraySequence<int>> cycles;
        int timer;

        void DFS_(int vertex);
        ArraySequence<pair<int, int>> DFS_edges(int vertex);
        void resetDFS();

        ArraySequence<int> dist;
        void BFS_(int vertex);
        int doubleBFS(int vertex1, int vertex2);
        void resetBFS();

    public:
        DiGraphProcessor(SharedPtr<DiGraph> graph);
        SharedPtr<DiGraph> getGraph() const;
        void SetGraph(SharedPtr<DiGraph> graph);

        void DFS(int vertex);
        void DFS_all();
        ArraySequence<int> getTin() const;
        ArraySequence<int> getTout() const;
        ArraySequence<string> getColor() const;
        ArraySequence<int> getParent() const;

        ArraySequence<int> achievableFrom(int vertex);

        bool isStronglyConnected();
        ArraySequence<ArraySequence<int>> getStronglyConnectedComponents();

        bool isAcyclic();
        ArraySequence<ArraySequence<int>> getCycles();
        ArraySequence<int> topSort();
        int DAGPathsCount(int vertex);

        bool isTree();
        ArraySequence<ArraySequence<pair<int, int>>> getSpanningTrees();

        ArraySequence<int> getDist() const;
        ArraySequence<int> BFS(int vertex);
        int distance(int vertex1, int vertex2);
    };
} // namespace sem3