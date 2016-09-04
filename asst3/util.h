#ifndef UTIL_H
#define UTIL_H

#include "Graph.h"
#include <vector>
#include <sstream>
#include <iterator>
#include <cassert>

namespace util {

template <typename N, typename E>
void assertNodesEq(const gdwg::Graph<N, E> &graph, std::vector<N> expectedNodes) {
    std::stringstream actual, expected;
    // this is the easiest way I can think of to test your graph, while making sure it still works with printNodes()
    graph.printNodes(actual); // ENSURE YOU MAKE void Graph::printNodes(ostream& stream = std::cout)
    std::copy(expectedNodes.begin(), expectedNodes.end(), std::ostream_iterator<N>(expected, "\n"));
    if (expected.str() != actual.str()) {
        std::cout << "Expected:\n" << expected.str() << "\nGot:\n" << actual.str();
        assert(expected.str() == actual.str());
    }
}

}

#endif //UTIL_H
