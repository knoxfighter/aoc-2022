#include "Day11.h"
#include "Helper.h"

#include <fstream>
#include <chrono>
#include <string>
#include <iostream>

namespace Day11 {
	uint64_t CalculateMonkeyBusiness() {
		// get all monkey inspected counts
		std::vector<uint64_t> counts;
		counts.reserve(monkeys.size());
		for (const auto& monkey: monkeys) {
			counts.push_back(monkey.GetInspectedCount());
		}

		std::ranges::sort(counts, [](const auto& a, const auto& b) { return a > b; });

		return counts[0] * counts[1];
	}
}

void Day11::Day11() {
	std::ifstream inputFile("inputs/11.txt");

	auto start = std::chrono::steady_clock::now();

	if (inputFile.is_open()) {
		std::string line;

		{
			Monkey* monkey = nullptr;

			while (std::getline(inputFile, line)) {
				trimLeft(line);
				if (line.starts_with("Monkey")) {
					monkey = &monkeys.emplace_back();
				} else if (line.starts_with("Starting")) {
					monkey->ParseItems(line);
				} else if (line.starts_with("Operation")) {
					monkey->ParseOperation(line);
				} else if (line.starts_with("Test")) {
					monkey->ParseTest(line);
				} else if (line.starts_with("If")) {
					monkey->ParseTarget(line);
				}
			}
			inputFile.close();
		}

		// calculate kgV (kleinster gemeinsamer Vielfache) of all monkey testvalues
		for (const auto& monkey : monkeys) {
			MaxTestValue *= monkey.mTestValue;
		}

		// run 20/10000 full rounds
		for (int i = 0; i < 10000; ++i) {
			for (auto& monkey: monkeys) {
				monkey.Round();
			}
		}

		auto end = std::chrono::steady_clock::now();

		std::cout << "Result Day 11: " << CalculateMonkeyBusiness() << std::endl;

		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time elapsed: " << elapsed << std::endl;
	}
}

Day11::Operation::Operation(Operator pOperator, const std::string& pPre, const std::string& pPost) : mOperator(pOperator) {
	if (pPre == "old") {
		mPreValue = std::make_unique<DirectValue>();
	} else {
		mPreValue = std::make_unique<LiteralValue>(std::stoull(pPre));
	}
	if (pPost == "old") {
		mPostValue = std::make_unique<DirectValue>();
	} else {
		mPostValue = std::make_unique<LiteralValue>(std::stoull(pPost));
	}
}

void Day11::Monkey::ParseItems(const std::string& pLine) {
	auto splitted = split(pLine, ' ');

	for (int i = 2; i < splitted.size(); ++i) {
		mItems.emplace_back(std::stoull(splitted[i]));
	}
}

void Day11::Monkey::ParseOperation(const std::string& pLine) {
	auto splitted = split(pLine, ' ');

	mOperation.emplace(static_cast<Operator>(splitted[4][0]), splitted[3], splitted[5]);
}

void Day11::Monkey::ParseTest(const std::string& pLine) {
	auto splitted = split(pLine, ' ');

	mTestValue = std::stoull(splitted[3]);
}

void Day11::Monkey::ParseTarget(const std::string& pLine) {
	auto splitted = split(pLine, ' ');

	if (splitted[1] == "true:") {
		mTrueTarget = std::stoull(splitted[5]);
	} else {
		mFalseTarget = std::stoull(splitted[5]);
	}
}

void Day11::Monkey::Round() {
	for (auto& item : mItems) {
		// worry level changes based on Operaion
		item.WorryLevel = mOperation->operator()(item.WorryLevel);

		// Monkey gets bored with item, you find that good
		// FIXME: this is disabled, cause we calculate part 2
//		item.WorryLevel /= 3;

		// keep the worryLevel low
		item.WorryLevel %= MaxTestValue;

		// divisable?
		if (item.WorryLevel % mTestValue == 0) {
			// true
			monkeys[mTrueTarget].CatchItem(item);
		} else {
			// false
			monkeys[mFalseTarget].CatchItem(item);
		}
	}

	mInspectedCount += mItems.size();
	mItems.clear();
}

void Day11::Monkey::CatchItem(const Item& pItem) {
	mItems.push_back(pItem);
}
