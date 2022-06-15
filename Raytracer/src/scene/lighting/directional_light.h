#pragma once

#include "lightsource.h"


class DirectionalLight : public Lightsource {

public:

	DirectionalLight(const Vec3& direction, const Vec3& color);

	const Ray lightRay(const Vec3& position) const override;

private:

	Vec3 m_direction;

};