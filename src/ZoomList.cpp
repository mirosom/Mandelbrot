#include "ZoomList.h"
#include<iostream>

namespace caveofprogramming {
	ZoomList::ZoomList(int w,int h) : m_width(w), m_height(h) {}
	void ZoomList::add(const Zoom& z) {
		m_zooms.push_back(z);
		// populating the ZoomLists center and scale, from the last zoom
		
		m_xCenter += (z.x - m_width / 2.0) * m_scale;
		m_yCenter += (- z.y + m_height / 2.0) * m_scale;
		m_scale *= z.scale;
	}

	std::pair<double, double> ZoomList::doZoom(int x, int y) {
		double xFractal = (x- m_width/2.0)*m_scale+m_xCenter;
		double yFractal = (y-m_height/2.0)*m_scale+m_yCenter;
		return std::make_pair(xFractal, yFractal );
	}

}
