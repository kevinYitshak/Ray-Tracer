#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

#include <cmath>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    return RGBColor(r - c.r, g - c.g, b - c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
    return ((r == c.r) && (g == c.g) && (b == c.b));
}

bool RGBColor::operator != (const RGBColor& c) const {
    return ((r != c.r) && (g != c.g) && (b != c.b));
}

RGBColor RGBColor::clamp() const {
    RGBColor clamped;
     if (this->r <0)
     {
         clamped.r=0.0;
     }
     else if (this->r>1)
     {
         clamped.r=1.0;
     }
     else
     {
         clamped.r=this->r;
        
     }

     if (this->g <0)
     {
         clamped.g=0.0;
     }
     else if (this->g>1)
     {
         clamped.g=1.0;
     }
     else
     {
         clamped.g=this->g;
        
     }

     if (this->b <0)
     {
         clamped.b=0.0;
     }
     else if (this->b>1)
     {
         clamped.b=1.0;
     }
     else
     {
         clamped.b=this->b;
        
     }

     return clamped;
}

RGBColor RGBColor::gamma(float gam) const {
    return RGBColor(pow(r, gam), pow(g, gam), pow(b, gam));
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator * (const RGBColor& c, float scalar) {
    return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
}

RGBColor operator / (const RGBColor& c, float scalar) {
    return RGBColor(c.r / scalar, c.g / scalar, c.b / scalar);
}

}
