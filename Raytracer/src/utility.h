#pragma once

#include <random>

#include "vec3.h"


float random(float min = 0.0f, float max = 1.0f);
Vec3 randomInSphere(float radius = 1.0f);
Vec3 randomInHemisphere(const Vec3& normal);