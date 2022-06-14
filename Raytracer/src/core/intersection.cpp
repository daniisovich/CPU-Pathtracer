#include "intersection.h"

#include "core.h"
#include "../scene/scene.h"


Intersection::Intersection(float t, const Vec3& position, const Vec3& ray_direction, const Vec3& out_normal, const std::shared_ptr<Material> material) 
																: m_t{ t }, m_position{ position }, m_view_dir{ Vec3::normalize(- ray_direction) }, m_material{material} {
	set_normal(ray_direction, out_normal);
}

Vec3 Intersection::lighting(const Scene& scene, float epsilon) const {

	Vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	Vec3 diffuse, specular;
	for (const auto& light : scene.lights()) {

		Ray lightray{ light->lightRay(m_position) };
		if (scene.intersect(lightray, epsilon, 1.0f).has_value()) continue;

		const Vec3 lightDir{ Vec3::normalize(lightray.direction()) };
		float weight{ Vec3::dot(lightDir, m_normal) };
		if (weight < 0.0f) continue;
		diffuse += 0.3f * weight * lightColor;

		const Vec3 reflectedLight{ Vec3::reflect(-lightDir, m_normal) };
		assert(reflectedLight == Vec3::normalize(reflectedLight));
		weight = Vec3::dot(reflectedLight, m_view_dir);
		if (weight < 0.0f) continue;
		specular += 0.2f * std::powf(weight, 10) * lightColor;

	}

	Vec3 ambient{ 0.5f * m_material->color() };
	return ambient + (diffuse + specular) / float(scene.lights().size());

}

bool Intersection::front_face() const { return m_front_face; }
float Intersection::t() const { return m_t; }
Vec3 Intersection::position() const { return m_position; }
Vec3 Intersection::normal() const { return m_normal; }
std::shared_ptr<Material> Intersection::material() const { return m_material; }

void Intersection::set_normal(const Vec3& ray_direction, const Vec3& out_normal) {
	m_front_face = Vec3::dot(ray_direction, out_normal) < 0.0f;
	m_normal = m_front_face ? out_normal : -out_normal;
}