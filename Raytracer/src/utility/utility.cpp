#include "utility.h"


namespace utility {

	float randomScalar(float min, float max) {

		static std::mt19937 generator(std::random_device{}());
		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(generator);

	}

	Vec3 randomInSphere(float radius) {

		while (true) {
			auto point{ Vec3::random(-radius, radius) };
			if (point.length() <= radius) return point;
		}

	}

	Vec3 randomInHemisphere(const Vec3& normal) {

		auto random_unit_vec{ Vec3::normalize(randomInSphere()) };
		if (Vec3::dot(random_unit_vec, normal) > 0.0f) return random_unit_vec;
		return -random_unit_vec;

	}

	Vec3 brdfHemisphere(const Vec3& ray_direction, const Vec3& normal) {
		return randomInHemisphere(normal);
	}

}