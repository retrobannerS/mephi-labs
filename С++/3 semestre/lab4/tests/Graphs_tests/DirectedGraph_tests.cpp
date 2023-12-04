#include "Graphs/DirectedGraph.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace sem3;
using namespace lab2;

ArraySequence<ListSequence<int>> getAdjacencyList() {
    vector<vector<int>> adjacencyList = {{1, 2, 3}, {0}, {0, 1, 3}, {1}};
    ArraySequence<ListSequence<int>> result;
    for (int i = 0; i < adjacencyList.size(); ++i) {
        result.PushBack(ListSequence<int>());
        for (int j = 0; j < adjacencyList[i].size(); ++j) {
            result[i].PushBack(adjacencyList[i][j]);
        }
    }
    return result;
}

TEST(DirectedGraph, DefaultConstructor) {
    // Arrange

    // Act
    DirectedGraph graph;

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 0);
}

TEST(DirectedGraph, ConstructorFromAdjacencyList) {
    // Arrange
    auto adjacencyList = getAdjacencyList();

    // Act
    DirectedGraph graph(adjacencyList);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graph.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
}

TEST(DirectedGraph, ConstructorFromAdjacencyMatrix) {
    // Arrange
    vector<vector<int>> vec = {{0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
    ArraySequence<ArraySequence<int>> adjacencyMatrix(vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            adjacencyMatrix[i].PushBack(vec[i][j]);
        }
    }

    // Act
    DirectedGraph graph(adjacencyMatrix);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyMatrix.GetSize());
    for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
        for (int j = 0; j < adjacencyMatrix.GetSize(); ++j)
            EXPECT_EQ(graph.hasEdge(i, j), adjacencyMatrix.Get(i).Get(j));
    }
}

TEST(DirectedGraph, ConstructorFromEdges) {
    // Arrange
    ArraySequence<pair<int, int>> edges;
    edges.PushBack(make_pair(0, 1));
    edges.PushBack(make_pair(0, 2));
    edges.PushBack(make_pair(0, 3));
    edges.PushBack(make_pair(1, 0));
    edges.PushBack(make_pair(1, 2));
    edges.PushBack(make_pair(1, 3));
    edges.PushBack(make_pair(2, 0));
    edges.PushBack(make_pair(2, 1));
    edges.PushBack(make_pair(2, 3));

    // Act
    DirectedGraph graph(edges);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 4);
    EXPECT_EQ(graph.getEdgeCount(), 9);
    for (int i = 0; i < edges.GetSize(); ++i) {
        EXPECT_TRUE(graph.hasEdge(edges.Get(i).first, edges.Get(i).second));
    }
}

TEST(DirectedGraph, CopyConstructor) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    DirectedGraph graphCopy(graph);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), graphCopy.getVertexCount());
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(i).GetSize(), graphCopy.getOutNeighbors(i).GetSize());
        for (int j = 0; j < graph.getOutNeighbors(i).GetSize(); ++j) {
            EXPECT_EQ(graph.getOutNeighbors(i)[j], graphCopy.getOutNeighbors(i)[j]);
        }
    }
}

TEST(DirectedGraph, MoveConstructor) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    DirectedGraph graphCopy(std::move(graph));

    // Assert
    EXPECT_EQ(graphCopy.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graphCopy.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
}

TEST(DirectedGraph, CopyAssignment) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    DirectedGraph graphCopy;

    // Act
    graphCopy = graph;

    // Assert
    EXPECT_EQ(graph.getVertexCount(), graphCopy.getVertexCount());
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(i).GetSize(), graphCopy.getOutNeighbors(i).GetSize());
        for (int j = 0; j < graph.getOutNeighbors(i).GetSize(); ++j) {
            EXPECT_EQ(graph.getOutNeighbors(i)[j], graphCopy.getOutNeighbors(i)[j]);
        }
    }
}

TEST(DirectedGraph, MoveAssignment) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    DirectedGraph graphCopy;

    // Act
    graphCopy = std::move(graph);

    // Assert
    EXPECT_EQ(graphCopy.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graphCopy.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
}

TEST(DirectedGraph, GetVertexCount) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
}

TEST(DirectedGraph, GetVertexCountAfterRemove) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.removeVertex(0);
    
    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
}

TEST(DirectedGraph, GetVertexCountAfterAdd) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.addVertex();

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
}

TEST(DirectedGraph, GetEdgeCount) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }
    // Act

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount);
}

TEST(DirectedGraph, GetEdgeCountAfterAdd) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }

    // Act
    graph.addEdge(1, 3);

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount + 1);
}

TEST(DirectedGraph, GetEdgeCountAfterRemove) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }

    // Act
    graph.removeEdge(1, 0);

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount - 1);
}

TEST(DirectedGraph, GetVertexes) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    auto vertexes = graph.getVertexes();

    // Assert
    EXPECT_EQ(vertexes.GetSize(), adjacencyList.GetSize());
    for (int i = 0; i < vertexes.GetSize(); ++i) {
        EXPECT_EQ(vertexes.Get(i), i);
    }
}

TEST(DirectedGraph, GetEdges) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    ArraySequence<pair<int, int>> edges;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j) {
            edges.PushBack(make_pair(i, adjacencyList.Get(i).Get(j)));
        }
    }

    // Act
    auto edgesFromGraph = graph.getEdges();

    // Assert
    EXPECT_EQ(edges.GetSize(), edgesFromGraph.GetSize());
    for (int i = 0; i < edges.GetSize(); ++i) {
        EXPECT_EQ(edges.Get(i).first, edgesFromGraph.Get(i).first);
        EXPECT_EQ(edges.Get(i).second, edgesFromGraph.Get(i).second);
    }
}

TEST(DirectedGraph, GetTombstonesEmpty) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    auto tombstones = graph.getTombstones();

    // Assert
    EXPECT_TRUE(tombstones.Empty());
}

TEST(DirectedGraph, GetTombstones) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    graph.removeVertex(0);
    graph.removeVertex(2);

    // Act
    auto tombstones = graph.getTombstones();

    // Assert
    EXPECT_EQ(tombstones.GetSize(), 2);
    EXPECT_EQ(tombstones.Get(0), 0);
    EXPECT_EQ(tombstones.Get(1), 2);
}

TEST(DirectedGraph, AddVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.addVertex();

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize()).GetSize(), 0);
}

TEST(DirectedGraph, AddAssignedVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    graph.removeVertex(1);

    // Act
    graph.addVertex(1);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
    EXPECT_EQ(graph.getOutNeighbors(1).GetSize(), 0);
}

TEST(DirectedGraph, AddAssignedVertexAfterSize) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.addVertex(adjacencyList.GetSize() + 10);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10).GetSize(), 0);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 1), invalid_argument);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 11), out_of_range);
}

TEST(DirectedGraph, AddAssignedVertexExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    
    // Act
    EXPECT_THROW(graph.addVertex(1), invalid_argument);
    EXPECT_THROW(graph.addVertex(0), invalid_argument);
    EXPECT_THROW(graph.addVertex(-1), out_of_range);
}

TEST(DirectedGraph, AddVertexWithNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act
    graph.addVertex(neighbors);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize()).GetSize(), neighbors.GetSize());
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize())[i], neighbors[i]);
    }
}

TEST(DirectedGraph, AddVertexWithAssignedNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act
    graph.addVertex(adjacencyList.GetSize() + 10, neighbors);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10).GetSize(), neighbors.GetSize());
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10)[i], neighbors[i]);
    }
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 1), invalid_argument);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 11), out_of_range);
}

TEST(DirectedGraph, AddVertexWithNeighborsExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act
    EXPECT_THROW(graph.addVertex(1, neighbors), invalid_argument);
    EXPECT_THROW(graph.addVertex(0, neighbors), invalid_argument);
    EXPECT_THROW(graph.addVertex(-1, neighbors), out_of_range);
}

TEST(DirectedGraph, AddEdge) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.addEdge(1, 3);

    // Assert
    EXPECT_TRUE(graph.hasEdge(1, 3));
}

TEST(DirectedGraph, AddEdgeExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_THROW(graph.addEdge(0, 4), out_of_range);
    EXPECT_THROW(graph.addEdge(4, 0), out_of_range);
    EXPECT_THROW(graph.addEdge(4, 4), out_of_range);
}

TEST(DirectedGraph, RemoveVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.removeVertex(0);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
    EXPECT_TRUE(graph.isTombstone(0));
}

TEST(DirectedGraph, RemoveLastVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.removeVertex(adjacencyList.GetSize() - 1);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
    EXPECT_TRUE(graph.isTombstone(adjacencyList.GetSize() - 1));
}

TEST(DirectedGraph, RemoveVertexExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.removeVertex(1);

    // Assert
    EXPECT_THROW(graph.removeVertex(-1), out_of_range);
    EXPECT_THROW(graph.removeVertex(4), out_of_range);
}

TEST(DirectedGraph, RemoveEdge) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act
    graph.removeEdge(1, 0);

    // Assert
    EXPECT_FALSE(graph.hasEdge(1, 0));
}


TEST(DirectedGraph, GetVertexInDegree) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_EQ(graph.getInDegree(0), 2);
    EXPECT_EQ(graph.getInDegree(1), 3);
    EXPECT_EQ(graph.getInDegree(2), 1);
    EXPECT_EQ(graph.getInDegree(3), 2);
}

TEST(DirectedGraph, GetVertexOutDegree) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act

    // Assert
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutDegree(i), adjacencyList.Get(i).GetSize());
    }
}

TEST(DirectedGraph, HasVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DirectedGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_TRUE(graph.hasVertex(0));
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
    EXPECT_TRUE(graph.hasVertex(3));
    EXPECT_FALSE(graph.hasVertex(4));
}



