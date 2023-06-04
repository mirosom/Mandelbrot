#pragma once



namespace caveofprogramming {
	struct RGB
	{
		double r, g, b;
		RGB(double, double, double);
		friend RGB operator-(const RGB&, const RGB&);
	};
}


