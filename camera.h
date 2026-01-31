#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class Camera {
	int imageHeight;			//Render image height
	Point3 cameraCenter;		//Camera center
	Vector3 pixel100Loc;		//Location of pixel 0, 0
	Vector3 pixelDelta_u;		//Offset pixel to the right
	Vector3 pixelDelta_v;		//Offset pixel below
	double pixelSamplesScene;	//Color scale factor for a sum of pixel samples

	void initialize() {
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		pixelSamplesScene = 1.0 / samplesPerPixel;

		cameraCenter = Point3(0, 0, 0);

		//Determine viewport dimensions
		double focalLength = 1.0;
		double viewportHeight = 2.0;
		double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

		//Calculate the vectors across the horizontal and down the vertical viewport edges
		Vector3 viewport_u = Vector3(viewportWidth, 0, 0);
		Vector3 viewport_v = Vector3(0, -viewportHeight, 0);

		//Calculate the horizontal and vertical delta vectors from pixel to pixel
		pixelDelta_u = viewport_u / imageWidth;
		pixelDelta_v = viewport_v / imageHeight;

		//Calculate the location of the upper left pixel
		Vector3 viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
		pixel100Loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);
	}

	Color ray_color(const Ray& r, int depth, const Hittable& world) {
		if (depth < 1) return Color(0, 0, 0);
		
		HitRecord rec;

		if (world.hit(r, Interval(0.001, INFINITY), rec)) {
			Ray scattered;
			Color attenuation;

			if (rec.mat->scatter(r, rec, attenuation, scattered)) return attenuation * ray_color(scattered, depth - 1, world);

			return Color(0, 0, 0);
		}

		Vector3 unitDirection = unit_vector(r.direction());
		double a = 0.5 * (unitDirection.y() + 1.0);

		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}

	Ray get_ray(int k, int i) const {
		Vector3 offset = sample_square();
		Vector3 pixelSample = pixel100Loc + ((k + offset.x()) * pixelDelta_u) + ((i + offset.y()) * pixelDelta_v);

		Point3 rayOrigin = cameraCenter;
		Point3 rayDirection = pixelSample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	Vector3 sample_square() const {
		return Vector3(random_double() - 0.5, random_double() - 0.5, 0);
	}

public:
	double aspectRatio = 1.0;		//Ratio of image with over height
	int imageWidth = 100;			//Render image width in pixel count
	int samplesPerPixel = 10;		//Count of random samples for each pixel
	int maxDepth = 10;				//Max number of ray bounces into secene

	void render(const Hittable& world) {
		initialize();

		std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int i = 0; i < imageHeight; i++) {
			std::clog << "\rScanlines remaining: " << (imageHeight - i) << std::flush;

			for (int k = 0; k < imageWidth; k++) {
				Color pixelColor(0, 0, 0);

				for (int sample = 0; sample < samplesPerPixel; sample++) {
					Ray r = get_ray(k, i);

					pixelColor += ray_color(r, maxDepth, world);
				}

				write_color(std::cout, pixelSamplesScene * pixelColor);
			}
		}

		std::clog << "\rDone! \n";
	}
};

#endif