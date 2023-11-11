

#include <rt/primmod/bmap.h>
#include <rt/solids/triangle.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/world.h>
#include <core/assert.h>
#include<core/matrix.h>
#include <core/interpolate.h>
#include <core/color.h>
#include <rt/textures/texture.h>

namespace rt {

    BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
    {
        this->base = base;
        this->bm = bumpmap;

        this->bv1 = bv1;
        this->bv2 = bv2;
        this->bv3 = bv3;
        base->texMapper = new TriangleMapper(bv1, bv2, bv3);

        this->vs = vscale;
    }

    BBox BumpMapper::getBounds() const {
        return base->getBounds();
    }

    Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
        Intersection hit_intersection = base->intersect(ray, previousBestDistance);
        if (hit_intersection) {
            Point uvw = base->texMapper->getCoords(hit_intersection);

            Vector xW = (this->base->p2 - this->base->p1).normalize();
            Vector yW = (this->base->p3 - this->base->p1).normalize();
            Vector zW = cross(xW, yW).normalize();
            Matrix worldMatrix = Matrix::system(xW, yW, zW);

            Vector x = (this->bv2 - this->bv1).normalize();
            Vector y = (this->bv3 - this->bv1).normalize();
            Vector z = cross(x, y).normalize();
            Matrix texMatrix = Matrix::system(x, y, z);

            RGBColor dxrgb = this->bm->getColorDX(uvw);
            RGBColor dyrgb = this->bm->getColorDY(uvw);
            float Bu = (dxrgb.r + dxrgb.g + dxrgb.b) / 3; // grayscale
            float Bv = (dyrgb.r + dyrgb.g + dyrgb.b) / 3;

            Vector wx = worldMatrix * (texMatrix * Vector(1, 0, 0));
            Vector wy = worldMatrix * (texMatrix * Vector(0, 1, 0));
            // perturb the normal
            Vector newNormal = (hit_intersection.normal() + (Bu * cross(hit_intersection.normal(), wy) - Bv * cross(hit_intersection.normal(), wx))).normalize();



            return Intersection(hit_intersection.distance, hit_intersection.ray, hit_intersection.solid, newNormal, hit_intersection.local());
        }
        else { return Intersection::failure(); }

    }

    void BumpMapper::setMaterial(Material* m) {
        base->setMaterial(m);
    }

    void BumpMapper::setCoordMapper(CoordMapper* cm) {
        base->setCoordMapper(cm);
    }

    float BumpMapper::getArea() const {
        return 0;
    }

}