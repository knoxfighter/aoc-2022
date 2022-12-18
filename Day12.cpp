#include "Day12.h"

#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>

void Day12::Day12() {
	std::ifstream inputFile("inputs/12.txt");

	auto start = std::chrono::steady_clock::now();

	if (inputFile.is_open()) {
		std::string line;

		std::vector<std::vector<Point>> field;
		std::vector<Position> queue;

		for (int i = 0; std::getline(inputFile, line); ++i) {
			std::vector<Point>& val = field.emplace_back();
			for (int j = 0; const auto &elem : line) {
				Point& point = val.emplace_back(elem);
				if (elem == 'S') {
					point.Value = 'a';
					point.Visited = true;
					queue.emplace_back(i, j);
				}
				++j;
			}
		}

		while (!queue.empty()) {
			const auto& elem = queue.front();

			const Point& point = field[elem.x][elem.y];

			// up


			// down
			// left
			// right

			queue.erase(queue.begin());
		}
		inputFile.close();

		auto end = std::chrono::steady_clock::now();

		std::cout << "Result Day 12 Part 1: " << "???" << std::endl;

		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time elapsed: " << elapsed << std::endl;
	}
}
