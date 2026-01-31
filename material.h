#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
		return false;
	}
};

class Lambertian : public Material {
	Color albedo;

public:
	Lambertian(const Color& albedo) : albedo(albedo) {}

	bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
		Vector3 scatterDirection = rec.normal + random_unit_vector();

		if (scatterDirection.near_zero()) scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;

		return true;
	}
};

class Metal : public Material {
	Color albedo;

public:
	Metal(const Color& albedo) : albedo(albedo) {}

	bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
		Vector3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return true;
	}
};

#endif