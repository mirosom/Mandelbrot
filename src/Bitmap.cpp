#include <fstream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

namespace caveofprogramming {
	Bitmap::Bitmap(int w, int h): m_width(w), m_height(h), m_pPixels(std::make_unique<uint8_t[]>(w*h*3)) {
		std::memset(m_pPixels.get(), 0, static_cast<uint64_t>(w) * h * 3);
		//std::memset(&m_pPixels[0], 0, static_cast<uint64_t>(w) * h * 3);
	}
	Bitmap::~Bitmap() {}
	bool Bitmap::write(std::string s) {
		BitmapFileHeader fileHeader;
		BitmapInfoHeader infoHeader;
		fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + static_cast<uint64_t>(m_width) * m_height * 3;
		fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
		infoHeader.width = m_width;
		infoHeader.height = m_height;

		std::fstream file(s, std::ios::out | std::ios::binary);
		if(!file) return false;

		file.write((char*)&fileHeader, sizeof fileHeader);
		file.write((char*)&infoHeader, sizeof infoHeader);
		file.write((char*)m_pPixels.get(), static_cast<uint64_t>(m_width) * m_height * 3);

		file.close();
		if (!file) return false;

		return true;
	}
	void Bitmap::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
		uint8_t* pPixel = m_pPixels.get();
		pPixel += y * m_width * 3 + x*3; // array[height][width] array[300][400] = array +(300 * width + 400)
		// pPixel = pPixel + (y*m_width*3 + x*3)
		pPixel[0] = b;
		pPixel[1] = g;
		pPixel[2] = r;

	}
}
