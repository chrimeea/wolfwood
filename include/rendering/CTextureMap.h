#if !defined( CTEXTUREMAP_H )
#define CTEXTUREMAP_H

#include <stdlib.h>
#include <windows.h>
#include <gl\gl.h>

class CTextureMap
{
    //Attributes
private:
public:
    char file_name[_MAX_FNAME];
    float tex_envmode;
    unsigned int texture_id[1];

    //Methods
private:
public:
    //Construction
    CTextureMap();
    CTextureMap(CTextureMap&);

    //Destruction
    ~CTextureMap();
};

#endif