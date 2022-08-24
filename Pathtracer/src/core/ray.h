#pragma once

#include "vec3.h"


class Ray {

public:

	Ray() = delete;
	Ray(const Vec3& origin, const Vec3& direction);
	Ray(const Ray& other);

	Vec3 point(float t) const;

	inline Vec3 origin() const { return m_origin; }
	inline Vec3 direction() const { return m_direction; }

private:

	Vec3 m_origin, m_direction;

};