#pragma once

#include "material.h"


class Metal : public Material {

public:

	Metal(const Vec3& color, float fuzziness);
	virtual Ray scatter(const Ray& ray, const Intersection& intersection) const final override;

private:

	float m_fuzziness;

};