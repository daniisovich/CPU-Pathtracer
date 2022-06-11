#include "utility.h"


float random(float min, float max) {

	static std::mt19937 generator(std::random_device{}());
	static std::uniform_real_distribution<float> distribution{ min, max };

	return distribution(generator);

}

Vec3 randomInSphere(float radius) {
	while (true) {
		auto point{ Vec3::randomVector(-radius, radius) };
		if (point.length() <= radius) return Vec3::normalize(point);
	}
}

Vec3 randomInHemisphere(const Vec3& normal) {
	auto random_vec{ randomInSphere() };
	if (Vec3::dot(random_vec, normal) > 0.0f) return random_vec;
	return -random_vec;
}