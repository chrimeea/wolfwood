#if !defined( CLIGHT_H )
#define CLIGHT_H

#include "rendering\vector.h"

class CLight
{
    //Attributes
public:
    float ambient_color[4];
    float diffuse_color[4];
    float specular_color[4];
    float position[4];
    float spot_cutoff;
    float spot_exponent;
    vect3d_t spot_direction;
    float const_att;
    float line_att;
    float quad_att;

    //Methods
public:
    //Construction
    CLight();
    CLight(CLight&);

    //Destruction
    ~CLight();
};

#endif