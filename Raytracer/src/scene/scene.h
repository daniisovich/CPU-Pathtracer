#pragma once

#include "scene.fwd.h"

#include <memory>
#include <vector>

#include "lighting/lightsource.h"
#include "scene_object.h"
#include "camera/camera.h"


class Scene {

public:

	Scene() = default;
	Scene(const Camera& camera);
	Scene(const std::vector<std::shared_ptr<SceneObject>>& objects, const std::vector<std::shared_ptr<Lightsource>>& lights, const Camera& camera);

	void add(const std::shared_ptr<Lightsource>& light);
	void add(const std::vector<std::shared_ptr<Lightsource>>& lights);

	void add(const std::shared_ptr<SceneObject>& object);
	void add(const std::vector<std::shared_ptr<SceneObject>>& objects);

	void setCamera(const Camera& camera);

	std::optional<Intersection> intersect(const Ray& ray, float near, float far) const;
	Ray spawnRay(float u, float v) const;

	std::vector<std::shared_ptr<Lightsource>> lights() const;

private:

	std::vector<std::shared_ptr<Lightsource>> m_lights{};
	std::vector<std::shared_ptr<SceneObject>> m_objects{};
	Camera m_camera;

};


Scene demoScene(float aspect_ratio);