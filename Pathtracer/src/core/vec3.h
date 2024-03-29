#pragma once


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

	bool degenerated() const;

	static float dot(const Vec3& a, const Vec3& b);
	static Vec3 cross(const Vec3& a, const Vec3& b);

	static Vec3 reflect(const Vec3& vec, const Vec3& normal);
	static Vec3 refract(const Vec3& vec, const Vec3& normal, float refractive_index_out, float refractive_index_in);

	static Vec3 clamp(const Vec3& vec, float lower_bound, float upper_bound);
	static Vec3 gammaCorrection(const Vec3& vec, int gamma);
	static Vec3 random(float min = 0.0f, float max = 1.0f);

	inline float x() const { return m_data[0]; }
	inline float y() const { return m_data[1]; }
	inline float z() const { return m_data[2]; }

	inline float r() const { return m_data[0]; }
	inline float g() const { return m_data[1]; }
	inline float b() const { return m_data[2]; }

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
