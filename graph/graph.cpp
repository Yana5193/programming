#include "Graph.h"
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <iostream>
void Node::addNeighbour(Node* neighbour) {
	if (neighbour) neighbours.insert(neighbour);
}
void Node::removeNeighbour(Node* neighbour) {
	neighbours.erase(neighbour);
}
Graph::Graph(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "[ОШИБКА] Не удалось открыть файл: " << fileName << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); 

	while (std::getline(file, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string u_name, v_name;
		if (ss >> u_name >> v_name) {
			static std::map<std::string, Node*> nameToNode;
			auto getNode = [&](const std::string& name) {
				for (Node* n : nodes) {
					if (n->getName() == name) return n;
				}
				Node* newNode = new Node(name);
				addNode(newNode);
				return newNode;
				};

			Node* u = getNode(u_name);
			Node* v = getNode(v_name);
			addEdge(u, v);
		}
	}
	file.close();
}
Graph::~Graph() {
	for (Node* n : nodes) delete n;
}
void Graph::removeNode(Node* node) {
	nodes.erase(node);
	for (std::set<Node*>::iterator it = nodes.begin();
		it != nodes.end(); it++) {
		(*it)->removeNeighbour(node);
	}
}
void Graph::addNode(Node* node) {
	if (node) nodes.insert(node);
}
void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addNeighbour(end);
	end->addNeighbour(begin);
}
void Graph::removeEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end()) return;
	if (nodes.find(end) == nodes.end()) return;

	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}

bool BFS::connected(Node* begin, Node* end) {
	std::queue<Node*> nodes; nodes.push(begin);
	std::set<Node*> visited;
	while (!nodes.empty()) {
		Node* next = nodes.front(); nodes.pop();
		if (end == next) return true;
		visited.insert(next);
		for (node_iterator it = next->nb_begin();
			it != next->nb_end(); it++)
			if (visited.find(*it) == visited.end())
				nodes.push(*it);
	}
	return false;
}
bool DFS::connected(Node* begin, Node* end) {
	visited.clear(); return connected(begin, end, 0);
}
bool DFS::connected(Node* begin, Node* end, int depth) {
	if (begin == end) return true;
	visited.insert(begin);
	for (node_iterator it = begin->nb_begin();
		it != begin->nb_end(); it++) {
		if (visited.find(*it) == visited.end()) {
			if (connected(*it, end, depth + 1)) return true;
		}
	}
	return false;
}
