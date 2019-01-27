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

        enum SearchTypeEnum {
            DEPTH_FIRST_SEARCH, 
            BREADTH_FIRST_SEARCH
        };

        template <typename T>
            class Graph {
                public:
                    Graph(NodeTypeEnum nodeType = UNDIRECTED) : nodeType(nodeType) {};

                    std::vector<shared_ptr<Node<T>>> visited;
                    std::map<T, std::shared_ptr<Node<T>>> nodes;
                    const NodeTypeEnum nodeType;

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
                            shared_ptr<Node<T>> node (new Node<T>(element, nodeType));
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
                            shared_ptr<Node<T>> temp (new Node<T>(edge.first, nodeType));
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
                            shared_ptr<Node<T>> temp (new Node<T>(edge.second, nodeType));
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
                            SearchTypeEnum searchType=DEPTH_FIRST_SEARCH, 
                            bool resetVisitState = true)
                    {
                        bool found = false;

                        // Only reset visited nodes
                        if ( resetVisitState ) {
                            for (auto const &n: visited) {
                                n->visitState = UNVISITED;
                            }
                            visited.clear();
                        }

                        // Make sure a and b exist in the graph, quick return otherwise
                        auto nodeA = nodes.find(a);
                        auto nodeB = nodes.find(b);

                        if ( (nodeA != nodes.end()) && (nodeB != nodes.end()) ) {
                            switch (searchType) {
                                case (DEPTH_FIRST_SEARCH):
                                    found = depthFirstSearch(nodeA->second, b);
                                    break;
                                case (BREADTH_FIRST_SEARCH):
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
                            visited.push_back(node);

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
                            visited.push_back(node);

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
                        string dotGraph = "unknown";
                        switch (graph.nodeType) {
                            case DIRECTED: 
                                dotGraph = "digraph"; 
                                break;
                            case UNDIRECTED: 
                            case BINARY_TREE: 
                            default:
                                dotGraph = "graph"; 
                                break;
                        }
                        os << dotGraph << " {" << endl;
                        for ( const auto &n: graph.nodes ) {
                            os << "  " << *(n.second) << std::endl;
                        }
                        os << "}";
                        return os;
                    }

            };
    }
}

#endif
