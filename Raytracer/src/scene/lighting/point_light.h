#pragma once

#include "lightsource.h"


class PointLight : public Lightsource {

public:

	PointLight() = default;
	PointLight(const Vec3& position, const Vec3& color);

	const Ray lightRay(const Vec3& position) const override;

private:

	Vec3 m_position;

};