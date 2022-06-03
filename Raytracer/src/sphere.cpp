#include "sphere.h"


const std::optional<std::pair<float, float>> solveQuadratic(const float& half_b, const float& c);


const std::optional<Hit> Sphere::intersect(const Ray& ray, float near, float far) const {

	const Vec3 oc{ ray.origin() - m_center };
	const float half_b{ Vec3::dot(oc, Vec3::normalize(ray.direction())) };
	const float c{ oc.sq_length() - m_radius * m_radius };

	const auto result = solveQuadratic(half_b, c);
	// ray doesn't hit object
	if (!result.has_value()) return {};
	const auto[t1, t2] = result.value();

	// ray starts before object
	if (t1 > near && t1 < far) 
		return getIntersection(ray, t1);

	// ray starts in object
	if (t2 > near && t2 < far) 
		return getIntersection(ray, t2);

	// ray starts after object
	return {};

}

const Hit Sphere::getIntersection(const Ray& ray, float t) const {
	const Vec3 intersection{ ray.point(t) };
	return Hit{ t, intersection, (m_center.invert() + intersection) / m_radius };
}

const std::optional<std::pair<float, float>> solveQuadratic(const float& half_b, const float& c) {

	const float discriminant = half_b * half_b - c;
	if (discriminant < 0) return {};
	if (discriminant == 0) return std::pair{ half_b, half_b };

	const float sqrt_disc{ sqrt(discriminant) };
	float t1 = (half_b > 0) ? -half_b - sqrt_disc : -half_b + sqrt_disc;
	float t2{ c / t1 };

	if (t1 > t2) std::swap(t1, t2);
	return std::pair{ t1, t2 };

}