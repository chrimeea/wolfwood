#include "rendering\CMeshBufferPool.h"
#include "utils\Config.h"
#include "rendering\CRenderer.h"
#include "rendering\MD2Structs.h"
#include "utils\Logger.h"

CMeshBufferPool *CMeshBufferPool::pool = NULL;

CMeshBufferPool::CMeshBufferPool()
{
	char *m = Config::GetValue("config/meshmanager/max");
	if (m) {
		max_buffers = atoi(m);
	}
	m = Config::GetValue("config/meshmanager/min");
	if (m) {
		min_buffers = atoi(m);
	}
	Config::ReadMappings(Config::GetValue("config/meshmanager/file"), mappings);
}

CMeshBufferPool::~CMeshBufferPool()
{
	freeAll();
}

CMeshBufferPool *CMeshBufferPool::getInstance()
{
	if (pool == NULL)
	{
		pool = new CMeshBufferPool();
	}
	return pool;
}

void CMeshBufferPool::Close()
{
	if (pool != NULL)
	{
		delete pool;
	}
}

bool CMeshBufferPool::Load(BufferData* bd, const char *fname)
{
	// incarca datele din fisierul de tip MD2

	FILE*			pf;
	md2_header		md2h;
	md2_frame*		frame;
	char*			buffer;
	char			frame_name[16]="\0";
	int				i,current_frame_type;
	char			file_path[CBPOOL_MAX_FILE_NAME];

	sprintf(file_path,"models\\%s", fname);
	pf=fopen(file_path, "rb");
	if(!pf) return 0;

	fread(&md2h,sizeof(md2_header), 1, pf);
	if(ferror(pf))
	{
		fclose(pf);
		return 0;
	}

	if(md2h.magic!=MD2_MAGIC_NUMBER || md2h.version!=MD2_VERSION)
	{
		fclose(pf);
		return 0;
	}

	MD2Data *pdata = (MD2Data*)(bd->data);

	pdata->frame_size = md2h.frameSize;
	pdata->num_frames = md2h.numFrames;
	pdata->num_glcmds = md2h.numGlCommands;
	pdata->num_skins = md2h.numSkins;
	pdata->num_vertices = md2h.numVertices;

	for(i = 0; i < MD2_MAX_ANIM_TYPE + 1; i++)
		pdata->animations[i].fps = 20;

	pdata->frames = new md2_anim_frame_t[md2h.numFrames];
	for(i=0;i<md2h.numFrames;i++)
	{
		pdata->frames[i].vertices=new vect3d_t[md2h.numVertices];
		pdata->frames[i].norm_inds=new int[md2h.numVertices];
	}

	pdata->skins=new CTextureMap[md2h.numSkins];
	pdata->glcmds=new int[md2h.numGlCommands];

	buffer=new char[md2h.numFrames*md2h.frameSize];

	fseek(pf,md2h.offsetSkins,SEEK_SET);
	for(i=0;i<md2h.numSkins;i++)
	{
		char fname[64];
		fread((char*)fname,64,1,pf);
		strcpy(pdata->skins[i].file_name,strrchr(fname,'/')+1);
	}

	fseek(pf,md2h.offsetFrames,SEEK_SET);
	fread((int*)buffer,md2h.frameSize,md2h.numFrames,pf);

	current_frame_type=-1;
	for(i=0;i<md2h.numFrames;i++)
	{
		frame=(md2_frame*)&buffer[md2h.frameSize*i];
		
		if(strncmp(frame_name,frame->name,strlen(frame->name)-3)!=0)
		{
			if(current_frame_type>=0) pdata->animations[current_frame_type].end=i-1;
			pdata->animations[++current_frame_type].start=i;
		}
		for(int u=0;u<16;u++) strcpy(frame_name+u,"");
		strncpy(frame_name,frame->name,strlen(frame->name)-3);

		for(int j=0;j<md2h.numVertices;j++)
		{
			float x, y, z;
			x = ((frame->vertices[j].vertex[0])*(frame->scale[0])+(frame->translate[0]));
			y = (frame->vertices[j].vertex[1])*(frame->scale[1])+(frame->translate[1]);
			z = (frame->vertices[j].vertex[2])*(frame->scale[2])+(frame->translate[2]);

			pdata->frames[i].vertices[j].x = x;
			pdata->frames[i].vertices[j].y = z;
			pdata->frames[i].vertices[j].z = -y;

			pdata->frames[i].norm_inds[j]=frame->vertices[j].lightNormalIndex;
		}
	}
	pdata->animations[current_frame_type].end=i;

	delete [] buffer;

	fseek(pf,md2h.offsetGlCommands,SEEK_SET);
	fread((char*)pdata->glcmds,sizeof(int),md2h.numGlCommands,pf);

	fclose(pf);

	return true;
}

bool CMeshBufferPool::InitBuffers(BufferData* bd)
{	
	// aloca memorie pentru structura MD2Data

	bd->data = (MD2Data *)malloc(sizeof(MD2Data));

	return true;
}

bool CMeshBufferPool::DeleteBuffers(unsigned int c, BufferData* bufd)
{
	// sterge memoria folosita de structura MD2Data

	for(int i = 0; i < c; i++)
	{
		MD2Data *pdata = (MD2Data *)(bufd[i].data);

		if(pdata != NULL)
		{
			if(pdata->frames != NULL)
			{
				for(int j = 0; j < pdata->num_frames; j++)
				{
					if((pdata->frames[j]).vertices != NULL)
						delete[] (pdata->frames[j]).vertices;
					if((pdata->frames[j]).norm_inds != NULL)
						delete[] (pdata->frames[j]).norm_inds;
				}
				delete[] pdata->frames;
			}
	
			if(pdata->glcmds != NULL) delete [] pdata->glcmds;
			if(pdata->skins != NULL) delete [] pdata->skins;

			free(pdata);
		}
	}

	return true;
}