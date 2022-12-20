#include "Day12.h"

#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <optional>

using namespace std::chrono_literals;

namespace Day12 {
    void DrawField(const std::vector<std::vector<Point>>& field) {
        for (const auto& elem: field) {
            for (const auto& item: elem) {
                std::string stepStr = std::to_string(item.Steps);
                std::string stepStr1;
                if (stepStr.size() == 1) {
                    stepStr1.append(" ").append(stepStr).append(" ");
                } else if (stepStr.size() == 2) {
                    stepStr1.append(stepStr).append(" ");
                } else {
                    stepStr1.append(stepStr);
                }
                std::string otherStr;
                otherStr.append(" . ");
                std::cout << (item.Visited ? stepStr1 : otherStr);
            }
            std::cout << std::endl;
        }
        std::cout << "---" << std::endl;
    }

    int RunField(const std::optional<Position>& pOverrideStartPosition = std::nullopt) {
        std::ifstream inputFile("inputs/12.txt");

        if (inputFile.is_open()) {
            std::string line;

            std::vector<std::vector<Point>> field;
            std::vector<Position> queue;
            Position finish;

            if (pOverrideStartPosition) {
                auto val = pOverrideStartPosition.value();
                queue.emplace_back(val.x, val.y);
            }

            for (int i = 0; std::getline(inputFile, line); ++i) {
                std::vector<Point>& val = field.emplace_back();
                for (int j = 0; const auto& elem: line) {
                    Point& point = val.emplace_back(elem);
                    if (elem == 'S') {
                        point.Value = 'a';
                        point.Visited = true;
                        if (!pOverrideStartPosition) {
                            queue.emplace_back(i, j);
                        }
                    }
                    if (elem == 'E') {
                        point.Value = 'z';
                        finish.x = i;
                        finish.y = j;
                    }
                    ++j;
                }
            }

            int a = 0;
            while (!queue.empty()) {
                auto elem = queue.front();
                queue.erase(queue.begin());

                const Point& point = field[elem.x][elem.y];

                auto visit = [&field, &point, &queue, &finish](const Position& visitPosition) {
                    if (visitPosition.x >= 0 && visitPosition.x <= field.size() - 1 && visitPosition.y >= 0 &&
                        visitPosition.y <= field[visitPosition.x].size() - 1) {
                        Point& visitPoint = field[visitPosition.x][visitPosition.y];
                        if (!visitPoint.Visited && visitPoint.Value <= point.Value + 1) {
                            visitPoint.Visited = true;
                            visitPoint.Steps = point.Steps + 1;
                            queue.emplace_back(visitPosition.x, visitPosition.y);

                            if (visitPosition == finish) {
                                queue.clear();
                            }
                        }
                    }
                };

                // up
                visit({elem.x - 1, elem.y});
                // down
                visit({elem.x + 1, elem.y});
                // left
                visit({elem.x, elem.y - 1});
                // right
                visit({elem.x, elem.y + 1});

                ++a;
            }
            inputFile.close();

//            DrawField(field);

            return field[finish.x][finish.y].Steps;
        }
        return 100000;
    }
}

void Day12::Day12() {
    auto start = std::chrono::steady_clock::now();

    std::ifstream inputFile("inputs/12.txt");

    std::vector<Position> startingPositions;

    if (inputFile.is_open()) {
        std::string line;

        for (int i = 0; std::getline(inputFile, line); ++i) {
            for (int j = 0; const auto& elem: line) {
                if (elem == 'a') {
                    startingPositions.emplace_back(i, j);
                }
            }
        }
    }
    inputFile.close();

    int res1 = RunField();
    int res2 = res1;

    for (const auto& startingPosition: startingPositions) {
        int res = RunField(startingPosition);
        if (res > 0) {
            res2 = std::min(res, res2);
        }
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "Result Day 12 Part 1: " << res1 << std::endl;
    std::cout << "Result Day 12 Part 2: " << res2 << std::endl;

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time elapsed: " << elapsed << std::endl;
}
