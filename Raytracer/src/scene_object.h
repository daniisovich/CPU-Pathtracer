#pragma once

#include <optional>

#include "ray.h"


struct Hit {
	// TODO: temporary struct
	float t;
	Vec3 intersection;
	Vec3 normal;
	bool front_face;

	inline void set_normal(const Vec3& ray_direction, const Vec3& out_normal) {
		front_face = Vec3::dot(ray_direction, out_normal) < 0;
		normal = front_face ? out_normal : out_normal.invert();
	}
};

class SceneObject {

public:
	virtual const std::optional<Hit> intersect(const Ray& ray, float near, float far) const = 0;

};