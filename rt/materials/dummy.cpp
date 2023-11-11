#include <rt/materials/dummy.h>
#include <core/assert.h>
#include <math.h>

namespace rt {
	DummyMaterial::DummyMaterial() {
		/* TODO */
	}

	RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
		/*computes the amount of light that is reflected on
		a material surface.

		Depends upon:
			inDir: dir vector of incoming light [world space co-or]
			outDir: dir vector of reflected light -> to the viewer
			normal: surface normal at hit point
			texPoint: local hit co-or Intersection::local()

		Reflectance fr = 1;
		Lo = Le + fr * Li * cos(theta_i)
		*/
		// cosTheta is the angle between normal and inDir;

		float cosTheta = dot(normal.normalize(), inDir.normalize());

		return RGBColor::rep(fabsf(cosTheta));
	}

	RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
		return RGBColor::rep(0.0f);
	}

	Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
		/* TODO */ NOT_IMPLEMENTED;
	}
}