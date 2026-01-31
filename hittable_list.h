#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

class HittableList : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList() {}

	HittableList(shared_ptr<Hittable> obj) {
		add(obj);
	}

	void add(shared_ptr<Hittable> obj) {
		objects.push_back(obj);
	}

	bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
		HitRecord tempRec;
		bool hitAnything = false;
		double clossestSoFar = rayT.max;

		for (const auto& obj : objects) {
			if (obj->hit(r, Interval(rayT.min, clossestSoFar), tempRec)) {
				hitAnything = true;
				clossestSoFar = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
};

#endif