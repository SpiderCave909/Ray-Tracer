#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"
#include "interval.h"

using Color = Vector3;

inline double linear_to_gamma(double linearComponent) {
	if (linearComponent > 0) return std::sqrt(linearComponent);

	return 0;
}

void write_color(std::ostream& out, const Color& pixelColor) {
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();

	//Apply a linear to gamma transform for gamma 2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	//Translate color to be 0..255
	static const Interval INTENSITY(0.000, 0.999);

	int rByte = int(256 * INTENSITY.clamp(r));
	int gByte = int(256 * INTENSITY.clamp(g));
	int bByte = int(256 * INTENSITY.clamp(b));

	//Write the pixel color
	out << rByte << ' ' << gByte << ' ' << bByte << "\n";
}

#endif