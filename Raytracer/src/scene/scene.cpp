#include "scene.h"

#include "sphere.h"


Scene::Scene(const std::vector<std::shared_ptr<SceneObject>>& objects) : m_objects{ objects } { }

void Scene::add(const std::shared_ptr<SceneObject>& object) {
	m_objects.push_back(object);
}

void Scene::add(const std::vector<std::shared_ptr<SceneObject>>& objects) {
	
	m_objects.reserve(m_objects.size() + objects.size());
	for (const auto& object : objects) {
		m_objects.push_back(object);
	}

}

std::optional<Hit> Scene::intersect(const Ray& ray, float near, float far) const {

	std::optional<Hit> intersection;
	for (size_t i{ 0 }; i < m_objects.size(); ++i) {

		const auto result{ m_objects[i]->intersect(ray, near, far) };
		if (!result.has_value() || (intersection.has_value() && result.value().t >= intersection.value().t)) continue;

		intersection = result;

	}

	return intersection;

}

Scene demoScene() {

	auto material = std::make_shared<Material>(Material{ Vec3{ 0.0f, 1.0f, 0.0f }, 0.8f });

	Scene scene;
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{ 0.0f, 0.0f, -1.0f }, 0.5f, material }));
	scene.add(std::make_shared<Sphere>(Sphere{ Vec3{0.0f, -100.5f, -1.0f }, 100.0f, material }));

	return scene;

}