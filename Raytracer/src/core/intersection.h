#pragma once

#include "../scene/scene.fwd.h"
#include "../scene/material/material.h"




class Intersection {

public:

	Intersection(float t, const Vec3& position, const Vec3& ray_direction, const Vec3& out_normal, const std::shared_ptr<Material> material);

	Vec3 lighting(const Scene& scene, float epsilon) const;

	bool front_face() const;
	float t() const;
	Vec3 position() const;
	Vec3 normal() const;
	std::shared_ptr<Material> material() const;

private:

	void set_normal(const Vec3& ray_direction, const Vec3& out_normal);

	bool m_front_face{ true };
	float m_t{ 0.0f };
	Vec3 m_position, m_normal, m_view_dir;
	std::shared_ptr<Material> m_material;

};