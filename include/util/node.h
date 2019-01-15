#ifndef CTCI_UTIL_NODE_H
#define CTCI_UTIL_NODE_H

#include <ostream>
#include <vector>
#include <utility>

namespace ctci 
{ 
    namespace util 
    {
        enum VisitEnum { Unvisited, Visiting, Visited };
        template <typename T>
            class Node 
            {
                public:
                    Node(T t);

                    bool insert(std::vector<std::pair<T, std::shared_ptr<Node<T>>>> &);
                    bool insert(const std::pair<T, std::shared_ptr<Node<T>>> &);

                    T value;
                    std::map<T, std::shared_ptr<Node<T>>> connections;
                    VisitEnum visitState;

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
