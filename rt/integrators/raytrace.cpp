#include <rt/integrators/raytrace.h>

//-----------------------------------

#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/materials/dummy.h>
#include <rt/solids/solid.h>
#include <rt/coordmappers/coordmapper.h>


namespace rt {
	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
		RGBColor totalIntensity = RGBColor::rep(0.0f);
		Point texPoint;
		Intersection object = world->scene->intersect(ray, FLT_MAX);

		// if ray intersects an object
		if (object)
		{	
			texPoint = object.solid->texMapper->getCoords(object);
			totalIntensity = totalIntensity + object.solid->material->getEmission(texPoint, object.normal(), -ray.d);
			// iterate through light sources
			for (auto light : world->light)
			{
				LightHit hit = light->getLightHit(object.hitPoint());

				// compute shadow ray
				// origin is offseted so that self shadowing is avoided.
				Ray shadowRay = Ray(object.hitPoint() + object.normal() * 0.0001, hit.direction);

				// check shadowray is same dir as primary ray
				if (dot(object.normal(), shadowRay.d) > 0.0f)
				{
					Intersection shadowObj = world->scene->intersect(shadowRay, hit.distance);

					// check shadowray is intersecting the scene
					if (!shadowObj)
					{
						RGBColor c1 = light->getIntensity(hit);
						RGBColor c2 = c1 * object.solid->material->getReflectance(texPoint, object.normal(), -ray.d, hit.direction); 

						totalIntensity = totalIntensity + c2;
					}
				}
			}
			return totalIntensity.clamp();
		}
		else
		{
			return RGBColor::rep(0.0f);
		}
	}
}