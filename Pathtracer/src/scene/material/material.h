#pragma once

#include "core/ray.h"
class Intersection;


class Material {

public:

	Material(const Vec3& color) : 
		m_color{ color } 
	{}

	virtual Ray scatter(const Ray& ray_direction, const Intersection& intersection) const = 0;
	inline Vec3 color() const { return m_color; }

protected:

	Vec3 m_color;

};