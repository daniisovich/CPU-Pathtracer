#include "precompiled/pch.h"
#pragma hdrstop

#include <windows.h>

#include "scene/scene.h"
#include "scene/material/material.h"
#include "scene/camera/camera.h"

#include "utility/utility.h"
#include "utility/thread_pool.h"
#include "utility/image.h"


Vec3 traceRay(const Ray& ray, const Scene& scene, int num_bounces, float epsilon = 0.001f) {

	if (num_bounces <= 0) return Vec3{0.0f};

	const auto intersection{ scene.intersect(ray, epsilon, utility::infinity) };
	if (!intersection.has_value()) return utility::gradientColor(ray.direction());

	const Intersection hit{ intersection.value() };

	const Ray reflection{ hit.material()->scatter(ray, hit) };
	const Vec3 color{ hit.material()->color() };

	return color * traceRay(reflection, scene, num_bounces - 1, epsilon);

}

void calculatePixelColor(int x, int y, int num_samples, int num_bounces, const Scene& scene, Image& img) {
	Vec3 accumulated_color{};
	for (int s{ 0 }; s < num_samples; ++s) {
		const Ray ray{ scene.spawnRay((x + utility::randomScalar()) / img.width(), (y + utility::randomScalar()) / img.height())};
		accumulated_color += traceRay(ray, scene, num_bounces);
	}
	img.setPixel(x, y, accumulated_color / float(num_samples));
}

int main() {

	const float aspect_ratio{ 16.0f / 9 };
	const int width{ 1280 }, height{ int(width / aspect_ratio) };

	Image img{ width, height };
	Scene scene{ demoScene(aspect_ratio) };

	ThreadPool pool;

	const int num_samples{ 500 }, num_bounces{ 10 };
	for (int y{ 0 }; y < img.height(); ++y) {
		for (int x{ 0 }; x < img.width(); ++x) {
			pool.queueJob(calculatePixelColor, x, y, num_samples, num_bounces, scene, img);
		}
	}
	pool.start();
	
	while (!pool.complete()) {
		Sleep(1000);
	}

	pool.stop();
	
	const int gamma{ 1 };
	img.writeToBMP("result", gamma);

	return EXIT_SUCCESS;

}