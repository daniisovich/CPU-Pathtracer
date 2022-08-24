#include "precompiled/pch.h"
#pragma hdrstop

#include "metal.h"

#include "utility/utility.h"
#include "core/intersection.h"


Metal::Metal(const Vec3& color, float fuzziness) : 
	Material(color), 
	m_fuzziness{ fuzziness > 0.0f ? fuzziness : 0.0f } 
{}

Ray Metal::scatter(const Ray& ray, const Intersection& intersection) const {

	const Vec3 reflected{ Vec3::reflect(Vec3::normalize(ray.direction()), intersection.normal()) };
	Vec3 fuzz_dir;
	do {
		fuzz_dir = m_fuzziness * utility::randomInSphere();
	} while (Vec3::dot(reflected + fuzz_dir, intersection.normal()) <= 0.0f);

	return Ray{ intersection.position(), reflected + fuzz_dir };

}