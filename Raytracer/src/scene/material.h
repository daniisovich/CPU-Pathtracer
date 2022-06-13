#pragma once

#include <optional>
#include <functional>

#include "../core/ray.h"


using BRDF = std::function<Vec3 (const Vec3&, const Vec3&)>;

class Material {

public:

	Material(const Vec3& color, float reflectiveness, float fuzziness, BRDF brdf);

	virtual std::pair<Vec3, std::optional<Vec3>> scatter(const Vec3& ray_direction, const Vec3& normal) const;

	const Vec3 color() const;
	float reflectiveness() const;

private:

	Vec3 m_color;
	float m_reflectiveness, m_fuzziness;
	BRDF m_brdf;

};