#pragma once

#include "lightsource.h"


class PointLight : Lightsource {

public:

	PointLight() = default;
	PointLight(const Vec3& position);

	const Ray lightRay(const Vec3& position) const override;

private:

	Vec3 m_position;

};