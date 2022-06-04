#include "scene.h"


void Scene::addObject(const std::shared_ptr<SceneObject> object) {
	objects.push_back(object);
}

std::optional<Hit> Scene::intersect(const Ray& ray, float near, float far) const {

	std::optional<Hit> intersection;
	for (size_t i{ 0 }; i < objects.size(); ++i) {

		auto result{ objects[i]->intersect(ray, near, far) };
		if (!result.has_value() || (intersection.has_value() && result.value().t >= intersection.value().t)) continue;

		intersection = result;

	}

	return intersection;

}