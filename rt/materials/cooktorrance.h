#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <vector>

namespace rt {

class CookTorranceMaterial: public Material {
public:

	CookTorranceMaterial(Texture* tex, float kd, float ks, float rho, float abs_coef, float m);
	virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
	virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual Sampling useSampling() const;

private:
	Texture* tex;

	float pd; // diffusivity
	float ps; // specular term
	float rho; // density term
	float absorption_coefficient;
	float m; // average slope of microfacet
	float alpha; // angle to avg normal of surface;
};

}

#endif