#include <string.h>
#include "rendering\CTextureMap.h"

CTextureMap::CTextureMap()
{
    strcpy(file_name,"\0");
    tex_envmode=GL_MODULATE;
    texture_id[0]=0;
}

CTextureMap::CTextureMap(CTextureMap& rTextureMap)
{
    strcpy(file_name,rTextureMap.file_name);
    tex_envmode=rTextureMap.tex_envmode;
    texture_id[0]=rTextureMap.texture_id[0];
}

CTextureMap::~CTextureMap()
{
	glDeleteTextures(1,texture_id);
}