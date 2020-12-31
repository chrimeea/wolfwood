#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <rendering\corona.h>
#include <string>
#include "rendering\CTextureBufferPool.h"
#include "utils\Config.h"

CTextureBufferPool *CTextureBufferPool::pool = NULL;

CTextureBufferPool::CTextureBufferPool()
{
	char *m = Config::GetValue("config/texmanager/max");
	if (m) {
		max_buffers = atoi(m);
	}
	m = Config::GetValue("config/texmanager/min");
	if (m) {
		min_buffers = atoi(m);
	}
	Config::ReadMappings(Config::GetValue("config/texmanager/file"), mappings);
}

CTextureBufferPool::~CTextureBufferPool()
{
	freeAll();
}

CTextureBufferPool *CTextureBufferPool::getInstance()
{
	if (pool == NULL)
	{
		pool = new CTextureBufferPool();
	}
	return pool;
}

void CTextureBufferPool::Close()
{
	if (pool != NULL)
	{
		delete pool;
	}
}

bool CTextureBufferPool::Load(BufferData* bd, const char *fname)
{
	int width,height;
	void* pixels=NULL;
	char file_path[MAX_PATH];
	sprintf(file_path,"textures\\%s",fname);
	
	corona::Image* image=corona::OpenImage(file_path);
	if(!image) return false;
	corona::PixelFormat pxformat=image->getFormat();
	switch(pxformat)
	{
	case corona::PF_R8G8B8:
	case corona::PF_R8G8B8A8:
		break;
	case corona::PF_B8G8R8:
	case corona::PF_I8:
		{
			if((image=corona::ConvertImage(image,corona::PF_R8G8B8))==0)
			{
				delete image;
				return false;
			}
			break;
		}
	case corona::PF_B8G8R8A8:
		{
			if((image=corona::ConvertImage(image,corona::PF_R8G8B8A8))==0)
			{
				delete image;
				return false;
			}
			break;
		}
	}
	width=image->getWidth();
	height=image->getHeight();
	pixels=image->getPixels();

	glBindTexture(GL_TEXTURE_2D, bd->bufferId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	if(glGetError() != GL_NO_ERROR)
	{
		//eroare la incarcarea imaginii
		return false;
	}
	
	delete image;

	return true;
}

bool CTextureBufferPool::InitBuffers(BufferData* bd)
{
	glGenTextures(1, &bd->bufferId);
	if(glGetError() != GL_NO_ERROR)
	{
		//eroare creare buffer
		return false;
	}
	return true;
}

bool CTextureBufferPool::DeleteBuffers(unsigned int i, BufferData* bufd)
{
	GLuint* textureNames;
	textureNames = new GLuint[i];
	for(unsigned int j=0;j<i;j++) textureNames[j] = bufd->bufferId;
	glDeleteTextures(i, textureNames);
	if(glGetError() != GL_NO_ERROR)
	{
		//eroare stergere buffere
		return false;
	}
	return true;
}