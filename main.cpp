#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "readFromFile.hpp"
#include "Graph.h"
#include "Edge.h"
#include "BFS.h"

using namespace std;

void printPath(vector<Vertex> path, Vertex firstPoint)
{
    cout << "Actual path: ";
    for(Vertex v: path)
    {
        cout << v << " <- ";
    }
    cout << firstPoint << endl;
}

int main(int argc, char *argv[])
{
    (void)argc;

    Vertex firstPoint = argv[1];
    Vertex secondPoint = argv[2];
    string algorithmType = argv[3];

    vector<string> vectorRepr = file_to_vector(argv[4]);
    vector<int> weights;
    vector<Vertex> fromNodeId;
    vector<Vertex> toNodeId;

    cout << "Start vertex ID: " << firstPoint << endl;
    cout << "End vertex ID: " << secondPoint << endl;
    cout << endl;

    int count = 0; // Used for putting current vertex and its weight into corresponding vector
    for (auto word : vectorRepr)
    {  
        if(count%3 == 0) weights.push_back(stoi(word));
        else if(count%3 == 1) fromNodeId.push_back(word);
        else toNodeId.push_back(word);
        count++;
	}

    // Create graph
    Graph g(weights, fromNodeId, toNodeId);

    // Use BFS to traverse the graph
    BFS bfs(g, firstPoint);
    BFS::Iterator it;
    cout << "Result of BFS:";
    for(it = bfs.begin(); it != bfs.end(); ++it)
    {
        cout << " " << *it;
    }
    cout << endl;
    cout << endl;

    if (algorithmType == "d")
    {      
        // Call dijkstras algorithm
        cout << "Running Dijkstra's algorithm..." << endl;
        pair<int, vector<Vertex>> res = g.dijkstrasPath(firstPoint, secondPoint);
        
        // Print out shortest distance and path
        if(res.first == 1000000000) cout << "End vertex unreachable." << endl;
        else
        {
            cout << "Path length for Dijkstra's algorithm: " << res.first << endl;
            printPath(res.second, firstPoint);
        }
    }
    else if (algorithmType == "a")
    {     
        // Call A* algorithm
        cout << "Running A* search algorithm..." << endl;
        pair<int, vector<Vertex>> res = g.aStarPath(firstPoint, secondPoint);

        // Print out shortest distance and path      
        if(res.first == -1) cout << "End vertex unreachable." << endl;
        else
        {
            cout << "Path length for A* search: " << res.first << endl;
            printPath(res.second, firstPoint);
        }
    }
    else
    {
        cout << "Algorithm type not found, please make sure you typed \"d\" or \"a\" for algorithm types." << endl;
    }

    return 0;
}