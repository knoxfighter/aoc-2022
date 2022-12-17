#pragma once

#include <set>
#include <type_traits>
#include <string>
#include <memory>

namespace Day9 {
	/*
	 *  .....
	 *  .....
	 * y.....
	 *  x
	 */
	enum class Direction {
		Up    = 1 << 0,
		Down  = 1 << 1,
		Left  = 1 << 2,
		Right = 1 << 3
	};
	inline Direction fromInput(const std::string& pInput) {
		if (pInput == "U") return Direction::Up;
		if (pInput == "D") return Direction::Down;
		if (pInput == "R") return Direction::Right;
		if (pInput == "L") return Direction::Left;
		return Direction::Up;
	}

	struct Position {
		int x = 0;
		int y = 0;

		auto operator<=>(const Position&) const = default;
	};

	struct Knot {
		int index;
		Position position;
		std::set<Position> visited;
		std::shared_ptr<Knot> tail;

		// H 0
		// 1 1
		// ...
		// 9 9
		Knot(int pIndex = 0) : index(pIndex) {
			// 9 subknot + 1 headknot
			if (index < 9) {
				tail = std::make_shared<Knot>(index+1);
			}
			visited.emplace();
		}

		void Move(Direction pDirection, uint32_t pAmount);
		void Move(Position pHeadPosition);
		std::set<Position> GetVisited();
		std::size_t GetLastVisitedAmount();
	};
}
