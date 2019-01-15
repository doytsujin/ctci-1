#ifndef CTCI_UTIL_GRAPH_H
#define CTCI_UTIL_GRAPH_H

#include <map>
#include <ostream>
#include <queue>
#include <vector>
#include <utility>

#include "util/node.h"

namespace ctci 
{ 
    namespace util 
    {
        using namespace std;

        enum SearchTypeEnum {DFS, BFS};

        template <typename T>
            class Graph {
                public:
                    std::map<T, std::shared_ptr<Node<T>>> nodes;

                    // Insert in a set of nodes into the graph (without children)
                    // Will return false if any of the nodes already exist
                    bool insert(std::vector<T> &nodes)
                    {
                        bool result = true;

                        for ( const auto &n: nodes ) {
                            result &= insert(n);
                        }
                        return result;
                    }

                    // Insert a node into the graph
                    // Will return false if node already exists
                    bool insert(const T &element)
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
                    bool insert(vector<pair<T, T>> &edges)
                    {
                        bool result = true;

                        for ( const auto &e: edges ) {
                            result &= insert(e);
                        }
                        return result;
                    }

                    // Insert in a directional edge, create nodes if needed
                    // Will return false if edge already exists
                    bool insert(const pair<T, T> &edge)
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

                    bool isConnected(const T &a, const T &b, 
                            SearchTypeEnum searchType=DFS, bool resetVisitState = true)
                    {
                        bool found = false;

                        // TODO: Fix marking nodes for visit, can't go through a 
                        // list and reset all of them, not scalable
                        if ( resetVisitState ) {
                            for (auto const &n: nodes) {
                                n.second->visitState = UNVISITED;
                            }
                        }

                        // Make sure a and b exist in the graph, quick return otherwise
                        auto nodeA = nodes.find(a);
                        auto nodeB = nodes.find(b);

                        if ( (nodeA != nodes.end()) && (nodeB != nodes.end()) ) {
                            switch (searchType) {
                                case (DFS):
                                    found = depthFirstSearch(nodeA->second, b);
                                    break;
                                case (BFS):
                                    found = breadthFirstSearch(nodeA->second, b);
                                    break;
                                default:
                                    break;
                            }
                        }

                        return found;
                    }

                private:
                    bool breadthFirstSearch(shared_ptr<Node<T>> node, const T &b)
                    {
                        bool found = false;
                        queue<shared_ptr<Node<T>>> nodes;

                        if ( (node != nullptr) && node->visitState == UNVISITED ) {
                            node->visitState = VISITED;

                            for (const auto &c: node->connections) {
                                if ( c.first == b) {
                                    found = true;
                                } else {
                                    nodes.push(c.second);
                                }
                                if ( found ) {
                                    break;
                                }
                            }

                            // OK, now go through and visit each of the children
                            while (!found && !nodes.empty()) {
                                auto nextNode = nodes.front();
                                nodes.pop();
                                found = breadthFirstSearch(nextNode, b);
                            }
                        }


                        return found;
                    }

                    bool depthFirstSearch(shared_ptr<Node<T>> node, const T &b)
                    {
                        bool found = false;

                        if ( (node != nullptr) && node->visitState == UNVISITED ) {
                            node->visitState = VISITED;

                            for (const auto &c: node->connections) {
                                if ( c.first == b ) {
                                    found = true;
                                } else {
                                    found = depthFirstSearch(c.second, b);
                                }
                                if ( found ) {
                                    break;
                                }
                            }
                        }

                        return found;
                    }

                    friend std::ostream& operator<<(std::ostream& os, const Graph &graph) {
                        for ( const auto &n: graph.nodes ) {
                            os << *(n.second) << std::endl;
                        }
                        return os;
                    }

            };
    }
}

#endif
