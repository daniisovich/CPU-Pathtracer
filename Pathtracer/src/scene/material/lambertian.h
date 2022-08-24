#pragma once

#include "material.h"


class Lambertian : public Material {

public:

	Lambertian(const Vec3& color);
	virtual Ray scatter(const Ray& ray_direction, const Intersection& intersection) const final override;

};