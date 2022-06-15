#include <iostream>
#include <memory>
#include <random>

#include "utility/utility.h"
#include "utility/image.h"
#include "scene/scene.h"
#include "scene/material.h"
#include "camera/camera.h"


Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.001f) {

	if (num_bounces <= 0) return {};

	const auto intersection{ scene.intersect(ray, epsilon, utility::infinity) };
	if (!intersection.has_value()) return utility::gradientColor(ray.direction());

	const Intersection hit{ intersection.value() };

	const auto reflection = hit.material()->scatter(ray.direction(), hit.normal());
	Vec3 color{ hit.lighting(scene, epsilon)};
	if (!reflection.has_value()) return color;

	const float reflectiveness{ hit.material()->reflectiveness() };
	return (1.0f - reflectiveness) * color + reflectiveness * traceRay(Ray{ hit.position(), reflection.value() }, scene, num_bounces - 1, epsilon);

}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1280 }, height{ int(width / aspect_ratio) };
	const float horizontal_fov{ 110.0f };

	Image img{ width, height };

	const Vec3 camera_position{ 0.0f, 0.0f, 3.0f }, camera_look_at{ 0.0f, 0.0f, -1.0f }, camera_up{ 0.0f, 1.0f, 0.0f };
	Camera camera{ camera_position, camera_look_at, camera_up, horizontal_fov, aspect_ratio };

	Scene scene{ demoScene() };

	const int num_samples{ 100 }, num_bounces{ 50 };
	for (int y{ 0 }; y < img.height(); ++y) {
		for (int x{ 0 }; x < img.width(); ++x) {
			Vec3 accumulated_color{};
			for (int s{ 0 }; s < num_samples; ++s) {
				const Ray ray{ camera.spawnRay((x + utility::randomScalar()) / img.width(), (y + utility::randomScalar()) / img.height())};
				accumulated_color += traceRay(ray, scene, num_bounces);
			}
			img.setPixel(x, y, accumulated_color / float(num_samples));
		}
	}

	const int gamma{ 1 };
	img.writeToBMP("result", gamma);

	return EXIT_SUCCESS;

}