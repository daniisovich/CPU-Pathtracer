#include "camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "../../utility/utility.h"


float degreeToRadian(float deg);


Camera::Camera() : Camera(Vec3{ 0.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 0.0f, -1.0f }, Vec3{ 0.0f, 1.0f, 0.0f }, 90.0f, 16.0f / 9.0f, 0.0f, 1.0f) { }

Camera::Camera(float horizontal_fov_deg, float aspect_ratio, float aperture, float focus_distance) 
	: Camera(Vec3{ 0.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 0.0f, -1.0f }, Vec3{ 0.0f, 1.0f, 0.0f }, horizontal_fov_deg, aspect_ratio, aperture, focus_distance) { }

Camera::Camera(const Vec3& position, const Vec3& look_at, const Vec3& up, float horizontal_fov_deg, float aspect_ratio, float aperture, float focus_distance) 
	: m_position{ position }, m_lens_radius{ aperture / 2 } {

	Vec3 view_dir{ Vec3::normalize(look_at - m_position) };
	m_right = Vec3::normalize(Vec3::cross(view_dir, up));
	// view_dir and right are orthogonal so the cross product between two unit vectors is a unit vector
	m_up = Vec3::cross(m_right, view_dir);

	float horizontal_fov_rad{ degreeToRadian(horizontal_fov_deg) };
	float viewport_width{ 2 * tanf(horizontal_fov_rad / 2) };
	float viewport_height{ viewport_width / aspect_ratio };

	m_view = { focus_distance * m_right * viewport_width, focus_distance * m_up * viewport_height };
	m_lower_left_corner = m_position + focus_distance * view_dir - (m_view.horizontal + m_view.vertical) / 2;

}

Ray Camera::spawnRay(float u, float v) const {
	
	// Instead of circle lens we use a square as the calculation is way faster
	const Vec3 random{ m_lens_radius * utility::randomInDisk() };
	const Vec3 origin_offset{ m_right * random.x() + m_up * random.y() };

	return { m_position + origin_offset, Vec3::normalize(m_lower_left_corner + m_view.horizontal * u + m_view.vertical * v - (m_position + origin_offset)) };

}

float degreeToRadian(float deg) {
	return deg / 180 * float(M_PI);
}