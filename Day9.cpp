#include "Day9.h"

void Day9::Knot::Move(Day9::Direction pDirection, uint32_t pAmount) {
	for (int i = 0; i < pAmount; ++i) {
		switch (pDirection) {
			case Direction::Up:
				position.y += 1;
				break;
			case Direction::Down:
				position.y -= 1;
				break;
			case Direction::Left:
				position.x -= 1;
				break;
			case Direction::Right:
				position.x += 1;
				break;
		}
		if (tail) {
			tail->Move(position);
		}
	}
}

void Day9::Knot::Move(Day9::Position pHeadPosition) {
	auto distanceX = pHeadPosition.x - position.x;
	auto distanceY = pHeadPosition.y - position.y;

	if (std::abs(distanceX) > 1 || std::abs(distanceY) > 1) {
		double dx = (double) distanceX / 2;
		double dy = (double) distanceY / 2;

		if (std::abs(dx) < 0.6) {
			dx *= 2;
		}
		if (std::abs(dy) < 0.6) {
			dy *= 2;
		}
		position.x += (int) dx;
		position.y += (int) dy;
	}

	visited.emplace(position);

	if (tail) {
		tail->Move(position);
	}
}

std::set<Day9::Position> Day9::Knot::GetVisited() {
	std::set<Position> res;
	if (tail) {
		res = tail->GetVisited();
	}

	for (const auto& item : visited) {
		res.emplace(item);
	}
	return res;
}

std::size_t Day9::Knot::GetLastVisitedAmount() {
	if (tail) {
		return tail->GetLastVisitedAmount();
	}
	return visited.size();
}
