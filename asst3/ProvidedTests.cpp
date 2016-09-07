#include "ProvidedTests.h"
#include <cassert>
#include <vector>
#include "Graph.h"
#include "util.h"

using namespace util;
using namespace std::string_literals;
using namespace gdwg;

void test1() {
    Graph<int, int> g;
    // add some nodes to each graph.
    g.addNode(1);
    int i = 2;
    assert(g.addNode(i));
    double d = 3.41;
    assert(g.addNode(static_cast<int>(d)));
    assertNodesEq(g, {1, 2, 3});

    Graph<std::string, double> g2{};
    std::string s = "world";
    assert(g2.addNode(s));
    assert(g2.addNode("Hello"));
    assertNodesEq(g2, {"Hello", "world"});


    Graph <std::shared_ptr<int>, std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    assert(g3.addNode(sp));
    assert(g3.addNode(std::make_shared<int>(6)));
    assert(g3.isNode(sp));
}

void test2() {
    // create 3 graphs
    Graph<int,int> g;
    g.addNode(1);
    int i = 2;
    g.addNode(i);
    double d = 3.41;
    g.addNode(static_cast<int>(d));
    g.addEdge(2,1,3);
    int j = 3;
    g.addEdge(i,j,1);
    assertEdgesEq(g, 2, {{3, 1}, {1, 3}});


    Graph<std::string,double> g2{};
    g2.addNode("Hello");
    std::string s = "world";
    g2.addNode(s);

    g2.addEdge("Hello","world",d);
    assertEdgesEq(g2, "Hello"s, {{s, d}});
    assertEdgesEq(g2, s, {});

    Graph<std::shared_ptr<int>,std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    g3.addNode(sp);
    g3.addNode(std::make_shared<int>(6));

    assertNodesEq(g, {1, 3, 2});
}

void test3() {
    Graph<int,int> g;
    g.addNode(1);
    int i = 2;
    g.addNode(i);
    double d = 3.41;
    g.addNode(static_cast<int>(d));
    i = 1;
    assert(!g.addNode(i));
    g.addEdge(2,1,3);
    int j = 3;
    g.addEdge(i,j,1);
    assert(!g.addEdge(2,1,3));
    // try to add an edge with a different weight
    assert(g.addEdge(2,1,2));
    assertThrows(g.addEdge(7, 1, 3));
    assertThrows(g.addEdge(2, 7, 3));

    Graph<std::string,double> g2{};
    g2.addNode("Hello");
    std::string s = "world";
    g2.addNode(s);
    assert(!g2.addNode("Hello"));
    g2.addEdge("Hello","world",d);
    assert(!g2.isConnected("world","Hello"));
    assertThrows(g2.isConnected("hello","pluto"));

    Graph<std::shared_ptr<int>,std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    g3.addNode(sp);
    g3.addNode(std::make_shared<int>(6));
    assert(!g3.addNode(sp));
    assert(g3.addNode(std::make_shared<int>(6)));
    
    assertThrows(g.printEdges(5));
}

const std::vector<std::function<void()>> tests = {test1, test2, test3};

void providedTests() {
    for (auto i = 0U; i < tests.size(); i++) {
        std::cout << "Running test " << i + 1 << "...";
        std::cout.flush();
        tests[i]();
        std::cout << "Passed\n";
    }
}