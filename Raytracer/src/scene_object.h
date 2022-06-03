#pragma once

#include <optional>

#include "ray.h"


struct Hit {
	// TODO: temporary struct
	float t;
	Vec3 intersection;
	Vec3 normal;
};

class SceneObject {

public:
	virtual const std::optional<Hit> intersect(const Ray& ray, float near, float far) const = 0;

};