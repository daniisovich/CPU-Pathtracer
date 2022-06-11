#include "directional_light.h"


DirectionalLight::DirectionalLight(const Vec3& direction) : m_direction{ direction } {}

const Ray DirectionalLight::lightRay(const Vec3& position) const {
	return { position, m_direction };
}