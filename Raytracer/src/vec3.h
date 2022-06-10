#pragma once

#include <array>
#include <string>
#include <ostream>


class Vec3 {

public:

	Vec3();
	Vec3(float val);
	Vec3(float x, float y, float z);
	Vec3(const Vec3& other);

	float length() const;
	float sq_length() const;

	void normalize();
	static Vec3 normalize(const Vec3& vec);

	static float dot(const Vec3& a, const Vec3& b);
	static Vec3 cross(const Vec3& a, const Vec3& b);

	static Vec3 reflect(const Vec3& vec, const Vec3& normal);
	static Vec3 refract(const Vec3& vec, const Vec3& normal, float index);

	static Vec3 clamp(const Vec3& vec, float lower_bound, float upper_bound);

	float x() const;
	float y() const;
	float z() const;

	float r() const;
	float g() const;
	float b() const;

	Vec3 operator-() const;

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;

	Vec3& operator+=(const Vec3& other);

	friend Vec3 operator*(const Vec3& vec, float val);
	friend Vec3 operator*(float val, const Vec3& vec);
	friend Vec3 operator/(const Vec3& vec, float val);

	friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);

private:

	std::array<float, 3> m_data;

};
