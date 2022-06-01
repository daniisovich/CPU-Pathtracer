#include "vec3.h"

#include <sstream>


Vec3 Vec3::normalize(const Vec3& vec) {
	return vec / vec.length();
}

void Vec3::normalize() {
	float len{ length() };
	data[0] /= len;
	data[1] /= len;
	data[2] /= len;
}

float Vec3::dot(const Vec3& other) const {
	return data[0] * other.data[0] + data[1] * other.data[1] + data[2] * other.data[2];
}

Vec3 Vec3::cross(const Vec3& other) const {
	return { data[1] * other.data[2] - data[2] * other.data[1],
			 data[2] * other.data[0] - data[0] * other.data[2],
			 data[0] * other.data[1] - data[1] * other.data[0] };
}

Vec3 Vec3::reflect(const Vec3& vec, const Vec3& normal) {
	return vec - 2 * vec.dot(normal) * normal;
}

Vec3 Vec3::refract(const Vec3& vec, const Vec3& normal, float index) {
	Vec3 l{ normalize(vec) };
	float costheta1{ l.dot(normal.invert()) };
	float costheta2 = sqrt(1 - index * index * (1 - costheta1 * costheta1));
	return index * l + (index * costheta1 - costheta2) * normal;
}

Vec3 Vec3::invert() const {
	return { -data[0], -data[1], -data[2] };
}

float Vec3::length() const {
	return sqrt(sq_length());
}

float Vec3::sq_length() const {
	return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

Vec3::Vec3() : data{ 0, 0, 0 } {}
Vec3::Vec3(float x, float y, float z) : data{ x, y, z } {}
Vec3::Vec3(const Vec3& other) : data{ other.data } {}

float Vec3::x() const { return data[0]; }
float Vec3::y() const { return data[1]; }
float Vec3::z() const { return data[2]; }

float Vec3::r() const { return data[0]; }
float Vec3::g() const { return data[1]; }
float Vec3::b() const { return data[2]; }

std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
	os << vec.toString();
	return os;
}

const std::string Vec3::toString() const {
	std::stringstream ss;
	ss << "(" << data[0] << ", " << data[1] << ", " << data[2] << ")";
	return ss.str();
}

Vec3 Vec3::operator+(const Vec3& other) const {
	return { data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2] };
}

Vec3 Vec3::operator-(const Vec3& other) const {
	return { data[0] - other.data[0], data[1] - other.data[1], data[2] - other.data[2] };
}

Vec3 Vec3::operator*(const Vec3& other) const {
	return { data[0] * other.data[0], data[1] * other.data[1], data[2] * other.data[2] };
}

Vec3 Vec3::operator/(const Vec3& other) const {
	return { data[0] / other.data[0], data[1] / other.data[1], data[2] / other.data[2] };
}

Vec3 operator*(const Vec3& vec, float val) {
	return { vec.data[0] * val, vec.data[1] * val, vec.data[2] * val };
}

Vec3 operator*(float val, const Vec3& vec) {
	return vec * val;
}

Vec3 Vec3::operator/(float val) const {
	return { data[0] / val, data[1] / val, data[2] / val };
}