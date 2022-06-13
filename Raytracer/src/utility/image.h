#pragma once

#include <vector>

#include "../core/vec3.h"


class Image {

public:

	Image(int width, int height);

	int width() const;
	int height() const;

	void setPixel(int x, int y, const Vec3& color);

	void writeToBMP(const std::string& filename, float gamma) const;

private:

	int flattenIndex(int x, int y) const;

	int m_width, m_height;
	std::vector<Vec3> m_data;

};