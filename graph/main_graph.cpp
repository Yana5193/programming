#include "Graph.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <set>
using namespace std;
void save_to_file(set<Node*> group, int number, string prefix) {
    string name = prefix + "_" + to_string(number) + ".txt";
    ofstream out(name);
    if (out.is_open()) {
        out << "Source,Target" << endl; 
        set<pair<string, string>> done_edges;
        for (Node* n : group) {
            for (auto it = n->nb_begin(); it != n->nb_end(); ++it) {
                string u = n->getName();
                string v = (*it)->getName();
                if (u > v) {
                    string temp = u;
                    u = v;
                    v = temp;
                }
                if (done_edges.find({ u, v }) == done_edges.end()) {
                    out << u << "," << v << endl;
                    done_edges.insert({ u, v });
                }
            }
        }
        out.close();
    }
}
void find_all_graphs(const Graph& g, string file_prefix) {
    set<Node*> not_visited;
    for (auto it = g.begin(); it != g.end(); ++it) {
        not_visited.insert(*it);
    }
    int graph_count = 0;
    while (!not_visited.empty()) {
        graph_count++;
        Node* start_node = *not_visited.begin();
        set<Node*> current_component;
        queue<Node*> q;

        q.push(start_node);
        not_visited.erase(start_node);
        current_component.insert(start_node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            // Смотрим всех соседей текущего узла
            for (auto it = current->nb_begin(); it != current->nb_end(); ++it) {
                Node* neighbor = *it;
                if (not_visited.count(neighbor)) {
                    not_visited.erase(neighbor);
                    current_component.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        save_to_file(current_component, graph_count, file_prefix);
    }

    cout << "Файл " << file_prefix << ": найдено графов - " << graph_count << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << " Тест" << std::endl;
    Graph testG("TestGraph.txt");
    find_all_graphs(testG, "test");

    cout << "Основа" << std::endl;
    Graph mainG("1000.csv");
    find_all_graphs(mainG, "main");
    return 0;
}