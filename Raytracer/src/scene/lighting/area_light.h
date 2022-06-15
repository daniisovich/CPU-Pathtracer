#pragma once

#include "lightsource.h"


class AreaLight : public Lightsource {

public:

	AreaLight() = default;
	AreaLight(const Vec3& position, float radius, const Vec3& color);

	const Ray lightRay(const Vec3& position) const override;

private:

	// for now area lightsources are spheres
	Vec3 m_position;
	float m_radius{ 1.0f };

};