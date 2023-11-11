#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {
	PointLight::PointLight(const Point& position, const RGBColor& intensity)
	{
		this->position = position;
		this->intensity = intensity;
	}

	LightHit PointLight::getLightHit(const Point& p) const {
		LightHit lh;
		lh.direction = (position - p).normalize();
		lh.distance = (position - p).length();
		lh.normal = -(position - p);
		return lh;
	}

	RGBColor PointLight::getIntensity(const LightHit& irr) const {
		// inv to square of distance
		return (intensity / (irr.distance * irr.distance));
	}
}