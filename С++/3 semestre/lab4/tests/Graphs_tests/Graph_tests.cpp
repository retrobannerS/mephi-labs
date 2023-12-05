#include "Graphs/Graph/Graph.hpp"
#include "gtest/gtest.h"

using namespace sem3;

ArraySequence<ListSequence<int>> fromVector(vector<vector<int>> v) {
    ArraySequence<ListSequence<int>> result;
    for (int i = 0; i < v.size(); ++i) {
        ListSequence<int> list;
        for (int j = 0; j < v[i].size(); ++j) {
            list.PushBack(v[i][j]);
        }
        result.PushBack(list);
    }
    return result;
}

TEST(Graph, DefaultConstructor) {
    // Arrange

    // Act
    Graph g;

    // Assert
    EXPECT_EQ(g.getVertexCount(), 0);
    EXPECT_EQ(g.getEdgeCount(), 0);
}

TEST(Graph, ConstructorFromAdjacencyList) {
    // Arrange
    vector<vector<int>> v = {{1, 2}, {0, 2}, {0, 1}};

    // Act
    Graph g(fromVector(v));

    // Assert
    EXPECT_EQ(g.getVertexCount(), 3);
    EXPECT_EQ(g.getEdgeCount(), 3);
}

TEST(Graph, Graph_ConstructorFromAdjacencyListExcept) {
    // Arrange
    vector<vector<int>> v = {{1, 2}, {0, 2}, {0, 1, 3}};
    ArraySequence<ListSequence<int>> adjList = fromVector(v);

    // Act

    // Assert
    EXPECT_THROW(Graph g(adjList), invalid_argument);
}

TEST(Graph, ConstructorFromAdjacencyMatrix) {
    // Arrange
    vector<vector<int>> v = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
    ArraySequence<ArraySequence<int>> adjMatrix;
    for (int i = 0; i < v.size(); ++i) {
        ArraySequence<int> list;
        for (int j = 0; j < v[i].size(); ++j) {
            list.PushBack(v[i][j]);
        }
        adjMatrix.PushBack(list);
    }

    // Act
    Graph g(adjMatrix);

    // Assert
    EXPECT_EQ(g.getVertexCount(), 3);
    EXPECT_EQ(g.getEdgeCount(), 3);
}

TEST(Graph, Graph_ConstructorFromAdjacencyMatrixExcept) {
    // Arrange
    vector<vector<int>> v = {{0, 1, 1}, {1, 0, 1}, {1, 0, 0}};
    ArraySequence<ArraySequence<int>> adjMatrix;
    for (int i = 0; i < v.size(); ++i) {
        ArraySequence<int> list;
        for (int j = 0; j < v[i].size(); ++j) {
            list.PushBack(v[i][j]);
        }
        adjMatrix.PushBack(list);
    }

    // Act

    // Assert
    EXPECT_THROW(Graph g(adjMatrix), invalid_argument);
}

TEST(Graph, ConstructorFromEdges) {
    // Arrange
    vector<pair<int, int>> v = {{0, 1}, {0, 2}, {1, 2}};
    ArraySequence<pair<int, int>> edges;
    for (int i = 0; i < v.size(); ++i) {
        edges.PushBack(v[i]);
    }

    // Act
    Graph g(edges);

    // Assert
    EXPECT_EQ(g.getVertexCount(), 3);
    EXPECT_EQ(g.getEdgeCount(), 3);
}

TEST(Graph, ConstructorFromEdges2) {
    // Arrange
    ArraySequence<pair<int, int>> edges;
    edges.PushBack(make_pair(0, 4));

    // Act
    Graph graph(edges);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 2);
    EXPECT_EQ(graph.getEdgeCount(), 1);
    EXPECT_TRUE(graph.hasEdge(0, 4));
    for (int i = 1; i < 4; ++i) {
        EXPECT_TRUE(graph.isTombstone(1));
    }
}

TEST(Graph, CopyConstructor) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g1(fromVector(v));

    // Act
    Graph g2(g1);

    // Assert
    EXPECT_EQ(g2.getVertexCount(), 5);
    EXPECT_EQ(g2.getEdgeCount(), 5);
}

TEST(Graph, MoveConstructor) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g1(fromVector(v));

    // Act
    Graph g2(std::move(g1));

    // Assert
    EXPECT_EQ(g2.getVertexCount(), 5);
    EXPECT_EQ(g2.getEdgeCount(), 5);
    EXPECT_EQ(g1.getVertexCount(), 0);
    EXPECT_EQ(g1.getEdgeCount(), 0);
}

TEST(Graph, CopyAssignment) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g1(fromVector(v));
    Graph g2;

    // Act
    g2 = g1;

    // Assert
    EXPECT_EQ(g2.getVertexCount(), 5);
    EXPECT_EQ(g2.getEdgeCount(), 5);
}

TEST(Graph, MoveAssignment) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g1(fromVector(v));
    Graph g2;

    // Act
    g2 = std::move(g1);

    // Assert
    EXPECT_EQ(g2.getVertexCount(), 5);
    EXPECT_EQ(g2.getEdgeCount(), 5);
    EXPECT_EQ(g1.getVertexCount(), 0);
    EXPECT_EQ(g1.getEdgeCount(), 0);
}

TEST(Graph, GetVertexCount) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act

    // Assert
    EXPECT_EQ(g.getVertexCount(), 5);
}

TEST(Graph, GetVertexCountAfterAdd) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act
    g.addVertex(7);

    // Assert
    EXPECT_EQ(g.getVertexCount(), 6);
}

TEST(Graph, GetVertexCountAfterRemove) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act
    g.removeVertex(0);

    // Assert
    EXPECT_EQ(g.getVertexCount(), 4);
}

TEST(Graph, GetEdgeCount) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act

    // Assert
    EXPECT_EQ(g.getEdgeCount(), 5);
}

TEST(Graph, GetEdgeCountAfterAdd) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act
    g.addEdge(2, 3);

    // Assert
    EXPECT_EQ(g.getEdgeCount(), 6);
}

TEST(Graph, GetEdgeCountAfterRemove) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph g(fromVector(v));

    // Act
    g.removeEdge(0, 1);

    // Assert
    EXPECT_EQ(g.getEdgeCount(), 4);
}

TEST(Graph, GetVertexes) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    ArraySequence<int> vertexes = g.getVertexes();

    // Assert
    EXPECT_EQ(vertexes.GetSize(), 6);
    EXPECT_EQ(vertexes.Get(0), 0);
    EXPECT_EQ(vertexes.Get(1), 1);
    EXPECT_EQ(vertexes.Get(2), 2);
    EXPECT_EQ(vertexes.Get(3), 3);
    EXPECT_EQ(vertexes.Get(4), 4);
    EXPECT_EQ(vertexes.Get(5), 5);
}

TEST(Graph, GetEdges) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    ArraySequence<pair<int, int>> edges = g.getEdges();

    // Assert
    EXPECT_EQ(edges.GetSize(), 6);
    EXPECT_EQ(edges.Get(0).first, 0);
    EXPECT_EQ(edges.Get(0).second, 1);
    EXPECT_EQ(edges.Get(1).first, 0);
    EXPECT_EQ(edges.Get(1).second, 2);
    EXPECT_EQ(edges.Get(2).first, 0);
    EXPECT_EQ(edges.Get(2).second, 3);
    EXPECT_EQ(edges.Get(3).first, 0);
    EXPECT_EQ(edges.Get(3).second, 4);
    EXPECT_EQ(edges.Get(4).first, 1);
    EXPECT_EQ(edges.Get(4).second, 2);
    EXPECT_EQ(edges.Get(5).first, 1);
    EXPECT_EQ(edges.Get(5).second, 5);
}

TEST(Graph, GetEdgesAfterAddEdge) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    g.addEdge(2, 3);
    ArraySequence<pair<int, int>> edges = g.getEdges();

    // Assert
    EXPECT_EQ(edges.GetSize(), 7);
    EXPECT_EQ(edges.Get(0).first, 0);
    EXPECT_EQ(edges.Get(0).second, 1);
    EXPECT_EQ(edges.Get(1).first, 0);
    EXPECT_EQ(edges.Get(1).second, 2);
    EXPECT_EQ(edges.Get(2).first, 0);
    EXPECT_EQ(edges.Get(2).second, 3);
    EXPECT_EQ(edges.Get(3).first, 0);
    EXPECT_EQ(edges.Get(3).second, 4);
    EXPECT_EQ(edges.Get(4).first, 1);
    EXPECT_EQ(edges.Get(4).second, 2);
    EXPECT_EQ(edges.Get(5).first, 1);
    EXPECT_EQ(edges.Get(5).second, 5);
    EXPECT_EQ(edges.Get(6).first, 2);
    EXPECT_EQ(edges.Get(6).second, 3);
}

TEST(Graph, GetTombstonesEmpty) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    ArraySequence<int> tombstones = g.getTombstones();

    // Assert
    EXPECT_EQ(tombstones.GetSize(), 0);
}

TEST(Graph, GetTombstonesAfterRemoveVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    g.removeVertex(0);
    ArraySequence<int> tombstones = g.getTombstones();

    // Assert
    EXPECT_EQ(tombstones.GetSize(), 1);
    EXPECT_EQ(tombstones.Get(0), 0);
}

TEST(Graph, GetTombstonesAfterAddVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    g.addVertex(10);
    ArraySequence<int> tombstones = g.getTombstones();

    // Assert
    EXPECT_EQ(tombstones.GetSize(), 4);
    EXPECT_EQ(tombstones.Get(0), 6);
    EXPECT_EQ(tombstones.Get(1), 7);
}

TEST(Graph, AddVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph g(fromVector(v));

    // Act
    g.addVertex();

    // Assert
    EXPECT_EQ(g.getVertexCount(), 7);
    EXPECT_EQ(g.getNeighbors(6).GetSize(), 0);
}

TEST(Graph, AddAssignedVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph graph(fromVector(v));
    graph.removeVertex(1);

    // Act
    graph.addVertex(1);
    graph.addVertex(3);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 6);
    EXPECT_EQ(graph.getNeighbors(1).GetSize(), 0);
    EXPECT_EQ(graph.getNeighbors(3).GetSize(), 1);
}

TEST(Graph, AddAssignedVertexAfterSize) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act
    graph.addVertex(v.size() + 10);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), v.size() + 1);
    EXPECT_EQ(graph.getNeighbors(v.size() + 10).GetSize(), 0);
    EXPECT_THROW(graph.getNeighbors(v.size() + 1), invalid_argument);
    EXPECT_THROW(graph.getNeighbors(v.size() + 11), out_of_range);
}

TEST(Graph, AddAssignedVertexExcepts) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_THROW(graph.addVertex(-1), out_of_range);
}

TEST(Graph, AddVertexWithNeighbors) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);
    Graph g(fromVector(v));

    // Act
    g.addVertex(neighbors);

    // Assert
    EXPECT_EQ(g.getVertexCount(), 7);
    EXPECT_EQ(g.getNeighbors(6).GetSize(), 3);
    EXPECT_EQ(g.getNeighbors(6).Get(0), 1);
    EXPECT_EQ(g.getNeighbors(6).Get(1), 2);
    EXPECT_EQ(g.getNeighbors(6).Get(2), 3);
}

TEST(Graph, AddAssignedVertexWithNeighbors) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);
    Graph graph(fromVector(v));
    graph.removeVertex(1);

    // Act
    graph.addVertex(1, neighbors);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 6);
    EXPECT_EQ(graph.getNeighbors(1).GetSize(), 3);
    EXPECT_EQ(graph.getNeighbors(1).Get(0), 1);
    EXPECT_EQ(graph.getNeighbors(1).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(1).Get(2), 3);
    EXPECT_TRUE(graph.getNeighbors(1).TryFind(1).HasValue());
    EXPECT_TRUE(graph.getNeighbors(2).TryFind(1).HasValue());
    EXPECT_TRUE(graph.getNeighbors(3).TryFind(1).HasValue());
}

TEST(Graph, AddAssignedVertexWithNeighborsAfterSize) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};
    ListSequence<int> neighbors;
    neighbors.PushBack(1);
    neighbors.PushBack(2);
    neighbors.PushBack(3);
    Graph graph(fromVector(v));

    // Act
    graph.addVertex(v.size() + 10, neighbors);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), v.size() + 1);
    EXPECT_EQ(graph.getNeighbors(v.size() + 10).GetSize(), 3);
    EXPECT_EQ(graph.getNeighbors(v.size() + 10).Get(0), 1);
    EXPECT_EQ(graph.getNeighbors(v.size() + 10).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(v.size() + 10).Get(2), 3);
    EXPECT_THROW(graph.getNeighbors(v.size() + 1), invalid_argument);
    EXPECT_THROW(graph.getNeighbors(v.size() + 11), out_of_range);
}

TEST(Graph, AddAssignedVertexWithNeighborsExcepts) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1}, {0}, {0}, {1}};

    // Act

    // Assert
    EXPECT_THROW(Graph(fromVector(v)).addVertex(-1, ListSequence<int>()), out_of_range);
}

TEST(Graph, AddEdge) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph graph(fromVector(v));

    // Act
    graph.addEdge(1, 3);
    graph.addEdge(1, 0);

    // Assert
    EXPECT_EQ(graph.getNeighbors(1).GetSize(), 3);
    EXPECT_EQ(graph.getNeighbors(1).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(1).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(1).Get(2), 3);
    EXPECT_EQ(graph.getNeighbors(3).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(3).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(3).Get(1), 1);
    EXPECT_EQ(graph.getNeighbors(0).GetSize(), 4);
    EXPECT_EQ(graph.getNeighbors(0).Get(0), 1);
    EXPECT_EQ(graph.getNeighbors(0).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(0).Get(2), 3);
    EXPECT_EQ(graph.getNeighbors(0).Get(3), 4);
}

TEST(Graph, AddEdgeExcepts) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    Graph graph(fromVector(v));
    // Act
    graph.removeVertex(1);
    // Assert
    EXPECT_THROW(graph.addEdge(-1, 0), out_of_range);
    EXPECT_THROW(graph.addEdge(0, -1), out_of_range);
    EXPECT_THROW(graph.addEdge(0, 5), out_of_range);
    EXPECT_THROW(graph.addEdge(5, 0), out_of_range);
    EXPECT_THROW(graph.addEdge(5, 5), out_of_range);
    EXPECT_THROW(graph.addEdge(1, 0), invalid_argument);
    EXPECT_THROW(graph.addEdge(0, 1), invalid_argument);
    EXPECT_THROW(graph.addEdge(1, 1), invalid_argument);
}

TEST(Graph, RemoveVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1, 3}, {0, 2}, {0}};
    Graph graph(fromVector(v));

    // Act
    graph.removeVertex(1);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), 4);
    EXPECT_EQ(graph.getNeighbors(0).GetSize(), 3);
    EXPECT_EQ(graph.getNeighbors(0).Get(0), 2);
    EXPECT_EQ(graph.getNeighbors(0).Get(1), 3);
    EXPECT_EQ(graph.getNeighbors(0).Get(2), 4);
    EXPECT_EQ(graph.getNeighbors(2).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(2).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(2).Get(1), 3);
    EXPECT_EQ(graph.getNeighbors(3).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(3).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(3).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(4).GetSize(), 1);
    EXPECT_EQ(graph.getNeighbors(4).Get(0), 0);
}

TEST(Graph, RemoveLastVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1, 3}, {0, 2}, {0}};
    Graph graph(fromVector(v));

    // Act
    graph.removeVertex(v.size() - 1);

    // Assert
    EXPECT_EQ(graph.getVertexCount(), v.size() - 1);
    EXPECT_EQ(graph.getNeighbors(0).GetSize(), 3);
    EXPECT_EQ(graph.getNeighbors(0).Get(0), 1);
    EXPECT_EQ(graph.getNeighbors(0).Get(1), 2);
    EXPECT_EQ(graph.getNeighbors(0).Get(2), 3);
}

TEST(Graph, RemoveVertexExcepts) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2}, {0, 1, 3}, {0, 2}, {0}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_THROW(graph.removeVertex(-1), out_of_range);
    EXPECT_THROW(graph.removeVertex(5), out_of_range);
}

TEST(Graph, RemoveEdge) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act
    graph.removeEdge(1, 2);

    // Assert
    EXPECT_EQ(graph.getEdgeCount(), 6);
    EXPECT_EQ(graph.getNeighbors(1).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(1).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(1).Get(1), 5);
    EXPECT_EQ(graph.getNeighbors(2).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(2).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(2).Get(1), 3);
    EXPECT_EQ(graph.getNeighbors(3).GetSize(), 2);
    EXPECT_EQ(graph.getNeighbors(3).Get(0), 0);
    EXPECT_EQ(graph.getNeighbors(3).Get(1), 2);
}

TEST(Graph, RemoveEdgeExcepts) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_THROW(graph.removeEdge(-1, 0), out_of_range);
    EXPECT_THROW(graph.removeEdge(0, -1), out_of_range);
    EXPECT_THROW(graph.removeEdge(0, 6), out_of_range);
    EXPECT_THROW(graph.removeEdge(6, 0), out_of_range);
    EXPECT_THROW(graph.removeEdge(6, 6), out_of_range);
}

TEST(Graph, HasVertex) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_TRUE(graph.hasVertex(0));
    EXPECT_TRUE(graph.hasVertex(1));
    EXPECT_TRUE(graph.hasVertex(2));
    EXPECT_TRUE(graph.hasVertex(3));
    EXPECT_TRUE(graph.hasVertex(4));
    EXPECT_TRUE(graph.hasVertex(5));
    EXPECT_FALSE(graph.hasVertex(-1));
    EXPECT_FALSE(graph.hasVertex(6));
}

TEST(Graph, HasEdge) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_TRUE(graph.hasEdge(0, 1));
    EXPECT_TRUE(graph.hasEdge(0, 2));
    EXPECT_TRUE(graph.hasEdge(0, 3));
    EXPECT_TRUE(graph.hasEdge(0, 4));
    EXPECT_TRUE(graph.hasEdge(1, 0));
    EXPECT_TRUE(graph.hasEdge(1, 2));
    EXPECT_TRUE(graph.hasEdge(1, 5));
    EXPECT_TRUE(graph.hasEdge(2, 0));
    EXPECT_TRUE(graph.hasEdge(2, 1));
    EXPECT_TRUE(graph.hasEdge(2, 3));
    EXPECT_TRUE(graph.hasEdge(3, 0));
    EXPECT_TRUE(graph.hasEdge(3, 2));
    EXPECT_TRUE(graph.hasEdge(4, 0));
    EXPECT_TRUE(graph.hasEdge(5, 1));
    EXPECT_FALSE(graph.hasEdge(-1, 0));
    EXPECT_FALSE(graph.hasEdge(0, -1));
    EXPECT_FALSE(graph.hasEdge(0, 6));
    EXPECT_FALSE(graph.hasEdge(6, 0));
    EXPECT_FALSE(graph.hasEdge(6, 6));
}

TEST(Graph, isTombstone) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act
    graph.removeVertex(2);
    // Assert
    EXPECT_FALSE(graph.isTombstone(0));
    EXPECT_FALSE(graph.isTombstone(1));
    EXPECT_TRUE(graph.isTombstone(2));
    EXPECT_FALSE(graph.isTombstone(3));
    EXPECT_FALSE(graph.isTombstone(4));
    EXPECT_FALSE(graph.isTombstone(5));
    EXPECT_TRUE(graph.isTombstone(6));
    EXPECT_TRUE(graph.isTombstone(7));
    EXPECT_TRUE(graph.isTombstone(8));
    EXPECT_TRUE(graph.isTombstone(9));
    EXPECT_TRUE(graph.isTombstone(10));
    EXPECT_TRUE(graph.isTombstone(11));
}

TEST(Graph, isEmpty) {
    // Arrange
    vector<vector<int>> v = {{1}, {0}};
    Graph graph(fromVector(v));
    Graph graph2;

    // Act

    // Assert
    EXPECT_FALSE(graph.isEmpty());
    graph.removeVertex(0);
    EXPECT_FALSE(graph.isEmpty());
    graph.removeVertex(1);
    EXPECT_TRUE(graph.isEmpty());
    EXPECT_TRUE(graph2.isEmpty());
}

TEST(Graph, BoolOperators) {
    // Arrange
    vector<vector<int>> v = {{1}, {0}};
    Graph graph(fromVector(v));
    Graph graphCopy(graph);
    Graph graphEmpty;

    // Act

    // Assert
    EXPECT_TRUE(graph == graphCopy);
    EXPECT_FALSE(graph != graphCopy);
    EXPECT_FALSE(graph == graphEmpty);
    EXPECT_TRUE(graph != graphEmpty);
}

TEST(Graph, GetVertexDegree) {
    // Arrange
    vector<vector<int>> v = {{1, 2, 3, 4}, {0, 2, 5}, {0, 1, 3}, {0, 2}, {0}, {1}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_EQ(graph.getDegree(0), 4);
    EXPECT_EQ(graph.getDegree(1), 3);
    EXPECT_EQ(graph.getDegree(2), 3);
    EXPECT_EQ(graph.getDegree(3), 2);
    EXPECT_EQ(graph.getDegree(4), 1);
    EXPECT_EQ(graph.getDegree(5), 1);
}

TEST(Graph, GetVertexDegreeExcepts) {
    // Arrange
    vector<vector<int>> v = {{1}, {0}};
    Graph graph(fromVector(v));

    // Act

    // Assert
    EXPECT_THROW(graph.getDegree(-1), out_of_range);
    EXPECT_THROW(graph.getDegree(2), out_of_range);
}