#include "Graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidLabel);
const int maxDistance = 1000000000;

using namespace std;

Graph::Graph(vector<int> weights, vector<Vertex> fromNodes, vector<Vertex> toNodes)
{

    for (size_t i = 0; i < fromNodes.size(); i++)
    {
        if (!vertexExists(fromNodes[i]))
        {
            insertVertex(fromNodes[i]);
        }
        if (!vertexExists(toNodes[i]))
        {
            insertVertex(toNodes[i]);
        }
    }

    int numVertices = getVertices().size();
    if (numVertices < 2)
    {
        error("The number of vertices is too low");
        exit(1);
    }

    // make sure all vertices are connected    
    for (size_t i = 0; i < fromNodes.size(); ++i)
    {
        Vertex cur = fromNodes[i];
        Vertex next = toNodes[i];
        insertEdge(cur, next);
        int weight = weights[i];
        setEdgeWeight(cur, next, weight);
    }
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end()) {
        std::cout << "Can not find vertex" << source << std::endl; 
        return vector<Vertex>();
    }
    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}

Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                // this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    return new_edge;
}

string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;

    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{
    if (adjacency_list.find(v) != adjacency_list.end())
    {       
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);

    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);

    return e;
}

Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }

    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    return true;
}

void Graph::clear()
{
    adjacency_list.clear();
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

void Graph::printGraph() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Find shortest path from start Vertex to end Vertex using A* algorithm
 * @param start - the starting Vertex
 * @param end - the ending Vertex
 * @return a pair containing the shortest distance from start to end (int) and 
 * the path taken (vector of Vertex objects)
 */
pair<int, vector<Vertex>> Graph::aStarPath(Vertex start, Vertex end)
{
    unordered_map<Vertex, int> h;
    for(Vertex src: getVertices())
    {
        h[src] = abs(stoi(src)-stoi(end));
    }

    unordered_map<Vertex, int> g;   
    for(Vertex v: getVertices())
    {
        g[v] = maxDistance;
    }
    g[start] = 0;

    unordered_map<Vertex, int> f;
    for(Vertex v: getVertices())
    {
        f[v] = g[v] + h[v];
    }

    unordered_map<Vertex, Vertex> prev; // used to store predecesor vertex

    priority_queue <pair<int, Vertex>, vector<pair<int, Vertex>>, greater<pair<int, Vertex>>> openSet;
    vector<Vertex> verticesInOpenSet;
    openSet.push(make_pair(f[start], start));
    verticesInOpenSet.push_back(start); // auxiliary vector that helps to find existing vertex in openSet

    while(!openSet.empty())
    {
        Vertex cur = openSet.top().second; // vertex that has lowest f value
        if(cur == end) // end vertex reached
        {
            vector<Vertex> path;            
            while(prev.find(cur) != prev.end())
            {
                path.push_back(cur); // put all vertices along shortest path in vector
                cur = prev[cur];
            }
            return make_pair(openSet.top().first, path);
        }

        openSet.pop();
        vector<Vertex>::iterator it = find(verticesInOpenSet.begin(), verticesInOpenSet.end(), cur);
        if(it != verticesInOpenSet.end()) verticesInOpenSet.erase(it);

        for(Vertex neighbor: getAdjacent(cur))
        {
            int tentative_g = g[cur] + getEdgeWeight(cur,neighbor);
            if(tentative_g < g[neighbor])
            {
                prev[neighbor] = cur;
                g[neighbor] = tentative_g;
                f[neighbor] = g[neighbor] + h[neighbor];
                vector<Vertex>::iterator it = find(verticesInOpenSet.begin(), verticesInOpenSet.end(), neighbor);
                if(it == verticesInOpenSet.end())
                {
                    openSet.push(make_pair(f[neighbor], neighbor));
                    verticesInOpenSet.push_back(neighbor);
                }
            }
        }
    }

    // end vertex unreachable
    vector<Vertex> res;
    return make_pair(-1, res);
}

/**
 * Find shortest path from start Vertex to end Vertex using Dijkstra's algorithm
 * @param start - the starting Vertex
 * @param end - the ending Vertex
 * @return a pair containing the shortest distance from start to end (int) and 
 * the path taken (vector of Vertex objects)
 */
pair<int, vector<Vertex>> Graph::dijkstrasPath(Vertex start, Vertex end)
{
    unordered_map<Vertex, int> dist;
    unordered_map<Vertex, Vertex> prev; // used to store predecesor vertex
    priority_queue <pair<int, Vertex>, vector<pair<int, Vertex>>, greater<pair<int, Vertex>>> PQ;
    dist[start] = 0;

    // Add all vertices to priority queue
    for(Vertex v: getVertices())
    {
        if(v != start)
        {
            dist[v] = maxDistance;
        }
        PQ.push(make_pair(dist[v], v));
    }
    
    while (!PQ.empty())
    {
        // Get vertex with minimum distance from start
        Vertex cur = PQ.top().second;
        PQ.pop();

        for (Vertex neighbor : getAdjacent(cur))
        {   
            // Calculate distance to adjacent node
            int newDist = dist[cur] + getEdgeWeight(cur, neighbor);
            if (newDist < dist[neighbor])
            {
                // Update with new distance and prev vertex
                dist[neighbor] = newDist;
                prev[neighbor] = cur;

                // Update priority queue with updated distance
                priority_queue <pair<int, Vertex>, vector<pair<int, Vertex>>, greater<pair<int, Vertex>>> newPQ;
                for (Vertex v : getVertices())
                {
                    newPQ.push(make_pair(dist[v], v));
                }
                PQ = newPQ;
            }
        }

        // terminate if target node is reached
        if(cur == end)
        {
            break;
        }
    }
    // Find shortest path to end point
    vector<Vertex> path;
    Vertex cur = end;           
    while(prev.find(cur) != prev.end())
    {
        path.push_back(cur); // put all vertices along shortest path in vector
        cur = prev[cur];
    }
    return make_pair(dist[end], path);
}