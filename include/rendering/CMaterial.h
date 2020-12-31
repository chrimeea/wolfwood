#if !defined( CMATERIAL_H )
#define CMATERIAL_H

#define MATERIAL_MAX_NAME_LENGTH 50

#include <stdlib.h>
#include "rendering\CTextureMap.h"

class CMaterial
{
    //Attributes
private:
public:
    float diffuse_color[4];
    float ambient_color[4];
    float specular_color[4];
    int shininess;
    CTextureMap texture1;
    bool texture1_present;
    char name[MATERIAL_MAX_NAME_LENGTH];

    //Methods
private:
public:
    //Construction
    CMaterial();
    CMaterial(CMaterial&);

    //Destruction
    ~CMaterial();

    //Set
    void SetName(char*);
};

#endif