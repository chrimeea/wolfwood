#pragma warning(disable : 4786)

#include "background\CImageAreaBufferPool.h"
#include "utils\Config.h"
#include "rendering\corona.h"
#include <string>
#include <fstream>
#include <algorithm>

CImageAreaBufferPool *CImageAreaBufferPool::pool = NULL;

CImageAreaBufferPool::CImageAreaBufferPool()
{
	char *m = Config::GetValue("config/imageareamanager/max");
	if (m) {
		max_buffers = atoi(m);
	}
	m = Config::GetValue("config/imageareamanager/min");
	if (m) {
		min_buffers = atoi(m);
	}
}

CImageAreaBufferPool::~CImageAreaBufferPool()
{
	freeAll();
}
	
CImageAreaBufferPool *CImageAreaBufferPool::getInstance()
{
	if (pool == NULL)
	{
		pool = new CImageAreaBufferPool();
	}
	return pool;
}

void CImageAreaBufferPool::Close()
{
	if (pool != NULL)
	{
		delete pool;
	}
}

bool CImageAreaBufferPool::Load(BufferData* bd, const char *fname)
{
	int width,height;
	unsigned char *pixels = NULL;
	corona::Image *image = NULL;
	ImageAreaData *p = (ImageAreaData *)(bd->data);

	std::string file_path(fname);
	file_path += EXTENSION;
	
	image = corona::OpenImage(file_path.c_str());
	if(!image) return false;
	width = image->getWidth();
	height = image->getHeight();
	pixels = (unsigned char *)image->getPixels();

	p->imgareapx = new unsigned char[width * height * 4];
	memcpy((void *)p->imgareapx, (void *)pixels, width * height * 4);
	delete image;

	file_path.insert(file_path.find_last_of('\\') + 1, 1, 'z');
	file_path.replace(file_path.length() - 3, 3, 1, 'z');
	p->zimgareapx = new float[width * height];
	std::ifstream fz(file_path.c_str());
	fz.read((char *)p->zimgareapx, width * height * sizeof(float));
	fz.close();
	
	return true;
}

bool CImageAreaBufferPool::InitBuffers(BufferData* bd)
{	
	bd->data = new ImageAreaData;
	return true;
}

bool CImageAreaBufferPool::DeleteBuffers(unsigned int c, BufferData* bufd)
{
	for(int i = 0; i < c; i++)
	{
		ImageAreaData *pdata = (ImageAreaData *)(bufd[i].data);
		if(pdata)
		{
			if(pdata->imgareapx) delete[] pdata->imgareapx;
			if(pdata->zimgareapx) delete[] pdata->zimgareapx;
			free(pdata);
		}
	}
	return true;
}