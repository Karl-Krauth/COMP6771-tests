#include "ProvidedTests.h"
#include <cassert>
#include <vector>
#include "Graph.h"
#include "util.h"

using namespace util;

void test1() {
    gdwg::Graph<int, int> g;
    // add some nodes to each graph.
    g.addNode(1);
    int i = 2;
    assert(g.addNode(i));
    double d = 3.41;
    assert(g.addNode(static_cast<int>(d)));
    assertNodesEq(g, {1, 2, 3});

    gdwg::Graph<std::string, double> g2{};
    std::string s = "world";
    assert(g2.addNode(s));
    assert(g2.addNode("Hello"));
    assertNodesEq(g2, {"Hello", "world"});


    gdwg::Graph <std::shared_ptr<int>, std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    assert(g3.addNode(sp));
    assert(g3.addNode(std::make_shared<int>(6)));
    assert(g3.isNode(sp));
}

void test2() {
    // create 3 graphs
    gdwg::Graph<int,int> g;
    g.addNode(1);
    int i = 2;
    g.addNode(i);
    double d = 3.41;
    g.addNode(static_cast<int>(d));
    g.addEdge(2,1,3);
    int j = 3;
    g.addEdge(i,j,1);
    assertEdgesEq(g, 2, );


    gdwg::Graph<std::string,double> g2{};
    g2.addNode("Hello");
    std::string s = "world";
    g2.addNode(s);


    gdwg::Graph<std::shared_ptr<int>,std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    g3.addNode(sp);
    g3.addNode(std::make_shared<int>(6));

    g2.addEdge("Hello","world",d);

    g2.printEdges("Hello");
    g2.printEdges("world");

    std::cout << "Printing nodes in graph g to check print order" << std::endl;
    g.printNodes();
}

const std::vector<std::function<void()>> tests = {test1, _mm_testnzc_si128()};

void providedTests() {
    for (auto i = 0U; i < tests.size(); i++) {
        printf("Running test %d\n", i + 1);
        tests[i]();
        printf("Completed test %d\n", i + 1);
    }
}