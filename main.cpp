#include <iostream>
#include <cxxopts.hpp>
#include <fstream>
#include <filesystem>
#include <array>
#include <deque>
#include <ranges>

#include "Helper.h"
#include "FileEntry.h"
#include "Day9.h"
#include "Day11.h"
#include "Day12.h"

void Day1();
void Day2();
void Day3();
void Day4();
void Day5();
void Day6();
void Day7();
void Day8();
void Day9Func();
void Day10();

int main(int argc, char** argv) {
    cxxopts::Options options("test", "A brief description");

    options.add_options()
            ("d,day", "The day of the challenge", cxxopts::value<int>()->default_value("0"))
            ("h,help", "Print usage")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    auto day = result["day"].as<int>();

    switch (day) {
        case 0: // run all days
			Day1();
			Day2();
			Day3();
			Day4();
			Day5();
			Day6();
			Day7();
			Day8();
			Day9Func();
			Day10();
			Day11::Day11();
			Day12::Day12();
            break;
        case 1:
			Day1();
            break;
        case 2:
			Day2();
            break;
        case 3:
			Day3();
            break;
        case 4:
			Day4();
            break;
        case 5:
			Day5();
            break;
        case 6:
			Day6();
            break;
        case 7:
			Day7();
            break;
		case 8:
			Day8();
			break;
		case 9:
			Day9Func();
			break;
		case 10:
			Day10();
			break;
		case 11:
			Day11::Day11();
			break;
		case 12:
			Day12::Day12();
			break;
    }

    return 0;
}

void Day1() {
    std::ifstream inputFile("inputs/1.txt");

    auto start = std::chrono::steady_clock::now();

    std::vector<uint64_t> elves;
    elves.emplace_back();

    if (inputFile.is_open()) {
        std::string line;
        int i = 0;
        while (std::getline(inputFile, line)) {
            if (line.empty()) {
                // new person
                ++i;
                elves.emplace_back();
            } else {
                // more food
                elves[i] += std::stoull(line);
            }
        }
        inputFile.close();

        std::ranges::sort(elves, [](const auto& a, const auto& b) { return a > b; });

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 1 Part 1: " << elves[0] << std::endl;

        // Part 2
        std::cout << "Result Day 1 Part 2: " << elves[0] + elves[1] + elves[2] << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day2() {
    std::ifstream inputFile("inputs/2.txt");

    auto start = std::chrono::steady_clock::now();

    uint64_t num1 = 0;
    uint64_t num2 = 0;

    if (inputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            std::vector<std::string> vals = split(line, ' ');

            // A = Rock
            // B = Paper
            // C = Scissors
            // X = Rock
            // Y = Paper
            // Z = Scissors

            if (vals[0] == "A" && vals[1] == "X") num1 += 3+1;
            if (vals[0] == "A" && vals[1] == "Y") num1 += 6+2;
            if (vals[0] == "A" && vals[1] == "Z") num1 += 0+3;
            if (vals[0] == "B" && vals[1] == "X") num1 += 0+1;
            if (vals[0] == "B" && vals[1] == "Y") num1 += 3+2;
            if (vals[0] == "B" && vals[1] == "Z") num1 += 6+3;
            if (vals[0] == "C" && vals[1] == "X") num1 += 6+1;
            if (vals[0] == "C" && vals[1] == "Y") num1 += 0+2;
            if (vals[0] == "C" && vals[1] == "Z") num1 += 3+3;

            if (vals[0] == "A" && vals[1] == "X") num2 += 0+3; // loose - C
            if (vals[0] == "A" && vals[1] == "Y") num2 += 3+1; // draw - A
            if (vals[0] == "A" && vals[1] == "Z") num2 += 6+2; // win - B
            if (vals[0] == "B" && vals[1] == "X") num2 += 0+1; // loose - A
            if (vals[0] == "B" && vals[1] == "Y") num2 += 3+2; // draw - B
            if (vals[0] == "B" && vals[1] == "Z") num2 += 6+3; // win - C
            if (vals[0] == "C" && vals[1] == "X") num2 += 0+2; // loose - B
            if (vals[0] == "C" && vals[1] == "Y") num2 += 3+3; // draw - C
            if (vals[0] == "C" && vals[1] == "Z") num2 += 6+1; // win - A
        }
        inputFile.close();

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 2 Part 1: " << num1 << std::endl;
        std::cout << "Result Day 2 Part 2: " << num2 << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day3() {
    std::ifstream inputFile("inputs/3.txt");

    auto start = std::chrono::steady_clock::now();

    if (inputFile.is_open()) {
        std::string line;
        std::string doubledChars;
        std::string elfGroups;

        std::string values;

        uint64_t i = 0;
        while (std::getline(inputFile, line)) {
            std::string firstPack = line.substr(0, line.length()/2);
            std::string secondPack = line.substr(line.length()/2);

            for (const auto &item : firstPack) {
                if (secondPack.contains(item)) {
                    doubledChars.append(1, item);
                    break;
                }
            }

            if (i % 3 == 0) {
                values = line;
            } else if (i % 3 == 1) {
                std::string newValues;
                for (const auto &item : line) {
                    if (values.contains(item)) {
                        newValues.append(1, item);
                    }
                }
                values = newValues;
            } else if (i % 3 == 2) {
                for (const auto &item : line) {
                    if (values.contains(item)) {
                        elfGroups.append(1, item);
                        break;
                    }
                }
            }

            ++i;
        }
        inputFile.close();

        uint64_t res1 = 0;
        for (const auto &item : doubledChars) {
            if (std::isupper(item)) {
                res1 += item - 'A' + 27;
            } else {
                res1 += item - 'a' + 1;
            }
        }

        uint64_t res2 = 0;
        for (const auto &item : elfGroups) {
            if (std::isupper(item)) {
                res2 += item - 'A' + 27;
            } else {
                res2 += item - 'a' + 1;
            }
        }

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 2 Part 1: " << res1 << std::endl;
        std::cout << "Result Day 2 Part 2: " << res2 << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day4() {
    std::ifstream inputFile("inputs/4.txt");

    auto start = std::chrono::steady_clock::now();

    if (inputFile.is_open()) {
        std::string line;

        uint64_t res1 = 0;
        uint64_t res2 = 0;

        while (std::getline(inputFile, line)) {
            auto sections = split(line, ',');
            auto section1 = split(sections[0], '-');
            auto section2 = split(sections[1], '-');

            auto section1_1 = std::stoull(section1[0]);
            auto section1_2 = std::stoull(section1[1]);
            auto section2_1 = std::stoull(section2[0]);
            auto section2_2 = std::stoull(section2[1]);

            // 35-73,35-82
            // 2-8,3-7 -> 2 <= 3 && 8 >= 7 -> true
            // 6-6,4-6 -> 4 <= 6 && 6 >= 6 -> true
            if (
                    (section1_1 <= section2_1 && section1_2 >= section2_2)
                    || (section2_1 <= section1_1 && section2_2 >= section1_2)
                    ) {
                ++res1;
            }


            // 2-4,6-8
            // 2-3,4-5
            // 5-7,7-9
            // 2-8,3-7
            // 6-6,4-6
            // 2-6,4-8
            if ((section1_1 >= section2_1 && section1_1 <= section2_1) || (section1_2 >= section2_1 && section1_2 <= section2_2)
            || (section2_1 >= section1_1 && section2_1 <= section1_2) || (section2_2 >= section1_1 && section2_2 <= section1_2)) {
                ++res2;
            }
        }
        inputFile.close();

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 4 Part 1: " << res1 << std::endl;
        std::cout << "Result Day 4 Part 2: " << res2 << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day5() {
    std::ifstream inputFile("inputs/5.txt", std::ios::binary);

    auto start = std::chrono::steady_clock::now();

    if (inputFile.is_open()) {
        constexpr int STACK_NUM = 9;
        std::array<std::deque<char>, STACK_NUM> lager;

        std::string line;

        int status = 0;
        while(std::getline(inputFile, line)) {
            if (status == 0) {
                for (int j = 0, k = 1; j < STACK_NUM; ++j, k += 4) {
                    if (line[k] == '1') {
                        status = 1;
                        break;
                    }
                    if (line[k] == ' ') {
                        continue;
                    }

                    lager[j].push_front(line[k]);
                }
            } else {
                if (line.empty()) continue;

                auto commandLine = split(line, ' ');
                int amount = std::stoi(commandLine[1]);
                int from = std::stoi(commandLine[3]) - 1;
                int to = std::stoi(commandLine[5]) - 1;

                // Part 1
//                for (int i = 0; i < amount; ++i) {
//                    auto back = lager[from].back();
//                    lager[from].pop_back();
//                    lager[to].push_back(back);
//                }

                // Part 2
                std::vector<char> CrateMover9001;
                for (int i = 0; i < amount; ++i) {
                    auto back = lager[from].back();
                    lager[from].pop_back();
                    CrateMover9001.push_back(back);
                }

                for (auto& item : CrateMover9001 | std::views::reverse) {
                    lager[to].push_back(item);
                }
            }
        }
        inputFile.close();

        std::string res1;
        for (int i = 0; i < STACK_NUM; ++i) {
            res1.append(1, lager[i].back());
        }

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 5: " << res1 << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day6() {
    std::ifstream inputFile("inputs/6.txt");

    auto start = std::chrono::steady_clock::now();

    if (inputFile.is_open()) {
        std::string line;

        uint64_t res1 = 0;
        uint64_t res2 = 0;

        auto findFirstDistinctAmount = [](const std::string& line, int amount){
            for (int i = 0; true; ++i) {
                std::string found;

                for (int j = i; j < i + amount; ++j) {
                    char c = line[j];
                    if (found.contains(c)) break;
                    found.append(1, c);
                }
                if (found.size() == amount) {
                    return i + amount;
                }
            }
        };

        while (std::getline(inputFile, line)) {
            res1 = findFirstDistinctAmount(line, 4);
            res2 = findFirstDistinctAmount(line, 14);

            // there is only one line
            break;
        }
        inputFile.close();

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 6 Part 1: " << res1 << std::endl;
        std::cout << "Result Day 6 Part 2: " << res2 << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day7() {
    std::ifstream inputFile("inputs/7.txt");

    auto start = std::chrono::steady_clock::now();

    if (inputFile.is_open()) {
        std::string line;

		std::shared_ptr<FileEntry> rootFile = std::make_shared<FileEntry>(FileEntry::Type::DIR, "/", 0);
		std::vector<std::shared_ptr<FileEntry>> path;
		std::shared_ptr<FileEntry> currentElem = rootFile;

        while (std::getline(inputFile, line)) {
			auto splitted = split(line, ' ');
			if (splitted[0] == "$") {
				// command
				if (splitted[1] == "cd") {
					if (splitted[2] == "/") {
						// move to root
						currentElem = rootFile;
						path.clear();
					} else if (splitted[2] == "..") {
						// move one up
						currentElem = path.back();
						path.pop_back();
					} else {
						// move into subdir
						path.emplace_back(currentElem);
						currentElem = currentElem->GetElement(splitted[2]);
					}
				}
			} else if (splitted[0] == "dir") {
				// directory definition
				currentElem->AddElement(FileEntry::Type::DIR, splitted[1]);
			} else {
				// file definition
				currentElem->AddElement(FileEntry::Type::FILE, splitted[1], std::stoull(splitted[0]));
			}
        }
        inputFile.close();

		uint64_t usedSpace = rootFile->CalculateSizes();
		uint64_t res1 = rootFile->GetSmallSizes();

		constexpr uint64_t MAX_SPACE = 70000000;
		constexpr uint64_t UPDATE_SPACE = 30000000;

		uint64_t neededSpace = UPDATE_SPACE - (MAX_SPACE - usedSpace);

		uint64_t smallestDirSize = UPDATE_SPACE;
		rootFile->GetSmallestDirSize(smallestDirSize, neededSpace);

        auto end = std::chrono::steady_clock::now();

        std::cout << "Result Day 7 Part 1: " << res1 << std::endl;
        std::cout << "Result Day 7 Part 2: " << smallestDirSize << std::endl;

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time elapsed: " << elapsed << std::endl;
    }
}

void Day8() {
	std::ifstream inputFile("inputs/8.txt");

	auto start = std::chrono::steady_clock::now();

	if (inputFile.is_open()) {
		std::string line;

		std::vector<std::vector<int>> field;

		while (std::getline(inputFile, line)) {
			auto& current = field.emplace_back();
			for (const auto &item : line) {
				current.emplace_back(item - '0');
			}
		}
		inputFile.close();

		auto VisibleCheck = [field](uint8_t current, std::size_t x, std::size_t y, int8_t direction, uint8_t& visionRange, bool leftRight = false) -> bool {
			std::size_t a = x;
			std::size_t b = y;
			if (leftRight) {
				a = y;
				b = x;
			}

			if (a == 0 || a == 98) {
				return true;
			}
			a += direction;
			visionRange = 1;

			while (true) {
				if (field[leftRight?b:a][leftRight?a:b] >= current) {
					return false;
				}

				if (a == 0 || a == 98 /*last index*/) {
					return true;
				}

				a += direction;
				++visionRange;
			}
		};

		uint64_t res1 = 0;
		uint64_t res2 = 0;
		for (std::size_t x = 0; x < field.size(); ++x) {
			for (std::size_t y = 0; y < field[x].size(); ++y) {
				uint8_t current = field[x][y];
				bool visible = false;
				uint8_t viewDistance = 0;
				uint64_t scenicScore = 1;

				// check upwards
				if (VisibleCheck(current, x, y, -1, viewDistance)) {
					visible = true;
				}
				scenicScore *= viewDistance;
				viewDistance = 0;

				// check downwards
				if (VisibleCheck(current, x, y, 1, viewDistance)) {
					visible = true;
				}
				scenicScore *= viewDistance;
				viewDistance = 0;

				// check left
				if (VisibleCheck(current, x, y, -1, viewDistance, true)) {
					visible = true;
				}
				scenicScore *= viewDistance;
				viewDistance = 0;

				// check right
				if (VisibleCheck(current, x, y, 1, viewDistance, true)) {
					visible = true;
				}
				scenicScore *= viewDistance;
				viewDistance = 0;

				if (visible) {
					++res1;
				}
				if (res2 < scenicScore) {
					res2 = scenicScore;
				}
			}
		}

		auto end = std::chrono::steady_clock::now();

		std::cout << "Result Day 7 Part 1: " << res1 << std::endl;
		std::cout << "Result Day 7 Part 2: " << res2 << std::endl;

		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time elapsed: " << elapsed << std::endl;
	}
}

void Day9Func() {
	using namespace Day9;

	std::ifstream inputFile("inputs/9.txt");

	auto start = std::chrono::steady_clock::now();

	if (inputFile.is_open()) {
		std::string line;

		Knot headKnot;

		while (std::getline(inputFile, line)) {
			auto splitted = split(line, ' ');

			Direction direction = fromInput(splitted[0]);
			int amount = std::stoi(splitted[1]);
			headKnot.Move(direction, amount);
		}
		inputFile.close();

		auto end = std::chrono::steady_clock::now();

		std::cout << "Result Day 9 Part 1: " << headKnot.tail->visited.size() << std::endl;
		std::cout << "Result Day 9 Funfact: Visited positions overall: " << headKnot.tail->visited.size() << std::endl;
		std::cout << "Result Day 9 Part 2: " << headKnot.GetLastVisitedAmount() << std::endl;

		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time elapsed: " << elapsed << std::endl;
	}
}

void Day10() {
	std::ifstream inputFile("inputs/10.txt");

	auto start = std::chrono::steady_clock::now();

	if (inputFile.is_open()) {
		std::vector<std::string> currentCommand;
		std::array<std::array<bool, 40>, 6> displayPixels{};
		uint32_t countVar = 0;
		int64_t X = 1;
		int64_t res1 = 0;

		for (int cycle = 0; cycle < 240; ++cycle) {
			if (cycle % 40 == 19) {
				res1 += (cycle+1) * X;
			}

			// get vertical pos
			int verticalPos = cycle / 40;
			// get horizontal pos
			int horizontalPos = cycle % 40;
			// check if horizontalPos has to be lit
			if (horizontalPos >= X-1 && horizontalPos <= X+1) {
				displayPixels[verticalPos][horizontalPos] = true;
			}

			if (countVar == 0) {
				std::string line;
				if (!std::getline(inputFile, line))
					break;
				currentCommand = split(line, ' ');

				if (currentCommand[0] == "noop") {
					countVar = 1;
				}
				if (currentCommand[0] == "addx") {
					countVar = 2;
				}
			}

			--countVar;
			if (countVar == 0) {
				if (currentCommand[0] == "addx") {
					X += std::stoi(currentCommand[1]);
				}
			}
		}

		inputFile.close();

		auto end = std::chrono::steady_clock::now();

		std::cout << "Result Day 10 Part 1: " << res1 << std::endl;
		std::cout << "Result Day 10 Part 2: " << std::endl;
		for (const auto &row : displayPixels) {
			for (const auto &pixel : row) {
				if (pixel) {
					std::cout << "#";
				} else {
					std::cout << ".";
				}
			}
			std::cout << std::endl;
		}

		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time elapsed: " << elapsed << std::endl;
	}
}
