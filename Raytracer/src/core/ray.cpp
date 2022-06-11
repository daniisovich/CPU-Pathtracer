#include "ray.h"


Ray::Ray(const Vec3& origin, const Vec3& direction) : m_origin{ origin }, m_direction{ direction } {}
Ray::Ray(const Ray& other) : m_origin{ other.m_origin }, m_direction{ m_direction } {}

Vec3 Ray::point(float t) const {
	return m_origin + t * m_direction;
}

const Vec3 Ray::origin() const { return m_origin; }
const Vec3 Ray::direction() const { return m_direction; }