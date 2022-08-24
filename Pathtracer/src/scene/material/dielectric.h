#pragma once

#include "material.h"


class Dielectric : public Material {

public:

	Dielectric(const Vec3& color, float refractive_index);
	virtual Ray scatter(const Ray& ray, const Intersection& intersection) const final override;

private:

	float m_refractive_index;

};