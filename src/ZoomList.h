#pragma once
#include <vector>
#include "Zoom.h"
#include <utility>

namespace caveofprogramming {
	class ZoomList
	{
	public:
		ZoomList(int, int);
		void add(const Zoom&);
		std::pair<double, double> doZoom(int , int );
		void zoomListGetter();
		
	private:
		int m_width{ 0 };
		int m_height{ 0 };
		std::vector<Zoom> m_zooms;
		double m_xCenter{ 0 };
		double m_yCenter{ 0 };
		double m_scale{ 1.0f };
	};
}


