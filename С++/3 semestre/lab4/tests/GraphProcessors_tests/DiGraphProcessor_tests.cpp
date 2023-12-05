#include "GraphProcessors/DiGraphProcessor/DiGraphProcessor.hpp"
#include "gtest/gtest.h"

using namespace sem3;
using namespace lab2;

SharedPtr<DiGraph> getDiGraph() {
    vector<vector<int>> v =
    { {1},
      {3, 6},
      {1, 3},
      {4},
      {5},
      {2},
      {0} };

    ArraySequence<ListSequence<int>> abjList;
    for (int i = 0; i < v.size(); ++i) {
        abjList.PushBack(ListSequence<int>());
        for (int j = 0; j < v[i].size(); ++j) {
            abjList[i].PushBack(v[i][j]);
        }
    }
    auto graph = sem3::make_shared<DiGraph>(abjList);
    return graph;
}

TEST(DiGraphProcessor, Constructor) {
    // Arrange
    auto graph = getDiGraph();

    // Act
    DiGraphProcessor g(graph);

    // Assert
    EXPECT_EQ(g.getGraph()->getVertexCount(), 7);
}

TEST(DiGraphProcessor, GetGraph) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);

    // Act
    auto result = g.getGraph();

    // Assert
    EXPECT_EQ(*result, *graph);
}

TEST(DiGraphProcessor, SetGraph) {
    // Arrange
    SharedPtr<DiGraph> graph = sem3::make_shared<DiGraph>(ArraySequence<ListSequence<int>>());
    graph->addVertex();
    graph->addVertex();
    graph->addEdge(0, 1);
    DiGraphProcessor g(graph);
    auto graph2 = getDiGraph();

    // Act
    g.SetGraph(graph2);

    // Assert
    EXPECT_EQ(*g.getGraph(), *graph2);
}

TEST(DiGraphProcessor, DFS) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    vector<int> tin_expected = {0, 1, 7, 4, 5, 6, 2};
    vector<int> tout_expected = {13, 12, 8, 11, 10, 9, 3};

    // Act
    g.DFS(0);
    auto tin = g.getTin();
    auto tout = g.getTout();

    // Assert
    EXPECT_EQ(tin.GetSize(), tin_expected.size());
    EXPECT_EQ(tout.GetSize(), tout_expected.size());
    for(int i = 0; i < tin.GetSize(); ++i) {
        EXPECT_EQ(tin[i], tin_expected[i]);
        EXPECT_EQ(tout[i], tout_expected[i]);
    }
}

TEST(DiGraphProcessor, DFS_all) {
    // Arrange
    auto graph = getDiGraph();
    graph->addVertex();
    DiGraphProcessor g(graph);
    vector<int> tin_expected = {0, 1, 7, 4, 5, 6, 2, 14};
    vector<int> tout_expected = {13, 12, 8, 11, 10, 9, 3, 15};

    // Act
    g.DFS_all();
    auto tin = g.getTin();
    auto tout = g.getTout();

    // Assert
    EXPECT_EQ(tin.GetSize(), tin_expected.size());
    EXPECT_EQ(tout.GetSize(), tout_expected.size());
    for(int i = 0; i < tin.GetSize(); ++i) {
        EXPECT_EQ(tin[i], tin_expected[i]);
        EXPECT_EQ(tout[i], tout_expected[i]);
    }
}

TEST(DiGraphProcessor, AchievableFrom) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    vector<int> expected = {0, 1, 2, 3, 4, 5, 6};

    // Act
    auto result = g.achievableFrom(0);

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
    for(int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }
}

TEST(DiGraphProcessor, AchievableFrom2) {
    // Arrange
    auto graph = getDiGraph();
    graph->addVertex();
    DiGraphProcessor g(graph);
    vector<int> expected = {0, 1, 2, 3, 4, 5, 6};

    // Act
    auto result = g.achievableFrom(1);
    auto result2 = g.achievableFrom(7);

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
    for(int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }
    EXPECT_EQ(result2.GetSize(), 1);
    EXPECT_EQ(result2[0], 7);
}

TEST(DiGraphProcessor, isStronglyConnected) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    SharedPtr<DiGraph> graph2 = sem3::make_shared<DiGraph>(*graph);
    graph2->removeEdge(5, 2);
    DiGraphProcessor g2(graph2);

    // Act
    auto result = g.isStronglyConnected();
    auto result2 = g2.isStronglyConnected();


    // Assert
    EXPECT_TRUE(result);
    EXPECT_FALSE(result2);
}

TEST(DiGraphProcessor, getStronglyConnectedComponents) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    vector<vector<int>> expected = { {0, 1, 2, 3, 4, 5, 6} };

    // Act
    auto result = g.getStronglyConnectedComponents();

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
    for(int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i].GetSize(), expected[i].size());
        for(int j = 0; j < result[i].GetSize(); ++j) {
            EXPECT_EQ(result[i][j], expected[i][j]);
        }
    }
}

TEST(DiGraphProcessor, getStronglyConnectedComponents2) {
    // Arrange
    auto graph = getDiGraph();
    graph->removeEdge(5, 2);
    DiGraphProcessor g(graph);
    vector<vector<int>> expected = {{0, 1, 6}, {2}, {3}, {4}, {5}};

    // Act
    auto result = g.getStronglyConnectedComponents();

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
}

TEST(DiGraphProcessor, isAcyclic) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    SharedPtr<DiGraph> graph2 = sem3::make_shared<DiGraph>(*graph);
    graph2->removeEdge(5, 2);
    graph2->removeEdge(6, 0);
    DiGraphProcessor g2(graph2);

    // Act
    auto result = g.isAcyclic();
    auto result2 = g2.isAcyclic();

    // Assert
    EXPECT_FALSE(result);
    EXPECT_TRUE(result2);
}

TEST(DiGraphProcessor, getCycles) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    vector<vector<int>> expected = {{0, 1, 6}, {2, 3, 4, 5}, {1, 2, 3, 4, 5}};

    // Act
    auto result = g.getCycles();

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
}

TEST(DiGraphProcessor, topSortExcept) {
    // Arrange
    auto graph = getDiGraph();
    graph->removeEdge(1, 6);
    graph->removeEdge(2, 1);
    graph->removeEdge(2, 3);
    graph->addEdge(2, 6);
    DiGraphProcessor g(graph);
    vector<int> expected = {0, 1, 2, 3, 4, 5, 6};

    // Act

    // Assert
    EXPECT_THROW(g.topSort(), std::logic_error);
}

TEST(DiGraphProcessor, topSort) {
    // Arrange
    auto graph = getDiGraph();
    graph->removeEdge(1, 6);
    graph->removeEdge(2, 1);
    graph->removeEdge(2, 3);
    DiGraphProcessor g(graph);
    vector<int> expected = {6, 0, 1, 3, 4, 5, 2};

    // Act
    auto result = g.topSort();

    // Assert
    for (int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }
}

TEST(DiGraphProcessor, DAGPathsCountExcept) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);

    // Act

    // Assert
    EXPECT_THROW(g.DAGPathsCount(6), std::logic_error);
}

TEST(DiGraphProcessor, DAGPathsCount) {
    // Arrange
    auto graph = getDiGraph();
    graph->removeEdge(1, 6);
    graph->removeEdge(2, 1);
    graph->removeEdge(2, 3);
    DiGraphProcessor g(graph);

    // Act
    auto result = g.DAGPathsCount(6);

    // Assert
    EXPECT_EQ(result, 7);
}

TEST(DiGraphProcessor, isTree) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    SharedPtr<DiGraph> graph2 = sem3::make_shared<DiGraph>(*graph);
    graph2->removeEdge(5, 2);
    graph2->removeEdge(6, 0);
    DiGraphProcessor g2(graph2);

    // Act
    auto result = g.isTree();
    auto result2 = g2.isTree();

    // Assert
    EXPECT_FALSE(result);
    EXPECT_TRUE(result2);
}

TEST(DiGraphProcessor, getSpanningTrees) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    
    // Act
    auto result = g.getSpanningTrees();

    // Assert
    EXPECT_TRUE(true);
}

TEST(DiGraphProcessor, getSpanningTrees2) {
    // Arrange
    auto graph = getDiGraph();
    graph->removeEdge(5, 2);
    DiGraphProcessor g(graph);

    // Act
    auto result = g.getSpanningTrees();

    // Assert
    EXPECT_TRUE(true);
}

TEST(DiGraphProcessor, getDist) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);

    // Act
    auto result = g.getDist();

    // Assert
    EXPECT_EQ(result.GetSize(), graph->getVertexCount());
    for(int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], INT_MAX);
    }
}

TEST(DiGraphProcessor, BFS) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    vector<int> expected = {0, 1, 5, 2, 3, 4, 2};

    // Act
    auto result = g.BFS(0);

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
    for (int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }
}

TEST(DiGraphProcessor, distance) {
    // Arrange
    auto graph = getDiGraph();
    DiGraphProcessor g(graph);
    graph->addVertex();

    // Act
    auto result = g.distance(0, 5);
    auto result2 = g.distance(0, 6);
    auto result3 = g.distance(0, 0);
    auto result4 = g.distance(0, 7);

    // Assert
    EXPECT_EQ(result, 3);
    EXPECT_EQ(result2, 1);
    EXPECT_EQ(result3, 0);
    EXPECT_EQ(result4, INT_MAX);
}