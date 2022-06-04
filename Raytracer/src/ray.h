#pragma once

#include "vec3.h"


class Ray {

public:

	Ray() = delete;
	Ray(const Vec3& origin, const Vec3& direction);
	Ray(const Ray& other);

	Vec3 point(float t) const;

	const Vec3 origin() const;
	const Vec3 direction() const;

private:
	Vec3 m_origin, m_direction;

};