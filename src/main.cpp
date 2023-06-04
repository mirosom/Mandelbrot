/*******************************************************************************/
// Name:					main.cpp
// Author:					Miro Holec
// Based on lecture:		John Purcell
// Copyright:
// Description:				Mandelbrot fractal creator with zoom functionality
// Date:					Jun 03,2023
/*******************************************************************************/


#include <iostream>
#include "FractalCreator.h"


using namespace caveofprogramming;

int main() {

	FractalCreator fractalCreator(800, 600);

	fractalCreator.addRange(0.0f, RGB(0, 0, 0));
	fractalCreator.addRange(0.1f, RGB(77, 0, 153));
	fractalCreator.addRange(0.25f, RGB(255, 204, 0));
	fractalCreator.addRange(0.5f, RGB(255,0,102));
	fractalCreator.addRange(1.0f, RGB(255, 255, 204));



	//zoomList.add(Zoom(307, 189, 0.005)); zoomList.add(Zoom(447, 337, 0.005)); zoomList.add(Zoom(482, 161, 0.05));
	fractalCreator.addZoom(Zoom(377, 122, 0.05)); // 94
	fractalCreator.addZoom(Zoom(426, 257, 0.05)); // 94a
	fractalCreator.addZoom(Zoom(401, 239, 0.05)); // 94b
	fractalCreator.addZoom(Zoom(386, 324, 0.05));
	fractalCreator.run("test_104d.bmp");
	
	std::cout << "Finished\n";
}