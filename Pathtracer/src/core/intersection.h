#pragma once

#include "scene/material/material.h"
class Scene;



class Intersection {

public:

	Intersection(float t, const Vec3& position, const Vec3& ray_direction, const Vec3& out_normal, const std::shared_ptr<Material> material);

	inline bool front_face() const { return m_front_face; }
	inline float t() const { return m_t; }
	inline Vec3 position() const { return m_position; }
	inline Vec3 normal() const { return m_normal; }
	inline std::shared_ptr<Material> material() const { return m_material; }

private:

	void set_normal(const Vec3& ray_direction, const Vec3& out_normal);

	bool m_front_face{ true };
	float m_t{ 0.0f };
	Vec3 m_position, m_normal;
	std::shared_ptr<Material> m_material;

};