#include <string.h>
#include "rendering\CMaterial.h"

CMaterial::CMaterial()
{
    for(int i=0;i<4;i++)
    {
        diffuse_color[i]=0.0;
        ambient_color[i]=0.0;
        specular_color[i]=0.0;
    }
    strcpy(name,"\0");
    texture1_present=0;
    shininess=10;
}

CMaterial::CMaterial(CMaterial& rMaterial)
{
    for(int i=0;i<4;i++)
    {
        diffuse_color[i]=rMaterial.diffuse_color[i];
        ambient_color[i]=rMaterial.ambient_color[i];
        specular_color[i]=rMaterial.specular_color[i];
    }
    strcpy(name,rMaterial.name);
    texture1_present=rMaterial.texture1_present;
    texture1=rMaterial.texture1;
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetName(char* nm)
{
    strcpy(name,nm);
}
