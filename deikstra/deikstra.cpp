#include "deikstra.h"

void Graph::addEdge(Node* begin, Node* end, int weight) {
    begin->addNeighbour(end);
    end->addNeighbour(begin);
    begin->setWeight(end, weight);
    end->setWeight(begin, weight);
}
void Node::addNeighbour(Node* neighbour) { 
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    if (neighbour) {
        neighbours.erase(neighbour);
    }
}
MarkedNode PriorityQueue::pop() {
    MarkedNode mn = nodes.back();
    nodes.pop_back();
    return mn;
}

void PriorityQueue::push(Node* node, int mark, Node* prev) {
    std::vector<MarkedNode>::iterator it = nodes.begin();
    MarkedNode mn(node, mark, prev);
    while (it != nodes.end() && mark < it->mark) it++;
    if (it == nodes.end()) nodes.push_back(mn);
    else nodes.insert(it, mn);
}

Way Dijkstra::shortestWay(Node* begin, Node* end) {
    PriorityQueue nodes;
    nodes.push(begin, 0, 0);
    std::map<Node*, MarkedNode> visited;

    while (!nodes.empty()) {
        MarkedNode next = nodes.pop();
        if (visited.find(next.node) != visited.end()) continue;

        visited[next.node] = next;
        if (end == next.node) return unroll(visited, begin, end);

        for (node_iterator it = next.node->nb_begin(); it != next.node->nb_end(); it++) {
            
            int weight = next.node->getWeight(*it) + next.mark;
            if (visited.find(*it) == visited.end()) {
                nodes.push(*it, weight, next.node);
            }
        }
    }
    return Way();
}
Way Dijkstra::unroll(std::map<Node*, MarkedNode> visited, Node* begin, Node* curr) {
    Way way;
    way.length = visited[curr].mark;
    while (curr != begin) {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
    }
    way.nodes.push_back(begin);
    return way;
}