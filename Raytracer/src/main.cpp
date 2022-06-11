#include <iostream>
#include <memory>
#include <random>

#include "utility.h"
#include "image.h"
#include "camera.h"
#include "scene.h"
#include "sphere.h"
#include "material.h"


Vec3 gradientColor(const Vec3& direction, const Vec3& lower_color = { 1.0f, 1.0f, 1.0f }, const Vec3& upper_color = { 0.5f, 0.7f, 1.0f }) {

	const Vec3 normalized_direction{ Vec3::normalize(direction) };
	const float t{ (normalized_direction.y() + 1.0f) * 0.5f };
	return lower_color * (1.0f - t) + upper_color * t;

}

Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.1f) {

	if (num_bounces <= 0) return {};

	const auto intersection{ scene.intersect(ray, epsilon, 100.0f) };
	if (!intersection.has_value()) return gradientColor(ray.direction());

	const auto hit{ intersection.value() };

	auto target_dir{ utility::randomInHemisphere(hit.normal) };
	return 0.5 * traceRay(Ray{ hit.intersection, target_dir }, scene, num_bounces - 1, epsilon);

	const auto material{ hit.material };
	
	const float reflectiveness{ material->reflectiveness() };
	if (num_bounces <= 0 || reflectiveness == 0.0f) return material->color();

	const Vec3 reflection{ Vec3::reflect(ray.direction(), hit.normal) };
	return (1 - reflectiveness) * material->color() + reflectiveness * traceRay(Ray{ hit.intersection, reflection }, scene, num_bounces - 1, epsilon);

}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1280 };
	const int height{ int(width / aspect_ratio) };
	const float horizontal_fov{ 90.0f };

	Image img{ width, height };
	Camera cam{ Vec3{0.0f, 1.0f, 2.0f}, Vec3{0.0f, 0.0f, -1.0f}, Vec3{0.0f, 1.0f, 0.0f}, horizontal_fov, aspect_ratio };

	Scene scene{ demoScene() };

	int num_samples{ 100 }, num_bounces{ 50 };
	for (int y{ 0 }; y < img.height(); ++y) {
		for (int x{ 0 }; x < img.width(); ++x) {
			Vec3 accumulated_color{};
			for (int s{ 0 }; s < num_samples; ++s) {
				const Ray ray{ cam.spawnRay((x + utility::randomScalar()) / img.width(), (y + utility::randomScalar()) / img.height())};
				accumulated_color += traceRay(ray, scene, num_bounces);
			}
			img.setPixel(x, y, accumulated_color / float(num_samples));
		}
	}

	img.writeToBMP("result");
	return EXIT_SUCCESS;

}