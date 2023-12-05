#include "Graphs/DiGraph/DiGraph.hpp"
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

TEST(DiGraph, DefaultConstructor) {
    // Arrange

    // Act
    DiGraph graph;

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 0);
    EXPECT_EQ(graph.getEdgeCount(), 0);
}

TEST(DiGraph, ConstructorFromAdjacencyList) {
    // Arrange
    auto adjacencyList = getAdjacencyList();

    // Act
    DiGraph graph(adjacencyList);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graph.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
}

TEST(DiGraph, ConstructorFromAdjacencyMatrix) {
    // Arrange
    vector<vector<int>> vec = {{0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
    ArraySequence<ArraySequence<int>> adjacencyMatrix(vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            adjacencyMatrix[i].PushBack(vec[i][j]);
        }
    }

    // Act
    DiGraph graph(adjacencyMatrix);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyMatrix.GetSize());
    for (int i = 0; i < adjacencyMatrix.GetSize(); ++i) {
        for (int j = 0; j < adjacencyMatrix.GetSize(); ++j)
            EXPECT_EQ(graph.hasEdge(i, j), adjacencyMatrix.Get(i).Get(j));
    }
}

TEST(DiGraph, ConstructorFromEdges) {
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
    DiGraph graph(edges);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 4);
    EXPECT_EQ(graph.getEdgeCount(), 9);
    for (int i = 0; i < edges.GetSize(); ++i) {
        EXPECT_TRUE(graph.hasEdge(edges.Get(i).first, edges.Get(i).second));
    }
}

TEST(DiGraph, ConstructorFromEdges2) {
    // Arrange
    ArraySequence<pair<int, int>> edges;
    edges.PushBack(make_pair(0, 4));

    // Act
    DiGraph graph(edges);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 2);
    EXPECT_EQ(graph.getEdgeCount(), 1);
    EXPECT_TRUE(graph.hasEdge(0, 4));
    for(int i = 1; i < 4; ++i){
        EXPECT_TRUE(graph.isTombstone(1));
    }

}

TEST(DiGraph, CopyConstructor) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    DiGraph graphCopy(graph);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), graphCopy.getVertexCount());
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(i).GetSize(), graphCopy.getOutNeighbors(i).GetSize());
        for (int j = 0; j < graph.getOutNeighbors(i).GetSize(); ++j) {
            EXPECT_EQ(graph.getOutNeighbors(i)[j], graphCopy.getOutNeighbors(i)[j]);
        }
    }
}

TEST(DiGraph, MoveConstructor) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    DiGraph graphCopy(std::move(graph));

    // Assert
    EXPECT_EQ(graphCopy.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graphCopy.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
    EXPECT_EQ(graph.getVertexCount(), 0);
}

TEST(DiGraph, CopyAssignment) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    DiGraph graphCopy;

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

TEST(DiGraph, MoveAssignment) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    DiGraph graphCopy;

    // Act
    graphCopy = std::move(graph);

    // Assert
    EXPECT_EQ(graphCopy.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j)
            EXPECT_EQ(graphCopy.getOutNeighbors(i)[j], adjacencyList.Get(i)[j]);
    }
    EXPECT_EQ(graph.getVertexCount(), 0);
}

TEST(DiGraph, GetVertexCount) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
}

TEST(DiGraph, GetVertexCountAfterRemove) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.removeVertex(0);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
}

TEST(DiGraph, GetVertexCountAfterAdd) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.addVertex();

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
}

TEST(DiGraph, GetEdgeCount) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }
    // Act

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount);
}

TEST(DiGraph, GetEdgeCountAfterAdd) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }

    // Act
    graph.addEdge(1, 3);

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount + 1);
}

TEST(DiGraph, GetEdgeCountAfterRemove) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    int edgeCount = 0;
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        edgeCount += adjacencyList.Get(i).GetSize();
    }

    // Act
    graph.removeEdge(1, 0);

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), edgeCount - 1);
}

TEST(DiGraph, GetVertexes) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    auto vertexes = graph.getVertexes();

    // Assert
    EXPECT_EQ(vertexes.GetSize(), adjacencyList.GetSize());
    for (int i = 0; i < vertexes.GetSize(); ++i) {
        EXPECT_EQ(vertexes.Get(i), i);
    }
}

TEST(DiGraph, GetEdges) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
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

TEST(DiGraph, GetTombstonesEmpty) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    auto tombstones = graph.getTombstones();

    // Assert
    EXPECT_TRUE(tombstones.Empty());
}

TEST(DiGraph, GetTombstones) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    graph.removeVertex(0);
    graph.removeVertex(2);

    // Act
    auto tombstones = graph.getTombstones();

    // Assert
    EXPECT_EQ(tombstones.GetSize(), 2);
    EXPECT_EQ(tombstones.Get(0), 0);
    EXPECT_EQ(tombstones.Get(1), 2);
}

TEST(DiGraph, AddVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.addVertex();

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize()).GetSize(), 0);
}

TEST(DiGraph, AddAssignedVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    graph.removeVertex(1);

    // Act
    graph.addVertex(1);
    graph.addVertex(3);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize());
    EXPECT_EQ(graph.getOutNeighbors(1).GetSize(), 0);
    EXPECT_EQ(graph.getOutNeighbors(3).GetSize(), 0);
}

TEST(DiGraph, AddAssignedVertexAfterSize) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.addVertex(adjacencyList.GetSize() + 10);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10).GetSize(), 0);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 1), invalid_argument);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 11), out_of_range);
}

TEST(DiGraph, AddAssignedVertexExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    EXPECT_THROW(graph.addVertex(-1), out_of_range);
}

TEST(DiGraph, AddVertexWithNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
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

TEST(DiGraph, AddVertexWithAssignedNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act
    graph.addVertex(adjacencyList.GetSize() + 10, neighbors);
    graph.addVertex(1, neighbors);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() + 1);
    EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10).GetSize(), neighbors.GetSize());
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(adjacencyList.GetSize() + 10)[i], neighbors[i]);
    }
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 1), invalid_argument);
    EXPECT_THROW(graph.getOutNeighbors(adjacencyList.GetSize() + 11), out_of_range);
    EXPECT_EQ(graph.getOutNeighbors(1).GetSize(), 3); 
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(1)[i], neighbors[i]);
    }
}

TEST(DiGraph, AddVertexWithNeighborsExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act
    EXPECT_THROW(graph.addVertex(-1, neighbors), out_of_range);
}

TEST(DiGraph, AddEdge) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.addEdge(1, 3);
    graph.addEdge(1, 0);

    // Assert
    EXPECT_TRUE(graph.hasEdge(1, 3));
    EXPECT_TRUE(graph.hasEdge(1, 0));
}

TEST(DiGraph, AddEdgeExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_THROW(graph.addEdge(0, 4), out_of_range);
    EXPECT_THROW(graph.addEdge(4, 0), out_of_range);
    EXPECT_THROW(graph.addEdge(4, 4), out_of_range);
}

TEST(DiGraph, RemoveVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.removeVertex(0);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
    EXPECT_TRUE(graph.isTombstone(0));
}

TEST(DiGraph, RemoveLastVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.removeVertex(adjacencyList.GetSize() - 1);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), adjacencyList.GetSize() - 1);
    EXPECT_TRUE(graph.isTombstone(adjacencyList.GetSize() - 1));
}

TEST(DiGraph, RemoveVertexExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.removeVertex(1);

    // Assert
    EXPECT_THROW(graph.removeVertex(-1), out_of_range);
    EXPECT_THROW(graph.removeVertex(4), out_of_range);
}

TEST(DiGraph, RemoveEdge) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    graph.removeEdge(1, 0);
    graph.removeEdge(1, 0);

    // Assert
    EXPECT_FALSE(graph.hasEdge(1, 0));
}

TEST(DiGraph, RemoveEdgeExcepts) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_THROW(graph.removeEdge(0, 4), out_of_range);
    EXPECT_THROW(graph.removeEdge(4, 0), out_of_range);
    EXPECT_THROW(graph.removeEdge(4, 4), out_of_range);
}

TEST(DiGraph, HasVertex) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_TRUE(graph.hasVertex(0));
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
    EXPECT_TRUE(graph.hasVertex(3));
    EXPECT_FALSE(graph.hasVertex(4));
    EXPECT_FALSE(graph.hasVertex(-1));
    EXPECT_FALSE(graph.hasVertex(5));
}

TEST(DiGraph, HasEdge) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_TRUE(graph.hasEdge(0, 1));
    EXPECT_TRUE(graph.hasEdge(0, 2));
    EXPECT_TRUE(graph.hasEdge(0, 3));
    EXPECT_TRUE(graph.hasEdge(1, 0));
    EXPECT_FALSE(graph.hasEdge(1, 2));
    EXPECT_FALSE(graph.hasEdge(1, 3));
    EXPECT_TRUE(graph.hasEdge(2, 0));
    EXPECT_TRUE(graph.hasEdge(2, 1));
    EXPECT_TRUE(graph.hasEdge(2, 3));
    EXPECT_FALSE(graph.hasEdge(0, 0));
    EXPECT_FALSE(graph.hasEdge(1, 1));
    EXPECT_FALSE(graph.hasEdge(2, 2));
    EXPECT_FALSE(graph.hasEdge(3, 3));
    EXPECT_FALSE(graph.hasEdge(0, 4));
    EXPECT_FALSE(graph.hasEdge(4, 0));
    EXPECT_FALSE(graph.hasEdge(4, 4));
    EXPECT_FALSE(graph.hasEdge(-1, 0));
    EXPECT_FALSE(graph.hasEdge(0, -1));
    EXPECT_FALSE(graph.hasEdge(-1, -1));
    EXPECT_FALSE(graph.hasEdge(5, 0));
    EXPECT_FALSE(graph.hasEdge(0, 5));
    EXPECT_FALSE(graph.hasEdge(5, 5));
}

TEST(DiGraph, IsTombstone) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    graph.removeVertex(0);
    graph.removeVertex(2);

    // Act

    // Assert
    EXPECT_TRUE(graph.isTombstone(0));
    EXPECT_FALSE(graph.isTombstone(1));
    EXPECT_TRUE(graph.isTombstone(2));
    EXPECT_FALSE(graph.isTombstone(3));
    EXPECT_TRUE(graph.isTombstone(4));
    EXPECT_TRUE(graph.isTombstone(-1));
    EXPECT_TRUE(graph.isTombstone(5));
}

TEST(DiGraph, IsEmpty) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    DiGraph graphEmpty;

    // Act

    // Assert
    EXPECT_FALSE(graph.isEmpty());
    EXPECT_TRUE(graphEmpty.isEmpty());
}

TEST(DiGraph, boolOperators) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    DiGraph graphCopy(graph);
    DiGraph graphEmpty;

    // Act

    // Assert
    EXPECT_TRUE(graph == graphCopy);
    EXPECT_FALSE(graph != graphCopy);
    EXPECT_FALSE(graph == graphEmpty);
    EXPECT_TRUE(graph != graphEmpty);
}

TEST(DiGraph, GetVertexInDegree) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    EXPECT_EQ(graph.getInDegree(0), 2);
    EXPECT_EQ(graph.getInDegree(1), 3);
    EXPECT_EQ(graph.getInDegree(2), 1);
    EXPECT_EQ(graph.getInDegree(3), 2);
}

TEST(DiGraph, GetVertexOutDegree) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act

    // Assert
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutDegree(i), adjacencyList.Get(i).GetSize());
    }
}

TEST(DiGraph, GetVertexInNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);

    // Act

    // Assert
    EXPECT_EQ(graph.getInNeighbors(0).GetSize(), neighbors.GetSize());
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getInNeighbors(0)[i], neighbors[i]);
    }
}

TEST(DiGraph, GetVertexOutNeighbors) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);

    // Act

    // Assert
    EXPECT_EQ(graph.getOutNeighbors(0).GetSize(), neighbors.GetSize());
    for (int i = 0; i < neighbors.GetSize(); ++i) {
        EXPECT_EQ(graph.getOutNeighbors(0)[i], neighbors[i]);
    }
}

TEST(DiGraph, Transpose) {
    // Arrange
    auto adjacencyList = getAdjacencyList();
    DiGraph graph(adjacencyList);

    // Act
    auto graphTransposed = graph.transpose();

    // Assert
    EXPECT_EQ(graphTransposed.getVertexCount(), adjacencyList.GetSize());
    for (int i = 0; i < adjacencyList.GetSize(); ++i) {
        for (int j = 0; j < adjacencyList.Get(i).GetSize(); ++j) {
            if(graph.hasEdge(i, adjacencyList[i][j]))
                EXPECT_TRUE(graphTransposed.hasEdge(adjacencyList[i][j], i));
        }
    }
}