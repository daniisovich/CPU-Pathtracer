#pragma once

#include "scene_object.h"


class Sphere : public SceneObject {

public:

	Sphere(const Vec3& center, float radius, const std::shared_ptr<Material>& material);
	const std::optional<Intersection> intersect(const Ray& ray, float near, float far) const final override;

private:

	const Intersection getIntersection(const Ray& ray, float t) const;

	Vec3 m_center;
	float m_radius;
	std::shared_ptr<Material> m_material;

};