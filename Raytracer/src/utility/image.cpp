#include "image.h"

#include <iostream>
#include <fstream>

#include <algorithm>

#include "../core/core.h"


Image::Image(int width, int height) : m_width{ width }, m_height{ height }, m_data(width * height, Vec3{}) {}

int Image::width() const { return m_width; }
int Image::height() const { return m_height; }

void Image::setPixel(int x, int y, const Vec3& color) {
	
	assertMessage(x >= 0 && x < m_width && y >= 0 && y < m_height, "Invalid coordinates");

	int flattened{ flattenIndex(x, y) };
	m_data[flattened] = color;

}

int Image::flattenIndex(int x, int y) const {
	return y * m_width + x;
}

void Image::writeToBMP(const std::string& filename, float gamma) const {

	std::ofstream output{ (filename + ".bmp").c_str(), std::ofstream::binary};
	if (!output.is_open()) {
		std::cerr << "File " << filename << " could not be opened" << std::endl;
		return;
	}

	const int components{ 3 };

	output.write("BM", 2);
	struct {
		uint32_t file_size{ 0 };
		uint32_t reserved{ 0 };
		uint32_t offset_data{ 54 };
	} file_header;
	file_header.file_size = 54 + m_width * m_height * components;
	const int file_header_size{ 4 + 4 + 4 };

	output.write((char*)&file_header, file_header_size);

	struct {
		uint32_t size{ 40 };
		int32_t width{ 0 };
		int32_t height{ 0 };
		uint16_t planes{ 1 };
		uint16_t bit_count{ 8 * components };
		uint32_t compression{ 0 };
		uint32_t size_image{ 0 };
		int32_t horizontal_resolution{ 11810 };
		int32_t vertical_resolution{ 11810 };
		uint32_t used_colors{ 0 };
		uint32_t important_colors{ 0 };
	} info_header;
	info_header.width = m_width;
	info_header.height = m_height;

	output.write((char*)&info_header, info_header.size);

	std::vector<uint8_t> pixel_data(m_width * m_height * components);
	for (size_t i{ 0 }; i < m_data.size(); ++i) {

		const Vec3 pixel_color{ 255 * Vec3::clamp(Vec3::gammaCorrection(m_data[i], gamma), 0.0f, 1.0f) };
		pixel_data[3 * i + 0] = uint8_t(pixel_color.b());
		pixel_data[3 * i + 1] = uint8_t(pixel_color.g());
		pixel_data[3 * i + 2] = uint8_t(pixel_color.r());

	}
	
	output.write((char*)pixel_data.data(), pixel_data.size());
	output.close();

}