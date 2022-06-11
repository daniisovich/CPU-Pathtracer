#pragma once

#include "../core/vec3.h"
#include "../core/ray.h"


struct Viewport {
	Vec3 horizontal;
	Vec3 vertical;
};

class Camera {

public:

	Camera(float horizontal_flov, float aspect_ratio);
	Camera(const Vec3& position, const Vec3& look_at, const Vec3& up, float horizontal_fov_deg, float aspect_ratio);

	Ray spawnRay(float u, float v) const;

private:

	Vec3 m_position, m_lower_left_corner;
	Viewport m_view;

};