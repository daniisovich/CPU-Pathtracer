#pragma once

#include "../../core/ray.h"


class Lightsource {

public:

	Lightsource(const Vec3& color) : m_color{ color } {}
	virtual const Ray lightRay(const Vec3& position) const = 0;

	Vec3 color() const { return m_color; }

protected:
	Vec3 m_color;

};