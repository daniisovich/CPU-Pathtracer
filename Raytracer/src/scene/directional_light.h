#pragma once

#include "lightsource.h"


class DirectionalLight : Lightsource {

public:

	DirectionalLight(const Vec3& direction);

	const Ray lightRay(const Vec3& position) const override;

private:

	Vec3 m_direction;

};