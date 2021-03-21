/**
 * @file BFS.h
 * 
 * Breadth-first data traversal
 * Based on the traversal used in mp_traversals
 *
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <map>

#include "Graph.h"
#include "Edge.h"

using namespace std;

class BFS
{
    public:
    class Iterator : std::iterator<std::forward_iterator_tag, string>
    {
        public:
        Iterator();
        Iterator(BFS* traversal);
        Iterator & operator++();
        Vertex operator*(); 
        bool operator !=(const Iterator &other);
        Vertex current;
        map<Vertex, bool> visited;

        private:
        BFS* traversal;
        void add_adjacent(Vertex current);
    };
    BFS();
    BFS(const Graph &graph, const Vertex &v);
    Graph graph_;
    Vertex start_;
    Iterator begin();
    Iterator end();
    void add(const Vertex &vertex);
    Vertex pop();
    Vertex peek();
    int size() const;
    bool empty() const;

    private:
        std::queue<Vertex> q;

};