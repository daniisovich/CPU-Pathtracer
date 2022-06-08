#include "point_light.h"


PointLight::PointLight(const Vec3& position) : m_position{ position } {}

const Ray PointLight::lightRay(const Vec3& position) const {
	return { position, m_position - position };
}