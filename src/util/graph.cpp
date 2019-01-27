// Graph object
// 

#include <vector>
#include <gtest/gtest.h>

#include "args.h"
#include "macros.h"
#include "util/graph.h"

using namespace ctci::util;
using namespace ctci;
using namespace std;

TEST(Graph, Initialize)
{
    Graph<int> graph;
    ASSERT_EQ(graph.nodes.size(), 0ul);
}

TEST(Graph, Templating)
{
    Graph<int> iGraph;
    int i = 5;
    iGraph.insert(i);
    ASSERT_EQ(iGraph.nodes[i]->value, i);

    Graph<string> sGraph;
    string s = "string";
    sGraph.insert(s);
    ASSERT_EQ(sGraph.nodes[s]->value, s);

    Graph<double> dGraph;
    double d = 3.14;
    dGraph.insert(d);
    ASSERT_EQ(dGraph.nodes[d]->value, d);
}

TEST(Graph, Insert)
{
    Graph<string> graph;

    string nodeOne = "one";
    string nodeTwo = "two";
    string nodeThree = "three";
    string nodeSolo = "solo";

    vector<string> solo = {nodeSolo};
    graph.insert(solo);

    shared_ptr<Node<string>> node1(new Node<string>(nodeOne));
    shared_ptr<Node<string>> node2(new Node<string>(nodeTwo));
    shared_ptr<Node<string>> node3(new Node<string>(nodeThree));

    vector<pair<string, shared_ptr<Node<string>>>> adjacencyList = {{nodeTwo, node2}, {nodeThree, node3}};
    node1->insert(adjacencyList);

    ASSERT_EQ(node1->value, nodeOne);
    ASSERT_EQ(node2->value, nodeTwo);
    ASSERT_EQ(node3->value, nodeThree);

    // Check duplicates are not successful
    ASSERT_EQ(node1->insert({nodeTwo, node2}), false);

    auto c2 = node1->connections.find(nodeTwo);
    if ( c2 == node1->connections.end() ) {
        ASSERT_EQ(true, false);
    } else {
        ASSERT_EQ(c2->first, nodeTwo);
    }

    auto c3 = node1->connections.find(nodeThree);
    if ( c3 == node1->connections.end() ) {
        ASSERT_EQ(true, false);
    } else {
        ASSERT_EQ(c3->first, nodeThree);
    }

    // Finally, verify solo is in fact solo
    ASSERT_EQ(graph.nodes[nodeSolo]->connections.size(), 0ul);
}

TEST(Graph, Cout)
{
    Graph<string> graph(UNDIRECTED);
    Graph<string> digraph(DIRECTED);

    vector<string> solo = {"solo"};
    graph.insert(solo);
    digraph.insert(solo);

    vector<pair<string, string>> edges = {
        {"a", "b"},
        {"a", "c"},
        {"b", "c"},
        {"c", "b"},
        {"b", "d"},
        {"d", "e"}
    };

    graph.insert(edges);
    digraph.insert(edges);

    stringstream dOutput;
    stringstream dgOutput;

    dOutput << graph;
    dgOutput << digraph;

    string dExpected = 
        "graph {\n" \
        "  a -- {b c}\n" \
        "  b -- {c d}\n" \
        "  c -- {b}\n" \
        "  d -- {e}\n" \
        "  e -- {}\n" \
        "  solo -- {}\n" \
        "}";

    string dgExpected = 
        "digraph {\n" \
        "  a -> {b c}\n" \
        "  b -> {c d}\n" \
        "  c -> {b}\n" \
        "  d -> {e}\n" \
        "  e -> {}\n" \
        "  solo -> {}\n" \
        "}";

    ASSERT_EQ(dOutput.str(), dExpected);
    ASSERT_EQ(dgOutput.str(), dgExpected);
}
