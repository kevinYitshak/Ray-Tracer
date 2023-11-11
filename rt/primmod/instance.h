#ifndef CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER
#define CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER

#include <core/vector.h>
#include <rt/primitive.h>
#include <core/matrix.h>

namespace rt {
	class Instance : public Primitive {
	public:

		//Primitive* archetype;
		// initialize the transformation and
		// inv transformation
		//Matrix T, T_inv;

		// initialize the bounding box for the primitive
		//BBox t_box;

		Instance(Primitive* content);
		Primitive* content();

		void reset(); //reset transformation back to identity
		void translate(const Vector& t);
		void rotate(const Vector& axis, float angle);
		void scale(float scale);
		void scale(const Vector& scale);

		virtual BBox getBounds() const;
		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
		virtual void setMaterial(Material* m);
		virtual void setCoordMapper(CoordMapper* cm);
	
	private:
		Primitive* archetype;
		Matrix transformation;// should check if this is correct.
		Matrix invTrans;
		//We store the bounding box for the instance, which is updated with each transformation on the primitive
		BBox instanceBounds;

		void computeBounds();
	
	};
}

#endif