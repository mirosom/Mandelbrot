#pragma once

#include <complex>

namespace caveofprogramming {
	class Mandelbrot
	{
	public:
		Mandelbrot();
		virtual ~Mandelbrot();
		static int getIterations(double, double); // takes the a and bi and counts z^2+c the number of iterations?
	
	public:
		static const int MAX_ITERATIONS = 500;	
	private:
	};

}