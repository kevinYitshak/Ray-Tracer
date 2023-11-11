#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    
    BBox box = BBox::empty();
  
    for (int i = 0; i < primitives.size(); i++)
    {
        box.extend(primitives[i]->getBounds());
    }
    return box;
    
}

Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const {
    
    // Assignment 2
    // find ray parameter t, of the input ray for which
    // it intersects a primitive.  0 < t < previousBestDistance
    // if t > previousBestDistance don't report.


    Intersection best_obj = Intersection::failure();
    Intersection curr_obj = Intersection::failure();

        
    for (int i = 0; i < primitives.size(); i++)
    {   
        Intersection curr_obj = primitives[i]->intersect(ray, previousBestDistance);
          
        if (curr_obj)
        {   
            //std::cout << curr_obj.distance << std::endl;
            best_obj = curr_obj;
            previousBestDistance = best_obj.distance;
        }
    }
    
    return best_obj;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    
    // to add new primitive to the scene
    this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    
    for (auto primitive : primitives)
    {
        primitive->setMaterial(m);
    }
    
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    
    for (auto primitive : primitives)
    {
        primitive->setCoordMapper(cm);
    }
}

}
