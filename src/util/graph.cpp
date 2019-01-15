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

// Insert in a set of nodes into the graph (without children)
// Will return false if any of the nodes already exist
template <typename T>
bool Graph<T>::insert(std::vector<T> &nodes)
{
    bool result = true;

    for ( const auto &n: nodes ) {
        result &= insert(n);
    }
    return result;
}

// Insert a node into the graph
// Will return false if node already exists
template <typename T>
bool Graph<T>::insert(const T &element)
{
    bool result = false;

    // Search for the first node.
    // Create it if it doesn't exist.
    auto found = nodes.find(element);
    if (found == nodes.end()) {
        shared_ptr<Node<T>> node (new Node<T>(element));
        nodes.insert({element, node});
    }

    return result;
}

// Insert in a set of directional edges, create nodes if needed
// Will return false if edge already exists
template <typename T>
bool Graph<T>::insert(vector<pair<T, T>> &edges)
{
    bool result = true;

    for ( const auto &e: edges ) {
        result &= insert(e);
    }
    return result;
}

// Insert in a directional edge, create nodes if needed
// Will return false if edge already exists
template <typename T>
bool Graph<T>::insert(const pair<T, T> &edge)
{
    bool result = true;

    // Search for the first node.
    // Create it if it doesn't exist.
    shared_ptr<Node<T>> parent;
    auto searchParent = nodes.find(edge.first);
    if (searchParent != nodes.end()) {
        parent = searchParent->second;
    } else {
        shared_ptr<Node<T>> temp (new Node<T>(edge.first));
        parent = temp;
        nodes.insert({edge.first, parent});
    }

    // Search for the second node.
    // Create it if it doesn't exist.
    shared_ptr<Node<T>> child;
    auto searchChild = nodes.find(edge.second);
    if (searchChild != nodes.end()) {
        child = searchChild->second;
    } else {
        shared_ptr<Node<T>> temp (new Node<T>(edge.second));
        child = temp;
        nodes.insert({edge.second, child});
    }

    // Finally, add the child to the parent's connections
    // Do nothing if it already exists, except print that it
    // already exists
    result &= parent->insert({edge.second, child});

    return result;
}

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
    Graph<string> graph;

    vector<string> solo = {"solo"};
    graph.insert(solo);

    vector<pair<string, string>> edges = {
        {"a", "b"},
        {"a", "c"},
        {"b", "c"},
        {"c", "b"},
        {"b", "d"},
        {"d", "e"}
    };

    graph.insert(edges);

    stringstream output;
    output << graph;
    string expected = 
        "a -> b, c\n" \
        "b -> c, d\n" \
        "c -> b\n" \
        "d -> e\n" \
        "e ->\n" \
        "solo ->\n";

    ASSERT_EQ(output.str(), expected);
}
