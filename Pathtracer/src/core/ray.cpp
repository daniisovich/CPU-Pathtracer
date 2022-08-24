#include "precompiled/pch.h"
#pragma hdrstop

#include "ray.h"


Ray::Ray(const Vec3& origin, const Vec3& direction) : 
	m_origin{ origin }, 
	m_direction{ direction } 
{}

Ray::Ray(const Ray& other) : 
	m_origin{ other.m_origin }, 
	m_direction{ other.m_direction } 
{}

Vec3 Ray::point(float t) const {
	return m_origin + t * m_direction;
}