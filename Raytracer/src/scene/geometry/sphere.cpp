#include "sphere.h"


const std::optional<std::pair<float, float>> solveQuadratic(float a, float half_b, float c);


Sphere::Sphere(const Vec3& center, float radius, const std::shared_ptr<Material>& material) : m_center{ center }, m_radius{ radius }, m_material{ material } { }

const std::optional<Intersection> Sphere::intersect(const Ray& ray, float near, float far) const {

	const Vec3 co{ ray.origin() - m_center };
	const float a{ ray.direction().sq_length() };
	const float half_b{ Vec3::dot(co, ray.direction()) };
	const float c{ co.sq_length() - m_radius * m_radius };

	const auto result = solveQuadratic(a, half_b, c);
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

const Intersection Sphere::getIntersection(const Ray& ray, float t) const {

	const Vec3 position{ ray.point(t) };
	const Vec3 out_normal{ Vec3::normalize(position - m_center) };
	Intersection intersection{ t, position, ray.direction(), out_normal, m_material };
	return intersection;

}

const std::optional<std::pair<float, float>> solveQuadratic(float a, float half_b, float c) {

	const float discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return {};
	if (discriminant == 0) return std::pair{ half_b / a, half_b / a };

	const float sqrt_disc{ sqrt(discriminant) };
	const float q = (half_b > 0) ? - half_b - sqrt_disc : - half_b + sqrt_disc;
	float t1{ q / a };
	float t2{ c / q };

	if (t1 > t2) std::swap(t1, t2);
	return std::pair{ t1, t2 };

}