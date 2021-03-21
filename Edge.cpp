#include "Edge.h"
using std::string;


Edge::Edge(Vertex u, Vertex v, int w, string lbl)
    : source(u), dest(v), label(lbl), weight(w)
{ /* nothing */
}

/**
 * 
 */
Edge::Edge(Vertex u, Vertex v)
    : source(u), dest(v), label(""), weight(-1)
{}

/**
 * 
 */
Edge::Edge(Vertex u, Vertex v, string lbl)
    : source(u), dest(v), label(lbl), weight(-1)
{}

/**
 * Default constructor for Edge object.
 */
Edge::Edge() : source(""), dest(""), label(""), weight(-1)
{}

/**
 * Gets label of edge.
 */
string Edge::getLabel() const
{
    return this->label;
}

int Edge::getWeight() const
{
    return this->weight;
}

bool Edge::operator<(const Edge& other) const
{
    return weight < other.weight;
}

/**
 * 
 */
bool Edge::operator==(Edge& other) const
{
    if (this->source != other.source)
        return false;
    if (this->dest != other.dest)
        return false;
    return true;
}