#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include <cstring>
#include <numeric>
#include <cmath>
#include <vector>
#include "Zoom.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"
namespace caveofprogramming {
	class FractalCreator
	{
	public:
		
		FractalCreator(int, int);
		virtual ~FractalCreator();
		void addZoom(const Zoom&);
		void run(std::string);
		void addRange(double, const RGB&);

	private:
		void calculateIteration();
		void calculateTotalIterations();
		void calculateRangeTotals();
		void drawFractal();
		void writeBitmap(std::string);
		int getRange(int iterations) const; 

	private:
		int m_width{ 0 };
		int m_height{ 0 };
		std::unique_ptr<int[]> m_histogram{ nullptr };
		std::unique_ptr<int[]> m_fractal{ nullptr };
		Bitmap m_bitmap;
		ZoomList m_zoomList;
		int m_total{ 0 };
		std::vector<int> m_ranges;
		std::vector<RGB> m_colors;
		std::vector<int> m_rangeTotals;
		bool m_bGotFirstRange{ false };
	};

}