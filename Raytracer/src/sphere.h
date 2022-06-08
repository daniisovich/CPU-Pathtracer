#pragma once

#include "scene_object.h"
#include "vec3.h"



class Sphere : public SceneObject {

public:

	Sphere(const Vec3& center, float radius);

	const std::optional<Hit> intersect(const Ray& ray, float near, float far) const override;

private:

	const Hit getIntersection(const Ray& ray, float t) const;

	Vec3 m_center;
	float m_radius;

};