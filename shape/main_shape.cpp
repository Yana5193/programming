#include <iostream>
#include <vector>
#include <iomanip> 
#include <fstream>
#include <string>
#include <queue>
#include "shape.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	vector<Shape*> shapes;

	shapes.push_back(new Circle({ 0, 0 }, 2.0));
	shapes.push_back(new Ellips({ 0, 0 }, 5.0, 3.0));
	shapes.push_back(new Triangle({ 0, 0 }, { 10, 0 }, { 5, 10 }));
	shapes.push_back(new Rectangle({ 0, 0 }, { 4, 0 }, { 4, 4 }, { 0, 4 }));
	shapes.push_back(new Polygon("granitsy-uchastka2.txt"));

	double totalArea = 0.0;

	cout << fixed << setprecision(2);
	cout << "Фигуры " << endl;

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->name();
		double curArea = shapes[i]->calc_area();
		cout << "   Площадь: " << curArea << endl;
		cout << "   Периметр: " << shapes[i]->calc_perimeter() << endl;
		totalArea += curArea;
	}
	cout << "Сумма площадей: " << totalArea << endl;
	for (int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}


	vector<string>grid(200);
	ifstream inputFile("input2.dat");
	for (int i = 0; i < 200; i++) {
		getline(inputFile, grid[i]);
	}
	vector<vector<bool>> visited(200, vector<bool>(200, false));
	int count_rect = 0;
	int count_circle = 0;
	int count_noise = 0; //каракули
	int count_triangle = 0;

	double rect_area_sum = 0.0;
	double circle_area_sum = 0.0;
	double tri_area_sum = 0.0;

	int dr[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
	int dc[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

	for (int r = 0; r < 200; r++) {
		for (int c = 0; c < 200; c++) {
			if (grid[r][c] == '1' && !visited[r][c]) {
				vector<pair<int, int>> comp;
				queue<pair<int, int>> q;
				q.push({ r,c });
				visited[r][c] = true;
				while (!q.empty()) { //пока не пустая
					pair<int, int> curr = q.front();//берем координаты из самого начала очереди
					q.pop();
					comp.push_back(curr);
					for (int i = 0; i < 8; i++) {
						int new_row = curr.first + dr[i];
						int new_col = curr.second + dc[i];
						if (new_row >= 0 && new_row < 200 && new_col >= 0 && new_col < 200) {
							if (grid[new_row][new_col] == '1' && !visited[new_row][new_col]) {
								visited[new_row][new_col] = true;
								q.push({ new_row, new_col });
							}
						}

					}
				}
				if (comp.size() < 7) {
					count_noise++;
				}
				else {
					int min_r = 200, max_r = 0, min_c = 200, max_c = 0;
					for (auto& p : comp) {
						if (p.first < min_r) min_r = p.first;
						if (p.first > max_r) max_r = p.first;
						if (p.second < min_c) min_c = p.second;
						if (p.second > max_c) max_c = p.second;
					}

					double w = max_c - min_c + 1;
					double h = max_r - min_r + 1;
					double fill_ratio = (double)comp.size() / (w * h);

					if (fill_ratio > 0.9) {
						count_rect++;
						rect_area_sum += comp.size();
					}
					else if (fill_ratio > 0.65) {
						count_circle++;
						circle_area_sum += comp.size();
					}
					else {
						count_triangle++;
						tri_area_sum += comp.size();
					}
				}



			}

		}
	}
	ofstream outfile("output.txt");
	if (outfile.is_open()) {
		outfile << "Rectangle = " << count_rect << "\n";
		outfile << "Circle = " << count_circle << "\n";
		outfile << "Triangle = " << count_triangle << "\n";
		outfile << "Noise = " << count_noise << "\n";
		outfile.close();
	}

	cout << "Прямоугольников: " << count_rect << " (Суммарная площадь: " << rect_area_sum << ")" << endl;
	cout << "Кругов:          " << count_circle << " (Суммарная площадь: " << circle_area_sum << ")" << endl;
	cout << "Треугольников:   " << count_triangle << " (Суммарная площадь: " << tri_area_sum << ")" << endl;
	cout << "Каракули:" << count_noise << endl;

	shapes.clear();
	return 0;
}