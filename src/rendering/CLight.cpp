#include "rendering\CLight.h"

CLight::CLight()
{
    for(int i=0;i<4;i++)
    {
        if(i<3) ambient_color[i]=0.0;
        else ambient_color[i]=1.0;
        if(i!=2) position[i]=0.0;
        else position[i]=1.0;
        diffuse_color[i]=specular_color[i]=1.0;
    }
    spot_exponent=0.0;
    spot_cutoff=180.0;
    const_att=1.0;
    line_att=0.0;
    quad_att=0.0;
}

CLight::CLight(CLight& rLight)
{
    for(int i=0;i<4;i++)
    {
        ambient_color[i]=rLight.ambient_color[i];
        diffuse_color[i]=rLight.diffuse_color[i];
        specular_color[i]=rLight.specular_color[i];
    }
    spot_exponent=rLight.spot_exponent;
    spot_cutoff=rLight.spot_cutoff;
    const_att=rLight.const_att;
    line_att=rLight.line_att;
    quad_att=rLight.quad_att;
}

CLight::~CLight()
{
}