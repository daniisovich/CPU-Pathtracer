#pragma once

#include "ray.h"
#include "vec3.h"


class Lightsource {

public:
	virtual const Ray lightRay(const Vec3& position) const = 0;

};