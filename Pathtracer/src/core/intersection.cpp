#include "precompiled/pch.h"
#pragma hdrstop

#include "intersection.h"
#include "scene/scene.h"


Intersection::Intersection(float t, const Vec3& position, const Vec3& ray_direction, const Vec3& out_normal, const std::shared_ptr<Material> material) : 
	m_t{ t }, 
	m_position{ position }, 
	m_material{material} 
{
	set_normal(ray_direction, out_normal);
}

void Intersection::set_normal(const Vec3& ray_direction, const Vec3& out_normal) {
	m_front_face = Vec3::dot(ray_direction, out_normal) < 0.0f;
	m_normal = m_front_face ? out_normal : -out_normal;
}