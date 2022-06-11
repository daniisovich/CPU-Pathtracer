#pragma once

#include "../core/ray.h"
#include "../core/vec3.h"


class Lightsource {

public:
	virtual const Ray lightRay(const Vec3& position) const = 0;

};