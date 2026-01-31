#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray {
	Point3 orig;
	Vector3 dir;

public:
	Ray() {}

	Ray(const Point3& origin, const Vector3& direction) : orig(origin), dir(direction) {}

	const Point3& origin() const {
		return orig;
	}

	const Vector3& direction() const {
		return dir;
	}

	Point3 at(double t) const {
		return orig + t * dir;
	}
};

#endif