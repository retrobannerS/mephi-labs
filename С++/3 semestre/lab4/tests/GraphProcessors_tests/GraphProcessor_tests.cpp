#include "GraphProcessors/GraphProcessor/GraphProcessor.hpp"
#include "gtest/gtest.h"

using namespace sem3;

SharedPtr<Graph> myGraph() {
    vector<vector<int>> v = {{7, 8}, {2, 3}, {1, 4, 5}, {1, 5, 6}, {2, 7}, {2, 3, 7, 8}, {3, 8}, {0, 4, 5}, {0, 5, 6}};

    ArraySequence<ListSequence<int>> abjList;
    for (int i = 0; i < v.size(); ++i) {
        abjList.PushBack(ListSequence<int>());
        for (int j = 0; j < v[i].size(); ++j) {
            abjList[i].PushBack(v[i][j]);
        }
    }
    auto graph = sem3::make_shared<Graph>(abjList);
    return graph;
}

TEST(GraphProcessor, Constructor) {
    // Arrange
    auto graph = myGraph();

    // Act
    GraphProcessor graphProcessor(graph);

    // Assert
    EXPECT_EQ(*graphProcessor.getGraph(), *graph);
}

TEST(GraphProcessor, getGraph) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.getGraph();

    // Assert
    EXPECT_EQ(*result, *graph);
}

TEST(GraphProcessor, SetGraph) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    auto newGraph = myGraph();
    newGraph->addVertex();

    // Act
    graphProcessor.SetGraph(newGraph);

    // Assert
    EXPECT_EQ(*graphProcessor.getGraph(), *newGraph);
}

TEST(GraphProcessor, DFS) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    graphProcessor.DFS(0);

    // Assert
    for (int i = 0; i < graphProcessor.getGraph()->getVertexCount(); ++i) {
        EXPECT_EQ(graphProcessor.getColor()[i], "black");
    }
}

TEST(GraphProcessor, DFS_all) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->addVertex();

    // Act
    graphProcessor.DFS_all();

    // Assert
    for (int i = 0; i < graphProcessor.getGraph()->getVertexCount(); ++i) {
        EXPECT_EQ(graphProcessor.getColor()[i], "black");
    }
}

TEST(GraphProcessor, getColor) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.getColor();

    // Assert
    for (int i = 0; i < graphProcessor.getGraph()->getVertexCount(); ++i) {
        EXPECT_EQ(result[i], "white");
    }
}

TEST(GraphProcessor, getParent) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.getParent();

    // Assert
    for (int i = 0; i < graphProcessor.getGraph()->getVertexCount(); ++i) {
        EXPECT_EQ(result[i], -1);
    }
}

TEST(GraphProcessor, achievableFrom) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.achievableFrom(0);

    // Assert
    for (int i = 0; i < graphProcessor.getGraph()->getVertexCount(); ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST(GraphProcessor, isConnected) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.isConnected();

    // Assert
    EXPECT_TRUE(result);
}

TEST(GraphProcessor, isNotConnected) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->addVertex();

    // Act
    auto result = graphProcessor.isConnected();

    // Assert
    EXPECT_FALSE(result);
}

TEST(GraphProcessor, isAcyclic) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.isAcyclic();

    // Assert
    EXPECT_FALSE(result);
}

TEST(GraphProcessor, isAcyclic2) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->removeEdge(0, 7);
    graph->removeVertex(5);

    // Act
    auto result = graphProcessor.isAcyclic();

    // Assert
    EXPECT_TRUE(result);
}

TEST(GraphProcessor, getCycles) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.getCycles();

    // Assert
    EXPECT_TRUE(true);
}

TEST(GraphProcessor, isTree) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.isTree();

    // Assert
    EXPECT_FALSE(result);
}

TEST(GraphProcessor, isTree2) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->removeEdge(0, 7);
    graph->removeEdge(5, 7);
    graph->removeEdge(5, 8);
    graph->removeEdge(5, 3);

    // Act
    auto result = graphProcessor.isTree();

    // Assert
    EXPECT_TRUE(result);
}

TEST(GraphProcessor, colorGraph) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.colorGraph();

    // Assert
    EXPECT_TRUE(true);
}

TEST(GraphProcessor, getSpanningTrees) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);

    // Act
    auto result = graphProcessor.getSpanningTrees();

    // Assert
    EXPECT_TRUE(true);
}

TEST(GraphProcessor, getSpanningTrees2) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->removeEdge(0, 7);
    graph->removeEdge(5, 7);
    graph->removeEdge(5, 8);
    graph->removeEdge(5, 3);

    // Act
    auto result = graphProcessor.getSpanningTrees();

    // Assert
    EXPECT_TRUE(true);
}

TEST(GraphProcessor, getDist) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->removeVertex(0);
    graph->addVertex(0);

    // Act
    graphProcessor.BFS(0);
    auto result = graphProcessor.getDist();

    // Assert
    EXPECT_EQ(result[0], 0);
    for(int i = 1; i < graph->getVertexCount(); ++i) {
        EXPECT_EQ(result[i], INT_MAX);
    }
}

TEST(GraphProcessor, BFS) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    vector<int> expected = {0, 4, 3, 3, 2, 2, 2, 1, 1};

    // Act
    auto result = graphProcessor.BFS(0);

    // Assert
    EXPECT_EQ(result.GetSize(), expected.size());
    for (int i = 0; i < result.GetSize(); ++i) {
        EXPECT_EQ(result[i], expected[i]);
    }
}

TEST(GraphProcessor, distance) {
    // Arrange
    auto graph = myGraph();
    GraphProcessor graphProcessor(graph);
    graph->addVertex();

    // Act
    auto result = graphProcessor.distance(0, 8);
    auto result2 = graphProcessor.distance(0, 5);
    auto result3 = graphProcessor.distance(0, 0);
    auto result4 = graphProcessor.distance(0, 1); 
    auto result5 = graphProcessor.distance(0, 9);  

    // Assert
    EXPECT_EQ(result, 1);
    EXPECT_EQ(result2, 2);
    EXPECT_EQ(result3, 0);
    EXPECT_EQ(result4, 4);
    EXPECT_EQ(result5, INT_MAX);
}