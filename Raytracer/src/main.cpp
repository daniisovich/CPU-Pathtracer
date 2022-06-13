#include <iostream>
#include <memory>
#include <random>

#include "utility/utility.h"
#include "utility/image.h"
#include "scene/scene.h"
#include "scene/material.h"
#include "camera/camera.h"


Vec3 gradientColor(const Vec3& direction, const Vec3& lower_color = { 1.0f, 1.0f, 1.0f }, const Vec3& upper_color = { 0.5f, 0.7f, 1.0f }) {

	const Vec3 normalized_direction{ Vec3::normalize(direction) };
	const float t{ (normalized_direction.y() + 1.0f) * 0.5f };
	return lower_color * (1.0f - t) + upper_color * t;

}

Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.001f) {

	if (num_bounces <= 0) return {};

	const auto intersection{ scene.intersect(ray, epsilon, utility::infinity) };
	if (!intersection.has_value()) return gradientColor(ray.direction());

	const Intersection hit{ intersection.value() };
	return hit.lighting(scene.lights());

	//const Vec3 target_dir{ utility::randomInHemisphere(hit.normal) };
	auto [color, reflection] = hit.material()->scatter(ray.direction(), hit.normal());
	if (!reflection.has_value()) return color;

	return color * traceRay(Ray{ hit.position(), reflection.value()}, scene, num_bounces - 1, epsilon);

}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1280 };
	const int height{ int(width / aspect_ratio) };
	const float horizontal_fov{ 120.0f };

	Image img{ width, height };
	Camera cam{ horizontal_fov, aspect_ratio };

	Scene scene{ demoScene() };

	const int num_samples{ 100 }, num_bounces{ 50 };
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

	const int gamma{ 1 };
	img.writeToBMP("result", gamma);

	return EXIT_SUCCESS;

}