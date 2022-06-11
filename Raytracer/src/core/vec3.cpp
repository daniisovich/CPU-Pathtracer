#include "vec3.h"

#include <sstream>
#include <algorithm>

#include "../utility/utility.h"


Vec3::Vec3() : Vec3(0.0f) {}
Vec3::Vec3(float val) : Vec3(val, val, val) {}
Vec3::Vec3(float x, float y, float z) : m_data{ x, y, z } {}
Vec3::Vec3(const Vec3& other) : m_data{ other.m_data } {}

Vec3 Vec3::normalize(const Vec3& vec) {
	return vec / vec.length();
}

void Vec3::normalize() {
	*this = *this / this->length();
}

float Vec3::dot(const Vec3& a, const Vec3& b) {
	return a.m_data[0] * b.m_data[0] + a.m_data[1] * b.m_data[1] + a.m_data[2] * b.m_data[2];
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
	return { a.m_data[1] * b.m_data[2] - a.m_data[2] * b.m_data[1],
			 a.m_data[2] * b.m_data[0] - a.m_data[0] * b.m_data[2],
			 a.m_data[0] * b.m_data[1] - a.m_data[1] * b.m_data[0] };
}

Vec3 Vec3::reflect(const Vec3& vec, const Vec3& normal) {
	return vec - 2 * Vec3::dot(vec, normal) * normal;
}

Vec3 Vec3::refract(const Vec3& vec, const Vec3& normal, float index) {

	Vec3 l{ normalize(vec) };
	float costheta1{ Vec3::dot(l, -normal) };
	float costheta2 = sqrt(1 - index * index * (1 - costheta1 * costheta1));
	return index * l + (index * costheta1 - costheta2) * normal;

}

float Vec3::length() const {
	return sqrt(sq_length());
}

float Vec3::sq_length() const {
	return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];
}

Vec3 Vec3::clamp(const Vec3& vec, float lower_bound, float upper_bound) {
	return { std::clamp(vec.m_data[0], lower_bound, upper_bound),
			 std::clamp(vec.m_data[1], lower_bound, upper_bound),
			 std::clamp(vec.m_data[2], lower_bound, upper_bound) };
}

Vec3 Vec3::gammaCorrection(const Vec3& vec, int gamma) {
	return { std::pow(vec.m_data[0], 1 / float(gamma)),
			 std::pow(vec.m_data[1], 1 / float(gamma)),
			 std::pow(vec.m_data[2], 1 / float(gamma)) };
}

float Vec3::x() const { return m_data[0]; }
float Vec3::y() const { return m_data[1]; }
float Vec3::z() const { return m_data[2]; }

float Vec3::r() const { return m_data[0]; }
float Vec3::g() const { return m_data[1]; }
float Vec3::b() const { return m_data[2]; }

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
	os << "(" << vec.m_data[0] << ", " << vec.m_data[1] << ", " << vec.m_data[2] << ")";
	return os;
}

Vec3 Vec3::operator-() const {
	return { -m_data[0], -m_data[1], -m_data[2] };
}

Vec3 Vec3::operator+(const Vec3& other) const {
	return { m_data[0] + other.m_data[0], m_data[1] + other.m_data[1], m_data[2] + other.m_data[2] };
}

Vec3 Vec3::operator-(const Vec3& other) const {
	return { m_data[0] - other.m_data[0], m_data[1] - other.m_data[1], m_data[2] - other.m_data[2] };
}

Vec3 Vec3::operator*(const Vec3& other) const {
	return { m_data[0] * other.m_data[0], m_data[1] * other.m_data[1], m_data[2] * other.m_data[2] };
}

Vec3 Vec3::operator/(const Vec3& other) const {
	return { m_data[0] / other.m_data[0], m_data[1] / other.m_data[1], m_data[2] / other.m_data[2] };
}

Vec3& Vec3::operator+=(const Vec3& other) {
	*this = *this + other;
	return *this;
}

Vec3 operator*(const Vec3& vec, float val) {
	return { vec.m_data[0] * val, vec.m_data[1] * val, vec.m_data[2] * val };
}

Vec3 operator*(float val, const Vec3& vec) {
	return vec * val;
}

Vec3 operator/(const Vec3& vec, float val) {
	return vec * (1 / val);
}

Vec3 Vec3::random(float min, float max) {
	return { utility::randomScalar(min, max), utility::randomScalar(min, max), utility::randomScalar(min, max) };
}