#include "scene.h"

#include "lighting/area_light.h"
#include "geometry/sphere.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "../utility/utility.h"


Scene::Scene(const Camera& camera) : m_camera{ camera } {}

Scene::Scene(const std::vector<std::shared_ptr<SceneObject>>& objects, const std::vector<std::shared_ptr<Lightsource>>& lights, const Camera& camera) 
	: m_objects{ objects }, m_lights{ lights }, m_camera{ camera } { }

void Scene::add(const std::shared_ptr<Lightsource>& light) {
	m_lights.push_back(light);
}

void Scene::add(const std::vector<std::shared_ptr<Lightsource>>& lights) {

	m_objects.reserve(m_lights.size() + lights.size());
	for (const auto& light : lights) {
		m_lights.push_back(light);
	}

}

void Scene::add(const std::shared_ptr<SceneObject>& object) {
	m_objects.push_back(object);
}

void Scene::add(const std::vector<std::shared_ptr<SceneObject>>& objects) {
	
	m_objects.reserve(m_objects.size() + objects.size());
	for (const auto& object : objects) {
		m_objects.push_back(object);
	}

}

void Scene::setCamera(const Camera& camera) {
	m_camera = camera;
}

Ray Scene::spawnRay(float u, float v) const {
	return m_camera.spawnRay(u, v);
}

std::optional<Intersection> Scene::intersect(const Ray& ray, float near, float far) const {

	std::optional<Intersection> intersection{ std::nullopt };
	for (size_t i{ 0 }; i < m_objects.size(); ++i) {

		const auto result{ m_objects[i]->intersect(ray, near, far) };
		if (!result.has_value() || (intersection.has_value() && result.value().t() >= intersection.value().t())) continue;

		intersection = result;

	}

	return intersection;

}

std::vector<std::shared_ptr<Lightsource>> Scene::lights() const { return m_lights; }

Scene demoScene(float aspect_ratio) {

	const float horizontal_fov{ 110.0f }, focal_distance{ 1.5f }, aperture{ focal_distance / 10.0f };
	const Vec3 camera_position{ 0.0f, 0.0f, 0.5f }, camera_look_at{ 0.0f, 0.0f, -1.0f }, camera_up{ 0.0f, 1.0f, 0.0f };
	Camera camera{ camera_position, camera_look_at, camera_up, horizontal_fov, aspect_ratio, aperture, focal_distance };

	Scene scene{ camera };

	const auto material_ground = std::make_shared<Lambertian>(Lambertian{ Vec3{ 0.8f, 0.8f, 0.0f } });
	const auto material_center = std::make_shared<Lambertian>(Lambertian{ Vec3{ 0.7f, 0.3f, 0.3f } });
	const auto material_left   = std::make_shared<Dielectric>(Dielectric{ Vec3{ 1.0f, 1.0f, 1.0f }, 1.5f });
	const auto material_right  = std::make_shared<Metal>(Metal{ Vec3{ 0.8f, 0.6f, 0.2f }, 1.0f });

	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{0.0f, -100.5f, -1.0f }, 100.0f, material_ground }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 0.0f, 0.0f, -1.0f }, 0.5f, material_center }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ -1.0f, 0.0f, -1.0f }, 0.5f, material_left }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ -1.0f, 0.0f, -1.0f }, -0.4f, material_left }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 1.0f, 0.0f, -1.0f }, 0.5f, material_right }));

	return scene;

}

Scene randomScene(float aspect_ratio) {

	const float horizontal_fov{ 40.0f }, focal_distance{ 10.0f }, aperture{ focal_distance / 100.0f };
	const Vec3 camera_position{ 13.0f, 2.0f, 3.0f }, camera_look_at{ 0.0f, 0.0f, 0.0f }, camera_up{ 0.0f, 1.0f, 0.0f };
	Camera camera{ camera_position, camera_look_at, camera_up, horizontal_fov, aspect_ratio, aperture, focal_distance };

	Scene scene{ camera };

	const auto material_ground = std::make_shared<Lambertian>(Vec3{ 0.5f, 0.5f, 0.5f });
	scene.add(std::make_shared<Sphere>(Vec3{ 0.0f, -1000.0f, 0.0f }, 1000.0f, material_ground));

	for (int a{ -11 }; a < 11; ++a) {
		for (int b{ -11 }; b < 11; ++b) {
			
			const float material{ utility::randomScalar() };
			const Vec3 center{ a + 0.9f * utility::randomScalar(), 0.2f, b + 0.9f * utility::randomScalar() };

			if ((center - Vec3{ 4.0f, 0.2f, 0.0f }).length() > 0.9f) {

				std::shared_ptr<Material> sphere_material;
				if (material < 0.8) {
					const Vec3 color{ Vec3::random() * Vec3::random() };
					sphere_material = std::make_shared<Lambertian>(color);
				} else if (material < 0.95) {
					const Vec3 color{ Vec3::random(0.5f, 1.0f) };
					const float fuzziness{ utility::randomScalar(0.0f, 0.5f) };
					sphere_material = std::make_shared<Metal>(color, fuzziness);
				} else {
					const Vec3 color{ 0.0f };
					sphere_material = std::make_shared<Dielectric>(color, 1.5f);
				}
				scene.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));

			}

		}
	}

	const auto material_dielectric = std::make_shared<Dielectric>(Vec3{ 1.0f }, 1.5f);
	const auto material_lambertian = std::make_shared<Lambertian>(Vec3{ 0.4f, 0.2f, 0.1f });
	const auto material_metal = std::make_shared<Metal>(Vec3{ 0.7f, 0.6f, 0.5f }, 0.0f);

	scene.add(std::make_shared<Sphere>(Vec3{ 0.0f, 1.0f, 0.0f }, 1.0f, material_dielectric));
	scene.add(std::make_shared<Sphere>(Vec3{ -4.0f, 1.0f, 0.0f }, 1.0f, material_lambertian));
	scene.add(std::make_shared<Sphere>(Vec3{ 4.0f, 1.0f, 0.0f }, 1.0f, material_metal));

	return scene;

}