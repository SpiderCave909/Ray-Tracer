#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
	double min, max;

	Interval() : min(INFINIT), max(-INFINIT) {}

	Interval(double min, double max) : min(min), max(max) {}

	double size() const {
		return max - min;
	}

	bool contains(double x) const {
		return (min <= x && x <= max);
	}

	bool surrounds(double x) const {
		return (min < x && x < max);
	}

	double clamp(double x) const {
		if (x < min) return min;

		if (x > max) return max;

		return x;
	}

	static const Interval UNIVERSE, EMPTY;
};

const Interval Interval::EMPTY		= Interval(INFINIT, -INFINIT);
const Interval Interval::UNIVERSE	= Interval(-INFINIT, INFINIT);

#endif