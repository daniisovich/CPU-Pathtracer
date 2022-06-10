#include <iostream>
#include <memory>
#include <random>

#include "image.h"
#include "camera.h"
#include "scene.h"
#include "sphere.h"
#include "material.h"

Vec3 backgroundColor(const Vec3& direction, const Vec3& color1 = { 1.0f, 1.0f, 1.0f }, const Vec3& color2 = { 0.5f, 0.7f, 1.0f }) {

	const Vec3 normalized_direction{ Vec3::normalize(direction) };
	const float t{ (normalized_direction.y() + 1.0f) * 0.5f };
	return color1 * (1.0f - t) + color2 * t;

}

Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.1f) {

	const auto intersection{ scene.intersect(ray, epsilon, 100.0f) };
	if (!intersection.has_value()) return backgroundColor(ray.direction());

	const auto hit{ intersection.value() };
	const auto material{ hit.material };
	
	const float reflectiveness{ material->reflectiveness() };
	if (num_bounces <= 0 || reflectiveness == 0.0f) return material->color();

	const Vec3 reflection{ Vec3::reflect(ray.direction(), hit.normal) };
	return (1 - reflectiveness) * material->color() + reflectiveness * traceRay(Ray{ hit.intersection, reflection }, scene, num_bounces - 1, epsilon);

}

float random(float min = 0.0f, float max = 1.0f) {

	static std::mt19937 generator(std::random_device{}());
	static std::uniform_real_distribution<float> distribution{ min, max };

	return distribution(generator);

}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1920 };
	const int height{ int(width / aspect_ratio) };
	const float horizontal_fov{ 90.0f };

	Image img{ width, height };
	Camera cam{ Vec3{0.0f, 0.0f, 2.0f}, Vec3{0.0f, 0.0f, -1.0f}, Vec3{0.0f, 1.0f, 0.0f}, horizontal_fov, aspect_ratio };

	Scene scene;

	auto material1 = std::make_shared<Material>(Material{ Vec3{ 1.0f, 0.0f, 0.0f }, 0.2f });
	auto material2 = std::make_shared<Material>(Material{ Vec3{ 0.0f, 1.0f, 0.0f }, 0.8f });

	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 0.0f, 0.0f, -1.0f }, 0.5f, material1 }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 1.0f, 0.0f, -1.0f }, 0.5f, material2 }));

	int num_samples{ 4 }, num_bounces{ 1 };
	for (int y{ 0 }; y < img.height(); ++y) {
		for (int x{ 0 }; x < img.width(); ++x) {
			Vec3 accumulated_color{};
			for (int s{ 0 }; s < num_samples; ++s) {
				const Ray ray{ cam.spawnRay((x + random()) / img.width(), (y + random()) / img.height())};
				accumulated_color += traceRay(ray, scene, num_bounces);
			}
			img.setPixel(x, y, accumulated_color / float(num_samples));
		}
	}

	img.writeToBMP("result");
	return EXIT_SUCCESS;

}