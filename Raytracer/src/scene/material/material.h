#pragma once

#include "../../core/ray.h"
#include "../../core/intersection.fwd.h"


class Material {

public:

	Material(const Vec3& color) : m_color{ color } {}
	virtual Ray scatter(const Ray& ray_direction, const Intersection& intersection) const = 0;
	inline virtual Vec3 color() const { return m_color; }

protected:

	Vec3 m_color;

};