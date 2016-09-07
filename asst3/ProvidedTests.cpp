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
    assert(g.addNode(1));
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
    Graph<int, int> g;
    assert(g.addNode(1));
    int i = 2;
    assert(g.addNode(i));
    double d = 3.41;
    assert(g.addNode(static_cast<int>(d)));
    assert(g.addEdge(2, 1, 3));
    int j = 3;
    assert(g.addEdge(i, j, 1));
    assertEdgesEq(g, 2, {{3, 1}, {1, 3}});
    assertNodesEq(g, {1, 3, 2});


    Graph<std::string, double> g2{};
    g2.addNode("Hello");
    std::string s = "world";
    g2.addNode(s);

    g2.addEdge("Hello", "world", d);
    assertEdgesEq(g2, "Hello"s, {{s, d}});
    assertEdgesEq(g2, s, {});

    Graph<std::shared_ptr<int>, std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    g3.addNode(sp);
    g3.addNode(std::make_shared<int>(6));
}

void test3() {
    Graph<int, int> g;
    assert(g.addNode(1));
    int i = 2;
    assert(g.addNode(i));
    double d = 3.41;
    assert(g.addNode(static_cast<int>(d)));
    i = 1;
    assert(!g.addNode(i));
    assert(g.addEdge(2, 1, 3));
    int j = 3;
    assert(g.addEdge(i, j, 1));
    assert(!g.addEdge(2, 1, 3));
    // try to add an edge with a different weight
    assert(g.addEdge(2, 1, 2));
    assertThrows(g.addEdge(7, 1, 3));
    assertThrows(g.addEdge(2, 7, 3));

    Graph<std::string, double> g2{};
    g2.addNode("Hello");
    std::string s = "world";
    g2.addNode(s);
    assert(!g2.addNode("Hello"));
    g2.addEdge("Hello", "world", d);
    assert(!g2.isConnected("world", "Hello"));
    assertThrows(g2.isConnected("hello", "pluto"));

    Graph<std::shared_ptr<int>, std::string> g3{};
    std::shared_ptr<int> sp = std::make_shared<int>(5);
    g3.addNode(sp);
    g3.addNode(std::make_shared<int>(6));
    assert(!g3.addNode(sp));
    assert(g3.addNode(std::make_shared<int>(6)));
    
    assertThrows(g.printEdges(5));
}

void test4() {
    gdwg::Graph<std::string, int> gCopy;

    // create some data to store as nodes.
    std::string s = "a";
    std::string t = "b";
    std::string u = "c";

    // add this data into the graph
    gCopy.addNode(s);
    gCopy.addNode(t);
    gCopy.addNode(u);

    gCopy.addEdge(u, t, 1);
    gCopy.addEdge(u, t, 2);

    assertNodesEq(gCopy, {s, t, u});
    // change the value of t and make sure that the graph still prints out the original value
    t = "d";
    assertNodesEq(gCopy, {s, "b", u});

    gdwg::Graph<std::shared_ptr<std::string>, std::shared_ptr<int>> gPtr;
    std::shared_ptr<std::string> sPtr = std::make_shared<std::string>("a");
    std::shared_ptr<std::string> tPtr = std::make_shared<std::string>("b");
    std::shared_ptr<std::string> uPtr = std::make_shared<std::string>("c");
    gPtr.addNode(sPtr);
    gPtr.addNode(tPtr);
    gPtr.addNode(uPtr);

    // add an edge between u and t
    gPtr.addEdge(uPtr, tPtr, std::make_shared<int>(1));
    // add a second edge between u and t with a different weight
    gPtr.addEdge(uPtr, tPtr, std::make_shared<int>(2));

    // change the value of the data in the ptr
    *tPtr = "d";

    // this should have updated in the graph as well as it is a pointer.
    // can confirm this using isNode
    assert(!gCopy.isNode(t));
    assert(gPtr.isNode(tPtr));
}

void test5() {
    gdwg::Graph<std::string, int> gCopy;

    // create some data to store as nodes.
    std::string s = "a";
    std::string t = "b";
    std::string u = "c";

    // add this data into the graph
    gCopy.addNode(s);
    gCopy.addNode(t);
    gCopy.addNode(u);

    gCopy.addEdge(u, t, 1);
    gCopy.addEdge(u, t, 2);

    assertNodesEq(gCopy, {s, t, u});

    gCopy.replace("a", "e");
    assertNodesEq(gCopy, {t, "e", u});

    assert(!gCopy.replace("b", "c"));

    assertThrows(gCopy.replace("a", "d"));
}

void test6 () {
    // make a graph
    gdwg::Graph<unsigned int,std::string> g;

    assert(g.addNode(1));
    assert(g.addNode(2));
    assert(g.addNode(3));
    assert(g.addNode(4));

    assert(g.addEdge(1,2,"1->2"));
    assert(g.addEdge(2,3,"2->3"));
    assert(g.addEdge(2,4,"2->4"));
    assert(g.addEdge(3,2,"3->2"));
    assert(g.addEdge(3,4,"3->4"));
    assert(g.addEdge(2,4,"cs6771"));
    assert(g.addEdge(3,4,"cs6771"));

    assertEdgesEq(g, 1U, {{2U, "1->2"}});
    assertEdgesEq(g, 2U, {{3U, "2->3"}, {4U, "2->4"}, {4U, "cs6771"}});
    assertEdgesEq(g, 3U, {{2U, "3->2"}, {4U, "3->4"}, {4U, "cs6771"}});
    assertEdgesEq(g, 4U, {});

    g.mergeReplace(2,3);

    assertEdgesEq(g, 3U, {{2U, "1->2"}});
    assertThrows(g.printEdges(2));
    assertEdgesEq(g, 3U, {{3U, "2->3"}, {4U, "2->4"}, {3U, "3->2"}, {4U, "3->4"}, {4U, "cs6771"}});
    assertEdgesEq(g, 4U, {});
}

const std::vector<std::function<void()>> tests = {test1, test2, test3, test4, test5, test6};

void providedTests() {
    for (auto i = 0U; i < tests.size(); i++) {
        std::cout << "Running test " << i + 1 << "..." << std::endl;
        tests[i]();
    }
}