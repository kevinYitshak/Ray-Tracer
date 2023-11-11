#include <rt/cameras/perspective.h>
#include <math.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{	
	// given up and forward vectors are reference vectors required to align the camera upright
	// the reference vectors need not to be orthogonal.
	this->center = center;
	this->d = 1;
	
	// Calculating orthogonal basis vectors from reference vectors
	this->d = 1; // focal length dist bw the camera and image plane
	this->w = - forward.normalize(); // vector looking backwards w.r.t the camera
	this->v =  cross(up, w).normalize(); //right vector w.r.t camera
	this->u =  cross(w, v).normalize(); //  up vector w.r.t camera
	
	this->ho = horizontalOpeningAngle;
	this->vo = verticalOpeningAngle;

}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    
	// the view direction is -w
  	// vo/2 and ho/2 are used to calculate half-height and half-width of the image plane

	Vector direction = (- d * w) + (d * tan(ho / 2) * x * v) + (d * tan(vo / 2) * y * u);
	return Ray(center, direction.normalize());
}

}
