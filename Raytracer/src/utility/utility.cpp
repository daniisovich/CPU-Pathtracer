#include "utility.h"

#define _USE_MATH_DEFINES
#include <math.h>


namespace utility {

	float randomScalar(float min, float max) {

		static std::mt19937 generator(std::random_device{}());
		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(generator);

	}

	Vec3 randomInDisk(float radius) {

		const float phi{ randomScalar(0.0f, 2.0f * float(M_PI)) };
		const float length{ randomScalar(0.0f, std::abs(radius)) };

		return length * Vec3{ std::cosf(phi), std::sinf(phi), 0.0f };

	}

	Vec3 randomInSphere(float radius) {

		const float theta{ randomScalar(0.0f, 2.0f * float(M_PI)) }, phi{ randomScalar(0.0f, 2.0f * float(M_PI)) };
		const float length{ randomScalar(0.0f, std::abs(radius)) };

		return length * Vec3{ std::sinf(theta) * std::cosf(phi), std::sinf(theta) * std::sinf(phi), std::cosf(theta) };

	}

	Vec3 randomInHemisphere(const Vec3& normal) {

		auto random_unit_vec{ Vec3::normalize(randomInSphere()) };
		if (Vec3::dot(random_unit_vec, normal) > 0.0f) return random_unit_vec;
		return -random_unit_vec;

	}

	Vec3 brdfHemisphere(const Vec3& ray_direction, const Vec3& normal) {
		return randomInHemisphere(normal);
	}

	Vec3 gradientColor(const Vec3& direction, const Vec3& lower_color, const Vec3& upper_color) {

		const Vec3 normalized_direction{ Vec3::normalize(direction) };
		const float t{ (normalized_direction.y() + 1.0f) * 0.5f };
		return lower_color * (1.0f - t) + upper_color * t;

	}

}