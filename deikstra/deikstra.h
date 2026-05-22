#ifndef DEIKSTRA_H
#define DEIKSTRA_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

class Node;
typedef std::set<Node*>::const_iterator node_iterator;

class Node {
    std::string name;
    std::set<Node*> neighbours;
    std::map<Node*, int> edgeWeights; 

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);

public:
    Node(const std::string& aname) : name(aname) {}
    const std::string& getName() const { return name; }
    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end() const { return neighbours.end(); }


    void setWeight(Node* neighbor, int w) { edgeWeights[neighbor] = w; }
    int getWeight(Node* neighbor) { return edgeWeights[neighbor]; }

    friend class Graph;
};


class Graph {
    std::set<Node*> nodes;
public:
    void addNode(Node* node) { nodes.insert(node); }
    void addEdge(Node* begin, Node* end, int weight);
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const { return nodes.end(); }
};


struct MarkedNode {
    Node* node;
    int mark;
    Node* prev;
    MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0) :
        node(anode), mark(amark), prev(aprev) {
    }
};


class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};

struct Way {
    std::vector<Node*> nodes;
    int length;
    Way() : length(-1) {}
};

class Dijkstra {
    const Graph& graph;
public:
    Dijkstra(const Graph& agraph) : graph(agraph) {}
    Way shortestWay(Node* begin, Node* end);
    static Way unroll(std::map<Node*, MarkedNode> visited, Node* begin, Node* curr);
};

#endif
