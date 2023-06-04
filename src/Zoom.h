#pragma once




namespace caveofprogramming {
	struct Zoom {
		int x{ 0 };
		int y{ 0 };
		double scale{ 0.0f };

		Zoom(int x, int y, double s) : x(x), y(y), scale(s) {}

	};
}
