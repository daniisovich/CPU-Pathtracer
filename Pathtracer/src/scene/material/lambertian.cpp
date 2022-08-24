#include "precompiled/pch.h"
#pragma hdrstop

#include "lambertian.h"

#include "utility/utility.h"
#include "core/intersection.h"


Lambertian::Lambertian(const Vec3& color) : 
	Material(color) 
{}

Ray Lambertian::scatter(const Ray& ray, const Intersection& intersection) const {

	Vec3 reflected;
	do {
		reflected = utility::randomOnHemisphere(intersection.normal());
	} while (reflected.degenerated());

	return Ray{ intersection.position(), reflected };

}