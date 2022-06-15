#include "directional_light.h"


DirectionalLight::DirectionalLight(const Vec3& direction, const Vec3& color) : m_direction{ direction }, Lightsource{ color } {}

const Ray DirectionalLight::lightRay(const Vec3& position) const {
	return { position, m_direction };
}