#include "scene.h"

#include "point_light.h"
#include "sphere.h"
#include "../utility/utility.h"


Scene::Scene(const std::vector<std::shared_ptr<SceneObject>>& objects, const std::vector<std::shared_ptr<Lightsource>>& lights) : m_objects{ objects }, m_lights{ lights } { }

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

std::optional<Intersection> Scene::intersect(const Ray& ray, float near, float far) const {

	std::optional<Intersection> intersection;
	for (size_t i{ 0 }; i < m_objects.size(); ++i) {

		const auto result{ m_objects[i]->intersect(ray, near, far) };
		if (!result.has_value() || (intersection.has_value() && result.value().t() >= intersection.value().t())) continue;

		intersection = result;

	}

	return intersection;

}

std::vector<std::shared_ptr<Lightsource>> Scene::lights() const { return m_lights; }

Scene demoScene() {

	auto material_ground = std::make_shared<Material>(Material{ Vec3{ 0.8f, 0.8f, 0.0f }, 0.5f, 0.0f, utility::brdfHemisphere });
	auto material_center = std::make_shared<Material>(Material{ Vec3{ 0.7f, 0.3f, 0.3f }, 0.5f, 0.0f, utility::brdfHemisphere });
	//auto material_left   = std::make_shared<Material>(Material{ Vec3{ 0.8f, 0.8f, 0.8f }, 0.5f, 0.3f, Vec3::reflect });
	//auto material_right  = std::make_shared<Material>(Material{ Vec3{ 0.8f, 0.6f, 0.2f }, 0.5f, 1.0f, Vec3::reflect });

	Scene scene;
	
	scene.add(std::make_shared<PointLight>(PointLight(Vec3{0.0f, 3.0f, -0.0f})));

	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{0.0f, -100.5f, -1.0f }, 100.0f, material_ground }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 0.0f, 0.0f, -1.0f }, 0.5f, material_center }));
	//scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ -1.0f, 0.0f, -1.0f }, 0.5f, material_left }));
	//scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 1.0f, 0.0f, -1.0f }, 0.5f, material_right }));

	return scene;

}