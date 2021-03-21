#include "../tests/catch/catch.hpp"
#include "../Edge.h"
#include "../Graph.h"
#include "../BFS.h"
#include <iostream>
#include <string>

/**
 * Edge tests
 */
TEST_CASE("Test Edge class", "[weight=30]")
{
    Edge e("0", "10", 5, std::string());
    Edge f("1", "6", 2, std::string());

    REQUIRE((e < f) == false);

    REQUIRE(e.getWeight() == 5);
    REQUIRE(f.getLabel() == "");

    REQUIRE((e == f) == false);
}

/**
 * Graph tests
 */
TEST_CASE("Test Graph class", "[weight=30]")
{
    std::vector<int> weights{10,10,12,12,15,15,14,14,1,1};
    std::vector<Vertex> fromNodeId{"0","1","1","2","2","5","4","5","1","5"};
    std::vector<Vertex> toNodeId{"1","0","2","1","5","2","5","4","5","1"};
    Graph g(weights, fromNodeId, toNodeId);

    REQUIRE(g.getEdgeWeight("0", "1") == 10);
    REQUIRE(g.getEdgeWeight("5", "2") == 15);
    REQUIRE(g.getEdgeWeight("1", "5") == 1);
}

/**
 * Algorithm tests
 */
TEST_CASE("Test Dijkstra's algorithm", "[weight=30]")
{
    std::vector<int> weights{10,10,12,12,15,15,14,14,1,1};
    std::vector<Vertex> fromNodeId{"0","1","1","2","2","5","4","5","1","5"};
    std::vector<Vertex> toNodeId{"1","0","2","1","5","2","5","4","5","1"};
    Graph g(weights, fromNodeId, toNodeId);
    pair<int, vector<Vertex>> res = g.dijkstrasPath("0", "5");
    REQUIRE(res.first == 11);
    REQUIRE(res.second == vector<Vertex>{"5","1"});
}

TEST_CASE("Test A* search algorithm", "[weight=30]")
{
    std::vector<int> weights{10,10,12,12,15,15,14,14,1,1};
    std::vector<Vertex> fromNodeId{"0","1","1","2","2","5","4","5","1","5"};
    std::vector<Vertex> toNodeId{"1","0","2","1","5","2","5","4","5","1"};
    Graph g(weights, fromNodeId, toNodeId);
    pair<int, vector<Vertex>> res = g.aStarPath("0", "5");
    REQUIRE(res.first == 11);
    REQUIRE(res.second == vector<Vertex>{"5","1"});
}

/**
 * Simple BFS Iterator test
 */
TEST_CASE("BFS maintains correct ordering", "[weight=10]")
{   
    Vertex one = "one";
    Vertex two = "two";
    Vertex three = "three";
    Vertex four = "four";

    Graph g = Graph();
    BFS bfs = BFS(Graph(), "zero");
    bfs.add(one);
    bfs.add(two);
    bfs.add(three);
    bfs.add(four);

    REQUIRE( bfs.pop() == "zero");
    REQUIRE( bfs.pop() == "one");
    REQUIRE( bfs.pop() == "two");
    REQUIRE( bfs.pop() == "three");
    REQUIRE( bfs.pop() == "four");

}