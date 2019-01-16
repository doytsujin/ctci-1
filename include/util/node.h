#ifndef CTCI_UTIL_NODE_H
#define CTCI_UTIL_NODE_H

#include <ostream>
#include <vector>
#include <utility>

namespace ctci 
{ 
    namespace util 
    {
        using namespace std;

        // Used for searches
        enum NodeTypeEnum {
            UNDIRECTED, 
            DIRECTED, 
            BINARY_TREE
        };
        enum NodeVisitStateEnum {
            UNVISITED, 
            VISITED
        };

        template <typename T>
            class Node 
            {
                public:
                    Node(T t, const NodeTypeEnum &nodeType = UNDIRECTED) 
                        : value(t), nodeType(nodeType), visitState(UNVISITED) {};

                    bool insert(vector<pair<T, shared_ptr<Node<T>>>> &elements)
                    {
                        bool result = true;
                        for (const auto &e: elements) {
                            result &= insert(e);
                        }
                        return result;
                    }

                    bool insert(const pair<T, shared_ptr<Node<T>>> &element)
                    {
                        bool result = true;

                        // Add the connection if it does not already exist
                        shared_ptr<Node<T>> connection;
                        auto searchConnection = connections.find(element.first);
                        if (searchConnection == connections.end()) {
                            connections.emplace(element);
                        } else {
                            result = false;
                        }

                        return result;
                    }

                    std::string visitStateToString()
                    {
                        switch (visitState) {
                            case UNVISITED: return "Unvisited";
                            case VISITED: return "Visited";
                            default: return "Error";
                        }
                    }

                public:
                    T value;
                    const NodeTypeEnum nodeType;
                    NodeVisitStateEnum visitState;

                    std::map<T, std::shared_ptr<Node<T>>> connections;

                    // Used for Binary Trees
                    shared_ptr<Node<T>> left;
                    shared_ptr<Node<T>> right;

                    friend std::ostream& operator<<(std::ostream& os, const Node &node) {
                        string nodeTypeString = "--";
                        switch (node.nodeType) {
                            case DIRECTED: 
                                nodeTypeString = "->"; 
                                break;
                            case UNDIRECTED:
                            case BINARY_TREE:
                            default:
                                nodeTypeString = "--"; 
                                break;
                        }

                        os << node.value << " " << nodeTypeString << " {";
                        bool first = true;
                        for (const auto &c: node.connections) {
                            os << (first ? "":" ") << c.first;
                            first = false;
                        }
                        os << "}";
                        return os;
                    }

            };
    }
}

#endif
