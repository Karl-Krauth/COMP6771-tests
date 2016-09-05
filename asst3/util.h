#ifndef UTIL_H
#define UTIL_H

#include "Graph.h"
#include <vector>
#include <sstream>
#include <iterator>
#include <cassert>
#include <map>

namespace util {

template <typename N, typename E>
void assertNodesEq(const gdwg::Graph<N, E> &graph, const std::vector<N>& expectedNodes) {
    std::stringstream actual, expected;
    // this is the easiest way I can think of to test your graph, while making sure it still works with printNodes()
    graph.printNodes(actual); // ENSURE YOU MAKE void Graph::printNodes(ostream& stream = std::cout)
    std::copy(expectedNodes.begin(), expectedNodes.end(), std::ostream_iterator<N>(expected, "\n"));
    if (expected.str() != actual.str()) {
        std::cout << "Expected:\n" << expected.str() << "\nGot:\n" << actual.str();
        assert(expected.str() == actual.str());
    }
}

template <typename N, typename E>
void assertEdgesEq(const gdwg::Graph<N, E>& graph, const N& value, const std::vector<std::pair<N, E>>& expectedEdges) {
    std::stringstream actual, expected;
    graph.printEdges(value, actual);
    expected << "Edges attached to Node " << value << "\n";
    if (expectedEdges.empty())
        expected << "(null)\n";
    else {
        std::sort(expectedEdges.begin(), expectedEdges.end(), [] (const auto &lhs, const auto &rhs) {
            // prioritise by edge (.second), then take node (.first) if required
            if (lhs.second < rhs.second)
                return true;
            else if (rhs.second < lhs.second)
                return false;
            return lhs.first < rhs.first;
        });
    }
    for (const auto& edge : expectedEdges) {
        expected << edge.first << edge.second << "\n";
    }

    if (expected.str() != actual.str()) {
        std::cout << "Expected:\n" << expected.str() << "\nGot:\n" << actual.str();
        assert(expected.str() == actual.str());
    }
};

}

#endif //UTIL_H
