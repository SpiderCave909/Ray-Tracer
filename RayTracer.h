#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

//C++ std using
using std::shared_ptr;
using std::make_shared;

//Constants
const double INFINIT = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

//Utility functions
inline double degrees_to_radians(double degrees) {
	return degrees * PI / 180.0;
}

inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;

	return distribution(generator);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

#include "vector3.h"
#include "color.h"
#include "ray.h"
#include "interval.h"