#include <rt/lights/spotlight.h>

namespace rt {
	SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
	{
		this->position = position;
		this->direction = direction.normalize();
		this->angle = angle;
		this->power = power;
		this->intensity = intensity;
	}

	RGBColor SpotLight::getIntensity(const LightHit& irr) const {
		
		if (dot(-irr.direction, direction) > cos(angle))
		{
			return (intensity * powf(dot(-irr.direction, direction), power)) / (irr.distance * irr.distance);
		}
		else { return RGBColor::rep(0.0f); }
	}
}