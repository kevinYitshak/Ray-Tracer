#include <rt/lights/arealight.h>
#include <core/color.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

	AreaLight::AreaLight(Solid* source)
	{
		this->source = source;
	}

	LightHit AreaLight::getLightHit(const Point& p) const {

		Point position = source->sample().point;

		LightHit lh;
		lh.direction = (position - p).normalize();
		lh.distance = (position - p).length() - 0.00015f;
		lh.normal = source->sample().normal;
		return lh;
	}

	RGBColor AreaLight::getIntensity(const LightHit& irr) const {
		
		//dummy arguments for now, as per the sheet.
		RGBColor intensity = source->material->getEmission(Point(), Vector(), Vector());
		float cosTheta = fabsf(dot(irr.normal, irr.direction));

		return intensity * source->getArea() * cosTheta / (irr.distance * irr.distance);
	}

}