#include "precompiled/pch.h"
#pragma hdrstop

#include "dielectric.h"
#include "core/intersection.h"


Dielectric::Dielectric(const Vec3& color, float refractive_index) : 
	Material(color), 
	m_refractive_index{ refractive_index } 
{}

Ray Dielectric::scatter(const Ray& ray, const Intersection& intersection) const {

	const float refractive_index_out{ intersection.front_face() ? 1.0f : m_refractive_index }, 
				refractive_index_in{ intersection.front_face() ? m_refractive_index : 1.0f };
	const Vec3 refracted{ Vec3::refract(Vec3::normalize(ray.direction()), intersection.normal(), refractive_index_out, refractive_index_in) };
	return Ray{ intersection.position(), refracted };

}