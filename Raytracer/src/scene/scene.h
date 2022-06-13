#pragma once

#include <memory>
#include <vector>

#include "lightsource.h"
#include "scene_object.h"


class Scene {

public:

	Scene() = default;
	Scene(const std::vector<std::shared_ptr<SceneObject>>& objects, const std::vector<std::shared_ptr<Lightsource>>& lights);

	void add(const std::shared_ptr<Lightsource>& light);
	void add(const std::vector<std::shared_ptr<Lightsource>>& lights);

	void add(const std::shared_ptr<SceneObject>& object);
	void add(const std::vector<std::shared_ptr<SceneObject>>& objects);

	std::vector<std::shared_ptr<Lightsource>> lights() const;

	std::optional<Intersection> intersect(const Ray& ray, float near, float far) const;

private:

	std::vector<std::shared_ptr<Lightsource>> m_lights{};
	std::vector<std::shared_ptr<SceneObject>> m_objects{};

};


Scene demoScene();