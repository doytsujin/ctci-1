// 4.1  Route Between Nodes: Given a directed graph, design an algorithm to find out 
// whether there is a route between two nodes
// 

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "util/graph.h"

#include "args.h"
#include "macros.h"

using namespace ctci::util;
using namespace ctci;
using namespace std;

TEST(RouteBetweenNodes, BFS)
{
    Graph<int> graph;

    vector<pair<int, int>> edges = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5}
    };
    graph.insert(edges);

    // Will pass!
    ASSERT_EQ(graph.isConnected(1, 5, BFS), true);

    // Not a bi-directional graph, so should fail
    ASSERT_EQ(graph.isConnected(5, 1, BFS), false);

    // Checking for route to node that doesn't exist
    ASSERT_EQ(graph.isConnected(6, 1, BFS), false);

    // Check for route to self (should fail)
    ASSERT_EQ(graph.isConnected(2, 2, BFS), false);

    // Check for route between two nodes that don't exist (false)
    ASSERT_EQ(graph.isConnected(7, 7, BFS), false);
}

TEST(RouteBetweenNodes, DFS)
{
    Graph<int> graph;

    vector<pair<int, int>> edges = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5}
    };
    graph.insert(edges);

    // Will pass!
    ASSERT_EQ(graph.isConnected(1, 5, DFS), true);

    // Not a bi-directional graph, so should fail
    ASSERT_EQ(graph.isConnected(5, 1, DFS), false);

    // Checking for route to node that doesn't exist
    ASSERT_EQ(graph.isConnected(6, 1, DFS), false);

    // Check for route to self (should fail)
    ASSERT_EQ(graph.isConnected(2, 2, DFS), false);

    // Check for route between two nodes that don't exist (false)
    ASSERT_EQ(graph.isConnected(7, 7, DFS), false);
}

TEST(RouteBetweenNodes, CyclicDFS)
{
    Graph<int> graph;

    vector<pair<int, int>> edges = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 1},
        {3, 5}
    };
    graph.insert(edges);

    const SearchTypeEnum searchType = DFS;
    ASSERT_EQ(graph.isConnected(1, 3, searchType), true);

    // should fail if we don't reset
    ASSERT_EQ(graph.isConnected(1, 3, searchType, false), false);

    // should pass again
    ASSERT_EQ(graph.isConnected(1, 3, searchType), true);

    ASSERT_EQ(graph.isConnected(3, 1, searchType), true);

    // Don't reset the nodes, should fail this time
    ASSERT_EQ(graph.isConnected(3, 1, searchType, false), false);

    // Rest of these are normal sanity checks
    ASSERT_EQ(graph.isConnected(2, 4, searchType), true);
    ASSERT_EQ(graph.isConnected(3, 5, searchType), true);
    ASSERT_EQ(graph.isConnected(5, 1, searchType), false);
    ASSERT_EQ(graph.isConnected(3, 3, searchType), true);
    ASSERT_EQ(graph.isConnected(4, 5, searchType), true);
}

TEST(RouteBetweenNodes, CyclicBFS)
{
    Graph<int> graph;

    vector<pair<int, int>> edges = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 1},
        {3, 5}
    };
    graph.insert(edges);

    const SearchTypeEnum searchType = BFS;
    ASSERT_EQ(graph.isConnected(1, 3, searchType), true);
    ASSERT_EQ(graph.isConnected(3, 1, searchType), true);
    ASSERT_EQ(graph.isConnected(2, 4, searchType), true);
    ASSERT_EQ(graph.isConnected(3, 5, searchType), true);
    ASSERT_EQ(graph.isConnected(5, 1, searchType), false);
    ASSERT_EQ(graph.isConnected(3, 3, searchType), true);
    ASSERT_EQ(graph.isConnected(4, 5, searchType), true);
}
