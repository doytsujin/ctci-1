// Node object
// 

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "args.h"
#include "macros.h"
#include "util/node.h"

using namespace std;

using namespace ctci;
using namespace ctci::util;

TEST(Node, Initialize)
{
    int value = 5;
    Node<int> node(value);

    ASSERT_EQ(node.value, value);
    ASSERT_EQ(node.visitState, UNVISITED);
}

TEST(Node, Cout)
{
    // Simple test
    string test = "test";
    const NodeTypeEnum nodeType = DIRECTED;
    Node<string> node(test, nodeType);
    stringstream testOutput;
    testOutput << node;
    string testExpected = "test -> {}";
    ASSERT_EQ(testOutput.str(), testExpected);

    // Complicated test

    string nodeOne = "a";
    string nodeTwo = "b";
    string nodeThree = "c";

    shared_ptr<Node<string>> node1(new Node<string>(nodeOne, nodeType));
    shared_ptr<Node<string>> node2(new Node<string>(nodeTwo, nodeType));
    shared_ptr<Node<string>> node3(new Node<string>(nodeThree, nodeType));

    vector<pair<string, shared_ptr<Node<string>>>> adjacencyList = {{nodeTwo, node2}, {nodeThree, node3}};
    node1->insert(adjacencyList);

    string expectedOne = "a -> {b c}";
    stringstream outputOne;

    string expectedTwo = "b -> {}";
    stringstream outputTwo;

    string expectedThree = "c -> {}";
    stringstream outputThree;

    outputOne << *node1;
    outputTwo << *node2;
    outputThree << *node3;

    ASSERT_EQ(outputOne.str(), expectedOne);
    ASSERT_EQ(outputTwo.str(), expectedTwo);
    ASSERT_EQ(outputThree.str(), expectedThree);

    // Make sure output was not affected
    outputOne.str("");
    outputTwo.str("");
    outputThree.str("");
    outputOne << *node1;
    outputTwo << *node2;
    outputThree << *node3;

    ASSERT_EQ(outputOne.str(), expectedOne);
    ASSERT_EQ(outputTwo.str(), expectedTwo);
    ASSERT_EQ(outputThree.str(), expectedThree);
}

TEST(Node, Insert)
{
    string nodeOne = "one";
    string nodeTwo = "two";
    string nodeThree = "three";

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
}

TEST(Node, Templating)
{
    int intValue = 5;
    Node<int> nodeInt(intValue);
    ASSERT_EQ(nodeInt.value, intValue);

    string stringValue = "abc";
    Node<string> nodeString(stringValue);
    ASSERT_EQ(nodeString.value, stringValue);

    double doubleValue = 3.14;
    Node<double> nodeDouble(doubleValue);
    ASSERT_EQ(nodeDouble.value, doubleValue);
}
