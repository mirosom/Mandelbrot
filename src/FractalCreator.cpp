#include "FractalCreator.h"
#include "Mandelbrot.h"
#include <cassert>

namespace caveofprogramming {

	FractalCreator::FractalCreator(int w, int h) :
		m_width(w),
		m_height(h),
		m_histogram(std::make_unique<int[]>(Mandelbrot::MAX_ITERATIONS)),
		m_fractal(std::make_unique<int[]>(static_cast<uint64_t>(m_width)* m_height)),
		m_bitmap(m_width, m_height),
		m_zoomList(m_width, m_height)
	{
		std::memset(m_histogram.get(), 0, Mandelbrot::MAX_ITERATIONS);
		std::memset(m_fractal.get(), 0, static_cast<uint64_t>(m_width)* m_height);
		m_zoomList.add(Zoom(400, 300, 0.005));
	}
	FractalCreator::~FractalCreator(){}
	void FractalCreator::calculateIteration() {

		for (int y{ 0 }; y < m_height; ++y) {
			for (int x{ 0 }; x < m_width; ++x) {
				auto coords = m_zoomList.doZoom(x, y);
				int iterations = Mandelbrot::getIterations(coords.first, coords.second);

				if (iterations != Mandelbrot::MAX_ITERATIONS) m_histogram[iterations]++;
				m_fractal[static_cast<uint64_t>(y) * m_width + x] = iterations;
			}
		}
	}

	void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
		m_ranges.push_back((int)(rangeEnd*Mandelbrot::MAX_ITERATIONS));
		m_colors.push_back(rgb);
		if (m_bGotFirstRange) {
			m_rangeTotals.push_back(0);
		}
		m_bGotFirstRange = true;
	}


	void FractalCreator::run(std::string s) {
		
		calculateIteration();
		calculateTotalIterations();
		calculateRangeTotals();
		drawFractal();

		writeBitmap(s);
	}

	void FractalCreator::calculateTotalIterations() {
		 m_total = std::accumulate(m_histogram.get(), m_histogram.get() + Mandelbrot::MAX_ITERATIONS, 0);
	}


	void FractalCreator::calculateRangeTotals() {
		int rangeIndex = 0;
		for (int i{ 0 }; i < Mandelbrot::MAX_ITERATIONS; ++i) {
			int pixels = m_histogram[i];
			if (i > m_ranges[rangeIndex + 1]) rangeIndex++;
			m_rangeTotals[rangeIndex] += pixels;
		}
	}

	void FractalCreator::drawFractal() {

		RGB startColor(0, 0, 20);
		RGB endColor(71, 71, 209);
		RGB colorDiff = endColor - startColor;
		RGB tempRGB = RGB(255, 0, 255);

		for (int y{ 0 }; y < m_height; ++y) {
			for (int x{ 0 }; x < m_width; ++x) {

				
				double hue = 0.0f;

				uint8_t red{ 0 };
				uint8_t green{ 0 };
				uint8_t blue{ 0 };

				int iter = m_fractal[static_cast<uint64_t>(y) * m_width + x];
				int range = getRange(iter);
				int rangeTotal = m_rangeTotals[range]; // 321.000 82.000 and 20.000 cca
				int rangeStart = m_ranges[range];

				RGB& startColor = m_colors[range];
				if (range != m_ranges.size())
					RGB& endColor = m_colors[range + 1];
				else
					RGB& endColor = tempRGB;

				colorDiff = endColor - startColor;

				// uint8_t color = (uint8_t)((double)iter / Mandelbrot::MAX_ITERATIONS * 256);
				
				if (iter != Mandelbrot::MAX_ITERATIONS) {
					int totalPixels = 0;

					for (int i{ rangeStart }; i < iter; ++i) 
						totalPixels += m_histogram[i];

					red = startColor.r + colorDiff.r*(double)totalPixels/rangeTotal;
					green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
					blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
				}


				m_bitmap.setPixel(x, y, red, green, blue);
			}
		}
	}
	
	int FractalCreator::getRange(int iterations) const {
		int range = 0;
		for (int i{ 1 }; i < m_ranges.size(); i++) {
			range = i;
			if (m_ranges[i] > iterations) {
				break;
			}
		}
		range--;
		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}

	
	void FractalCreator::addZoom(const Zoom& z){
		m_zoomList.add(z);
	}

	void FractalCreator::writeBitmap(std::string s) {
		m_bitmap.write(s);
	}



}
