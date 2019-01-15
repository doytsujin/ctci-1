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

        enum VisitStateEnum {UNVISITED, VISITING, VISITED};
        template <typename T>
            class Node 
            {
                public:
                    Node(T t) : value(t), visitState(UNVISITED) {};

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
                            case VISITING: return "Visiting";
                            case VISITED: return "Visited";
                            default: return "Error";
                        }
                    }

                public:
                    T value;
                    std::map<T, std::shared_ptr<Node<T>>> connections;
                    VisitStateEnum visitState;

                    friend std::ostream& operator<<(std::ostream& os, const Node &node) {
                        os << node.value << " ->";
                        bool first = true;
                        for (const auto &c: node.connections) {
                            os << (first ? " ":", ") << c.first;
                            first = false;
                        }
                        return os;
                    }

            };
    }
}

#endif
