#pragma once

#include "vec3.h"


class Material {

public:

	Material(const Vec3& color, float reflectiveness);

	const Vec3 color() const;
	float reflectiveness() const;

private:

	Vec3 m_color;
	float m_reflectiveness;

};