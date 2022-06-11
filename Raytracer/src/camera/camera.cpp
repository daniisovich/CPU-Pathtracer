#include "camera.h"

#define _USE_MATH_DEFINES
#include <math.h>


float degreeToRadian(float deg);


Camera::Camera(float horizontal_fov_deg, float aspect_ratio) : Camera(Vec3{ 0.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 0.0f, -1.0f }, Vec3{ 0.0f, 1.0f, 0.0f }, horizontal_fov_deg, aspect_ratio) { }

Camera::Camera(const Vec3& position, const Vec3& look_at, const Vec3& up, float horizontal_fov_deg, float aspect_ratio) : m_position{ position } {

	Vec3 view_dir{ Vec3::normalize(look_at - m_position) };
	Vec3 right{ Vec3::normalize(Vec3::cross(view_dir, up)) };
	// view_dir and right are orthogonal so the cross product between two unit vectors is a unit vector
	Vec3 orth_up{ Vec3::cross(right, view_dir) };

	float horizontal_fov_rad{ degreeToRadian(horizontal_fov_deg) };
	float viewport_width{ 2 * tanf(horizontal_fov_rad / 2) };
	float viewport_height{ viewport_width / aspect_ratio };

	m_view = { right * viewport_width, orth_up * viewport_height };
	m_lower_left_corner = m_position + view_dir - (m_view.horizontal + m_view.vertical) / 2;

}

Ray Camera::spawnRay(float u, float v) const {
	return { m_position, m_lower_left_corner + m_view.horizontal * u + m_view.vertical * v - m_position };
}

float degreeToRadian(float deg) {
	return deg / 180 * float(M_PI);
}