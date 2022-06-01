#pragma once

#include <array>
#include <string>


class Vec3 {

public:

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec3& other);

	float dot(const Vec3& other) const;
	Vec3 cross(const Vec3& other) const;

	static Vec3 normalize(const Vec3& vec);
	void normalize();

	Vec3 invert() const;
	float length() const;
	float sq_length() const;

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;

	Vec3 operator*(float val) const;
	Vec3 operator/(float val) const;

	float x() const;
	float y() const;
	float z() const;

	float r() const;
	float g() const;
	float b() const;

	const std::string toString() const;

private:

	std::array<float, 3> data;

};
