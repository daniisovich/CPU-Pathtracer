#include "area_light.h"

#include "../../utility/utility.h"


AreaLight::AreaLight(const Vec3& position, float radius) : m_position{ position }, m_radius{ radius } {}

const Ray AreaLight::lightRay(const Vec3& position) const {

	const Vec3 center_light_ray{ m_position - position };
	const Vec3 random_offset{ m_radius * utility::randomInHemisphere(-center_light_ray) };
	return Ray{ position, center_light_ray + random_offset };

}