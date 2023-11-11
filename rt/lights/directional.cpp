#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {
	DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
	{
		this->direction = direction;
		this->color = color;
	}

	LightHit DirectionalLight::getLightHit(const Point& p) const {
		LightHit lh;
		lh.distance = FLT_MAX;
		lh.direction = -direction;
		lh.normal = direction;
		return lh;
	}

	RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
		return color;
	}
}