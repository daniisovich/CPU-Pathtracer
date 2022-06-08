#include <iostream>
#include <memory>

#include "image.h"
#include "camera.h"
#include "scene.h"
#include "sphere.h"
#include "material.h"

Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.001f) {
	if (num_bounces < 0) return { 0.0f, 0.0f, 0.0f };

	const auto intersection{ scene.intersect(ray, epsilon, 100.0f) };
	if (!intersection.has_value()) {
		const Vec3 normalized_direction{ Vec3::normalize(ray.direction()) };
		const float t{ (normalized_direction.y() + 1.0f) * 0.5f };
		return Vec3{ 1.0f, 1.0f, 1.0f } * (1.0f - t) + Vec3{ 0.5f, 0.7f, 1.0f } * t;
	}

	const auto hit{ intersection.value() };
	const auto material{ hit.material };
	
	if (material->reflectiveness() == 0.0f) return material->color();
	Vec3 reflection{ Vec3::reflect(ray.direction(), hit.normal) };
	float reflectiveness{ material->reflectiveness() };
	return (1 - reflectiveness) * material->color() + reflectiveness * traceRay(Ray{ hit.intersection, reflection }, scene, num_bounces - 1, epsilon);

}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1920 };
	const int height{ int(width / aspect_ratio) };
	const float horizontal_fov{ 90.0f };

	Image img{ width, height };
	Camera cam{ horizontal_fov, aspect_ratio };

	Scene scene;

	auto material1 = std::make_shared<Material>(Material{ Vec3{ 1.0f, 0.0f, 0.0f }, 0.0f });
	auto material2 = std::make_shared<Material>(Material{ Vec3{ 0.0f, 1.0f, 0.0f }, 0.0f });

	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 0.0f, 1.0f, 0.0f }, 1.0f, material1 }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 2.0f, 1.0f, 0.0f }, 1.0f, material2 }));

	for (size_t y{ 0 }; y < img.height(); ++y) {
		for (size_t x{ 0 }; x < img.width(); ++x) {
			const Ray ray{ cam.spawnRay(float(x) / img.width(), float(y) / img.height()) };
			img.setPixel(x, y, traceRay(ray, scene, 0));
		}
	}

	img.writeToBMP("result");
	return EXIT_SUCCESS;

}