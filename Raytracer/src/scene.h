#pragma once

#include <memory>
#include <vector>

#include "scene_object.h"


class Scene {

public:

	Scene() = default;
	Scene(const std::vector<std::shared_ptr<SceneObject>>& objects);

	void addObject(const std::shared_ptr<SceneObject> object);
	void addObjects(const std::vector<std::shared_ptr<SceneObject>>& objects);

	std::optional<Hit> intersect(const Ray& ray, float near, float far) const;

private:

	std::vector<std::shared_ptr<SceneObject>> m_objects{};

};