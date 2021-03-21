#pragma once
#include <string>
using std::string;

typedef string Vertex;

/**
 * Class adapted from CS 225 Lab ML
 */
class Edge
{
  public:
    Vertex source;
    Vertex dest;

    /**
     * Default Constructor
     * */
    Edge();

    /**
     * Constructor
     * @param Vertex u the origin vertex
     * @param Vertex V the destination vertex
     * */
    Edge(Vertex u, Vertex v);

    /**
     * Constructor
     * @param Vertex u the origin vertex
     * @param Vertex V the destination vertex
     * @param string lbl the label of the edge
     * */
    Edge(Vertex u, Vertex v, string lbl);

    /**
     * Constructor
     * @param Vertex u the origin vertex
     * @param Vertex V the destination vertex
     * @param int w the weight of the edge
     * @param string lbl the label of the edge
     * */
    Edge(Vertex u, Vertex v, int w, string lbl);
    
    /**
     * Get label functionn for the current edge
     * @param none
     * @return string the label for the edge
     * */
    string getLabel() const;

    /** 
     * equivalent operator 
     * @param none
     * @return bool returns true if the edges have the same origin and same destination
     * */
    bool operator==(Edge& other) const;

    /**
     * gets the weight of the edge
     * @param none
     * @return int the weight provided for the edge
     * */
    int getWeight() const;
    
    /**
     * Less than operator that compares the weight of the edges
     * @param &Edge the address of the edged to be compared too
     * @return bool returns true if the current edge weight is less than the other's
     * */
    bool operator<(const Edge& other) const;

private:
    /* the edge label */
    string label; 

    /* the edge weight*/
    int weight;
};