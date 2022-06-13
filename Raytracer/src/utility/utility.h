#pragma once

#include <random>

#include "../core/vec3.h"


namespace utility {

	float randomScalar(float min = 0.0f, float max = 1.0f);
	Vec3 randomInSphere(float radius = 1.0f);
	Vec3 randomInHemisphere(const Vec3& normal);

	const float infinity{ std::numeric_limits<float>::infinity() };

	Vec3 brdfHemisphere(const Vec3& ray_direction, const Vec3& normal);

}