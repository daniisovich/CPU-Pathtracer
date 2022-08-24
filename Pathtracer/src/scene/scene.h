#pragma once

#include "scene/geometry/scene_object.h"
#include "scene/camera/camera.h"


class Scene {

public:

	Scene() = default;
	Scene(const Camera& camera);
	Scene(const std::vector<std::shared_ptr<SceneObject>>& objects, const Camera& camera);

	void add(const std::shared_ptr<SceneObject>& object);
	void add(const std::vector<std::shared_ptr<SceneObject>>& objects);

	void setCamera(const Camera& camera);
	std::optional<Intersection> intersect(const Ray& ray, float near, float far) const;
	Ray spawnRay(float u, float v) const;

private:

	std::vector<std::shared_ptr<SceneObject>> m_objects{};
	Camera m_camera;

};


Scene demoScene(float aspect_ratio);
Scene randomScene(float aspect_ratio);