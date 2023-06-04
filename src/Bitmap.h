#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <memory>

namespace caveofprogramming {

	class Bitmap
	{
	public:
		Bitmap(int, int);
		virtual ~Bitmap();
		bool write(std::string);
		void setPixel(int, int, uint8_t, uint8_t, uint8_t);
	private:
		int m_width{ 0 };
		int m_height{ 0 };
		std::unique_ptr<uint8_t[]> m_pPixels{ nullptr };
	};

}