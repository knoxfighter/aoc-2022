#pragma once

namespace Day12 {
	void Day12();

	struct Point {
		char Value;
		bool Visited = false;
		int Steps = 0;

		Point(char pValue) : Value(pValue) {}
	};
	struct Position {
		int x;
		int y;
	};
}
