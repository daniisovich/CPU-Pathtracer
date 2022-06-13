#include "material.h"

#include "../utility/utility.h"


Material::Material(const Vec3& color, float reflectiveness, float fuzziness, BRDF brdf) : m_color{ color }, m_reflectiveness{ reflectiveness }, m_fuzziness{ fuzziness }, m_brdf{ brdf } { }

std::pair<Vec3, std::optional<Vec3>> Material::scatter(const Vec3& ray_direction, const Vec3& normal) const {

	if (m_reflectiveness == 0.0f) return { m_color, {} };
	Vec3 reflected{ m_brdf(ray_direction, normal) };
	return { m_color, { reflected + m_fuzziness * utility::randomInSphere()} };

}

const Vec3 Material::color() const { return m_color; }
float Material::reflectiveness() const { return m_reflectiveness; }