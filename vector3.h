#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
	//Save info
	double vec3[3];

	//Constructors
	Vector3() : vec3{ 0, 0, 0 } {}

	Vector3(double x, double y, double z) : vec3{x, y, z} {}

	//Get info
	double x() const {
		return vec3[0];
	}

	double y() const {
		return vec3[1];
	}

	double z() const {
		return vec3[2];
	}

	Vector3 operator-() const {
		return Vector3(-vec3[0], -vec3[1], -vec3[2]);
	}

	double operator[](int i) const {
		return vec3[i];
	}

	double& operator[](int i) {
		return vec3[i];
	}

	Vector3& operator+=(const Vector3& v) {
		vec3[0] += v.vec3[0];
		vec3[1] += v.vec3[1];
		vec3[2] += v.vec3[2];

		return *this;
	}

	Vector3& operator*=(double t) {
		vec3[0] *= t;
		vec3[1] *= t;
		vec3[2] *= t;

		return *this;
	}

	Vector3& operator/=(double t) {
		return *this *= 1 / t;
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return vec3[0] * vec3[0] + vec3[1] * vec3[1] + vec3[2] * vec3[2];
	}

	bool near_zero() const {
		double s = 1e-8;

		return (std::fabs(vec3[0]) < s) && (std::fabs(vec3[1]) < s) && (std::fabs(vec3[2]) < s);
	}

	static Vector3 random() {
		return Vector3(random_double(), random_double(), random_double());
	}
	
	static Vector3 random(double min, double max) {
		return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
};

using Point3 = Vector3;

//Vector utility functions
inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
	return out << v.vec3[0] << ' ' << v.vec3[1] << ' ' << v.vec3[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
	return Vector3(u.vec3[0] + v.vec3[0], u.vec3[1] + v.vec3[1], u.vec3[2] + v.vec3[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
	return Vector3(u.vec3[0] - v.vec3[0], u.vec3[1] - v.vec3[1], u.vec3[2] - v.vec3[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
	return Vector3(u.vec3[0] * v.vec3[0], u.vec3[1] * v.vec3[1], u.vec3[2] * v.vec3[2]);
}

inline Vector3 operator*(double t, const Vector3 v) {
	return Vector3(t * v.vec3[0], t * v.vec3[1], t * v.vec3[2]);
}

inline Vector3 operator*(const Vector3 v, double t) {
	return t * v;
}

inline Vector3 operator/(const Vector3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const Vector3& u, const Vector3& v) {
	return	u.vec3[0] * v.vec3[0] +
			u.vec3[1] * v.vec3[1] +
			u.vec3[2] * v.vec3[2];
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.vec3[1] * v.vec3[2] - u.vec3[2] * v.vec3[1],
				   u.vec3[2] * v.vec3[0] - u.vec3[0] * v.vec3[2],
				   u.vec3[0] * v.vec3[1] - u.vec3[1] * v.vec3[0]);
}

inline Vector3 unit_vector(const Vector3& v) {
	return v / v.length();
}

inline Vector3 random_unit_vector() {
	while (true) {
		Vector3 p = Vector3::random(-1, 1);
		double lensq = p.length_squared();

		if (1e-160 < lensq && lensq <= 1) return p / sqrt(lensq);
	}
}

inline Vector3 random_on_hemisphere(const Vector3& normal) {
	Vector3 onUnitSphere = random_unit_vector();

	if (dot(onUnitSphere, normal) > 0.0) return onUnitSphere;
	else return -onUnitSphere;
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) {
	return v - 2 * dot(v, n) * n;
}

#endif