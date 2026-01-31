#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
	Point3 center;
	double radius;
	shared_ptr<Material> mat;

public:
	Sphere(const Point3 center, double radius, shared_ptr<Material> mat) 
		: center(center), radius(std::fmax(0, radius)), mat(mat) {}

	bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
		Vector3 oc = center - r.origin();
		double a = r.direction().length_squared();
		double h = dot(r.direction(), oc);
		double c = oc.length_squared() - radius * radius;
		double discriminant = h * h - a * c;

		if (discriminant < 0) return false;
		
		double sqrtd = std::sqrt(discriminant);

		//Find the nearest root that lies in the acceptable range
		double root = (h - sqrtd) / a;

		if (!rayT.surrounds(root)) {
			root = (h + sqrtd) / a;

			if (!rayT.surrounds(root)) return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);

		Vector3 outwardNormal = (rec.p - center) / radius;

		rec.set_face_normal(r, outwardNormal);
		rec.mat = mat;

		return true;
	}
};

#endif