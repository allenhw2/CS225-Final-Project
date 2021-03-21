/**
 * @file BFS.cpp
 * 
 * Breadth-first data traversal
 * Based on the traversal used in mp_traversals
 *
 */

#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "Graph.h"

#include "BFS.h"

BFS::BFS() {
    // nothing
}

/**
 * Initializes a breadth-first traversal on a given graph, starting at `start
 * @param graph The graph this BFS is going to traverse
 * @param v_start The start vertex of this BFS
 */
BFS::BFS(const Graph &graph, const Vertex &v_start) {
    graph_ = graph;
    start_ = v_start;
    q.push(start_);
}

/**
 * @returns Iterator for the traversal starting at the first point.
 */
BFS::Iterator BFS::begin() {
    return BFS::Iterator(this);
}

/**
 * @returns Iterator for the traversal one past the end of the traversal.
 */
BFS::Iterator BFS::end() {
    return BFS::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 * @param vertex the vertex to add
 */
void BFS::add(const Vertex &vertex) {
    q.push(vertex);
}

/**
 * Returns the size of the traversal.
 */
int BFS::size() const {
    return q.size();
}

/**
 * @returns bool true if the traversal is empty.
 */
bool BFS::empty() const {
    return q.empty();
}

/**
 * Removes and returns the current Vertex in the traversal.
 * @returns Vertex the popped Vertex
 */
Vertex BFS::pop() {
    if (empty()) {
        return "";
    }
    Vertex temp = q.front();
    q.pop();
    return temp;
}

/**
 * Returns the current Vertex in the traversal.
 * @returns Vertex the current Vertex
 */
Vertex BFS::peek() {
    if (empty()) {
        return "";
    }
    return q.front();
}


// iterator implementation below

/**
 * Default iterator constructor
 */
BFS::Iterator::Iterator() : traversal(NULL) {
    // do nothing
}

/**
 * Traversal iterator constructor
 * @param traversal current traversal
 * @returns Iterator current iterator
 */
BFS::Iterator::Iterator(BFS* traversal) : traversal(traversal) {
    vector<Vertex> vertices = traversal->graph_.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        std::pair<Vertex, bool> p(vertices[i], false); 
        visited.insert(p);
    }

    current = traversal->peek();
    if(current != "") // fixed issue in line 109 by using this if statement (probably)
    {
        visited[current] = true; // this might cause an issue if the vertex doesn't exist
    }
}

/**
 * Iterator increment operator
 * Advances the traversal of the image
 * @return iterator to the next point
 */
BFS::Iterator& BFS::Iterator::operator++() {
    current = traversal->peek();
    traversal->pop();
    visited[current] = true;   
    add_adjacent(current);

    while (!traversal->empty() && visited[traversal->peek()]) { // pop already visited vertices
        traversal->pop();
    }

    if (traversal->empty()) { // traversal over
        map<Vertex, bool>::iterator it; 
        for (it = visited.begin(); it != visited.end(); it++) 
        { 
            if(it->second == false)
            {
                traversal->add(it->first);
                current = traversal->peek();
                break;
            }
        }
        return *this;
    }

    current = traversal->peek(); // next valid vertex
    return *this;
}

/**
 * Iterator accessor operator
 * Accesses the current point in the traversal
 * @return the current vertex
 */
Vertex BFS::Iterator::operator*() {
    return current;
}

/**
 * Iterator inequality operator
 * Determines if two iterators are not equal
 * @param other the iterator to compare to
 * @return whether the two are unequal
 */
bool BFS::Iterator::operator!=(const Iterator &other) {
    bool thisEmpty = false; 
    bool otherEmpty = false;

    if (traversal == NULL) { 
        thisEmpty = true; 
    }
    if (other.traversal == NULL) { 
        otherEmpty = true; 
    }
    if (!thisEmpty) { 
        thisEmpty = traversal->empty(); 
    }
    if (!otherEmpty) {
        otherEmpty = other.traversal->empty();
    }
    if (thisEmpty && otherEmpty) {
        return false; 
    }
    else if ((!thisEmpty)&&(!otherEmpty)) {
        return (traversal != other.traversal); 
    }
    else {
        return true; 
    }
}

/**
 * Adds the vertices adjacent to the current vertex to the traversal
 * @param current the current vertex
 */
void BFS::Iterator::add_adjacent(Vertex vertex) {
    vector<Vertex> adjacent = traversal->graph_.getAdjacent(vertex);
    for (size_t i = 0; i < adjacent.size(); i++) {
        if(visited[adjacent[i]] == false)
        {
            traversal->add(adjacent[i]);
        }
    }
}
