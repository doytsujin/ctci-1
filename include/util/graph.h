#ifndef CTCI_UTIL_GRAPH_H
#define CTCI_UTIL_GRAPH_H

#include <map>
#include <ostream>
#include <vector>
#include <utility>

#include "util/node.h"

namespace ctci 
{ 
    namespace util 
    {
        template <typename T>
        class Graph {
            public:
                bool insert(std::vector<T> &);
                bool insert(const T &);

                bool insert(std::vector<std::pair<T, T>> &);
                bool insert(const std::pair<T, T> &);

                std::map<T, std::shared_ptr<Node<T>>> nodes;

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
