#include "point_light.h"


PointLight::PointLight(const Vec3& position, const Vec3& color) : m_position{ position }, Lightsource{ color } {}

const Ray PointLight::lightRay(const Vec3& position) const {
	return { position, m_position - position };
}