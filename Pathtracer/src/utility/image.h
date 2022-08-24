#pragma once

#include "core/vec3.h"


class Image {

public:

	Image(int width, int height);

	inline int width() const { return m_width; }
	inline int height() const { return m_height; }

	void setPixel(int x, int y, const Vec3& color);

	void writeToBMP(const std::string& filename, float gamma) const;

private:

	int flattenIndex(int x, int y) const;

	int m_width, m_height;
	std::vector<Vec3> m_data;

};