#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/pointlight.h>

namespace rt {

	class ProjLight : public PointLight {
	public:
		ProjLight() {}
		ProjLight(const Point& position, const RGBColor& intensity);
		
		virtual RGBColor getIntensity(const LightHit& irr) const;
	};

}

#endif
