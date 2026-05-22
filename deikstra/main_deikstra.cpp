#include <iostream>
#include <algorithm>
#include "deikstra.h"
using namespace std;
int main() {
    Graph g;
    
    map<int, Node*> n;
    for (int i = 1; i <= 19; i++) {
        n[i] = new Node(std::to_string(i));
        g.addNode(n[i]);
    }
    g.addEdge(n[1], n[2], 10);
    g.addEdge(n[1], n[3], 6);
    g.addEdge(n[1], n[4], 8);
    g.addEdge(n[2], n[4], 5);
    g.addEdge(n[2], n[7], 11);
    g.addEdge(n[2], n[5], 13);
    g.addEdge(n[3], n[5], 3);
    g.addEdge(n[4], n[3], 2); 
    g.addEdge(n[4], n[5], 5);
    g.addEdge(n[4], n[6], 7);
    g.addEdge(n[4], n[7], 12);
    g.addEdge(n[5], n[6], 9);
    g.addEdge(n[5], n[9], 12);
    g.addEdge(n[6], n[8], 8);
    g.addEdge(n[6], n[9], 10);
    g.addEdge(n[7], n[6], 4);
    g.addEdge(n[7], n[8], 6);
    g.addEdge(n[7], n[9], 16);
    g.addEdge(n[8], n[9], 15);

    Dijkstra d(g);
    Way result = d.shortestWay(n[1], n[9]);

    if (result.length != -1) {
        cout << "Короткий путь: " << result.length << std::endl;
        cout << "Путь: ";
        reverse(result.nodes.begin(), result.nodes.end());
        for (Node* node : result.nodes) {
            cout << node->getName() << " ";
        }
    }
    else {
        cout << "не найден" << endl;
    }

    return 0;
}