#include <rt/solids/env.h>

namespace rt {

	Environment::Environment(CoordMapper* texMapper, Material* material){
		this->texMapper = texMapper;
		this->material = material;
	}

	BBox Environment::getBounds() const {
		return BBox::full();
	}

	Intersection Environment::intersect(const Ray& ray, float previousBestDistance) const 
	{	
		if (previousBestDistance == FLT_MAX) { return Intersection(FLT_MAX, ray, this, Vector::rep(0.0f), Point::rep(0.0f)); }
		return Intersection::failure();

		//return Intersection(FLT_MAX, ray, this, Vector::rep(0.0f), Point::rep(0.0f));
	}

	Solid::Sample Environment::sample() const {
		NOT_IMPLEMENTED;
	}

	float Environment::getArea() const {
		return FLT_MAX;
	}

}
