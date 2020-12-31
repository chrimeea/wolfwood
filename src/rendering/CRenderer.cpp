#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "rendering\corona.h"
#include "rendering\CRenderer.h"
#include "rendering\GLExtensions_Defs.h"
#include "rendering\CTextureBufferPool.h"
#include <fstream>

CRenderer* CRenderer::renderer=NULL;

CRenderer::CRenderer()
{
	bit_vertex_array_refcnt=0;
	render_to_pos = false;

	global_light.position[0]=300.0;
	global_light.position[1]=3000.0;
	global_light.position[2]=350.0;
	global_light.position[3]=0.0;
	global_light.ambient_color[0]=0.0;
	global_light.ambient_color[1]=0.0;
	global_light.ambient_color[2]=0.0;
	global_light.ambient_color[3]=1.0;
	for(int i=0;i<4;i++)
		global_light.specular_color[i]=global_light.diffuse_color[i]=1.0;
	CTextureBufferPool::getInstance();
	fontSet = new FontSet();
}

CRenderer::~CRenderer()
{
	CTextureBufferPool::Close();
	delete fontSet;
}

CRenderer* CRenderer::GetInstance()
{
	if(NULL==renderer) renderer=new CRenderer();
	return renderer;
}

void CRenderer::DrawText(int x, int y, unsigned cr, unsigned cg, unsigned cb, const char *s)
{
	glShadeModel(GL_FLAT);
	glColor3d(cr, cg, cb);
	glRasterPos2i(x, y);
	fontSet->DrawLetter(s);
	glShadeModel(GL_SMOOTH);
}

void CRenderer::BeginScene()
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(250.0,200.0,250.0,0.0,10.0,0.0,0.0,1.0,0.0);
}


void CRenderer::EndScene()
{
	glFlush();
}

void CRenderer::BeginRender(unsigned int mode)
{
	glBegin(mode);
}

void CRenderer::EndRender()
{
	glEnd();
}

void CRenderer::SetTexture(CTextureMap* t)
{
	if(t!=NULL)
		glBindTexture(GL_TEXTURE_2D,t->texture_id[0]);
	else
		glBindTexture(GL_TEXTURE_2D,0);
}

void CRenderer::SetMaterial(CMaterial* m)
{
	if(m!=NULL)
	{
	  glMaterialfv(GL_FRONT,GL_AMBIENT,m->ambient_color);
	  glMaterialfv(GL_FRONT,GL_DIFFUSE,m->diffuse_color);
	  glMaterialfv(GL_FRONT,GL_SPECULAR,m->specular_color);
	  glMateriali(GL_FRONT,GL_SHININESS,m->shininess);
	}
	else 
	{
		float def_amb[4]={(float)1.0,(float)1.0,(float)1.0,(float)1.0};
		float def_diff[4]={(float)1.0,(float)1.0,(float)1.0,(float)1.0};
		float def_spec[4]={0.2f,0.2f,0.2f,1.0f};
		float def_shin=0.0;
		glMaterialfv(GL_FRONT,GL_AMBIENT,def_amb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,def_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,def_spec);
		glMaterialf(GL_FRONT,GL_SHININESS,def_shin);
	}
}

void CRenderer::SetLight(CLight* l)
{
	if(l!=NULL)
	{
		glLightfv(GL_LIGHT0,GL_AMBIENT,l->ambient_color);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,l->diffuse_color);
		glLightfv(GL_LIGHT0,GL_SPECULAR,l->specular_color);
		glLightfv(GL_LIGHT0,GL_POSITION,l->position);
		if(!glIsEnabled(GL_LIGHTING))
			glEnable(GL_LIGHTING);
		if(!glIsEnabled(GL_LIGHT0))
			glEnable(GL_LIGHT0);
	}
}

void CRenderer::SetVertex(vect3d_t* v)
{
	glVertex3f(v->x,v->y,v->z);
}

void CRenderer::SetTexCoords(float* tc)
{
	glTexCoord2fv(tc);
}

void CRenderer::SetTexCoords(texcoord_t* tc)
{
	glTexCoord2f(tc->s,tc->t);
}

void CRenderer::SetNormal(vect3d_t* v)
{
	glNormal3f(v->x,v->y,v->z);
}

void CRenderer::InitializeGL()
{
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	SetGlobalLight();

	InitGLExtensions();
}

void CRenderer::ResizeScene(int width,int height)
{
	if (height==0)
	{
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,10000.0f);
}

int CRenderer::LoadTexture(CTextureMap* t)
{
	// foloseste CTextureBufferPool pentru a incarca cu maxim de eficienta o textura
	t->texture_id[0] = ((BufferData *)(CTextureBufferPool::getInstance()->getBuffer((const char *)t->file_name)))->bufferId;
	return 1;
}

void CRenderer::SetFrontFace(int ff)
{
	if(ff == GL_CW || ff == GL_CCW)
	{
		glFrontFace((GLint)ff);
	}
}

void CRenderer::SetGlobalLight()
{
	float scene_amb[4]={1.0,1.0,1.0,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,scene_amb);
	SetLight(&global_light);
}

void CRenderer::ExportGLExtensionsToTXT()
{
	const GLubyte* exts=NULL;
	exts=glGetString(GL_EXTENSIONS);
	FILE* f=fopen("gl_exts.txt","wt");
	fprintf(f,"Supported extensions by OpenGL implementation:\n\n");
	int i=0;
	while(exts[i]!='\0')
	{
		while(exts[i]!=' ')
			fprintf(f,"%c",exts[i++]);
		fprintf(f,"\n");
		i++;
	}
	fclose(f);
}

void CRenderer::Translate(vect3d_t v)
{
	glTranslatef(v.x,v.y,v.z);
}

void CRenderer::Rotate(float dgr, vect3d_t v)
{
	glRotatef(dgr,v.x,v.y,v.z);
}

void CRenderer::DrawGrid()
{
	int tile_size=16;
	int	width=100;
	int height=100;

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT,GL_LINE);

	glBegin(GL_QUADS);
	glColor3f(0.0f,0.0f,0.666f);
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			glVertex3f((float)i*tile_size,0.0f,(float)j*tile_size);
			glVertex3f((float)i*tile_size,0.0f,(float)(j+1)*tile_size);
			glVertex3f((float)(i+1)*tile_size,0.0f,(float)(j+1)*tile_size);
			glVertex3f((float)(i+1)*tile_size,0.0f,(float)j*tile_size);
		}
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void CRenderer::BeginRenderToPos(float x,float z)
{
	GLint mtxmode;
	glGetIntegerv(GL_MATRIX_MODE, &mtxmode);
	if(mtxmode == GL_MODELVIEW)
	{
		glPushMatrix();
		glTranslatef((GLfloat)x, (GLfloat)0.0, (GLfloat)z);
		render_to_pos = true;
	}
}

void CRenderer::EndRenderToPos()
{
	if(render_to_pos == true)
	{
		GLint mtxmode;
		glGetIntegerv(GL_MATRIX_MODE, &mtxmode);
		if(mtxmode == GL_MODELVIEW)
		{
			glPopMatrix();
		}
	}
}

//Private Methods

void CRenderer::InitGLExtensions()
{
	const GLubyte* glver=NULL;
	glver=glGetString(GL_VERSION);
	strcpy(gl_version,"\0");
	strcpy(gl_version,(const char*)glver);
}


int CRenderer::IsExtensionSupported(char* extension)
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	start = extensions;
	for (;;)
	{
		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where) break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
		if (*terminator == ' ' || *terminator == '\0')
			return 1;
		start = terminator;
	}
	return 0;
}

void CRenderer::DrawArea(int x,
						 int y,
						 unsigned width,
						 unsigned height,
						 int skipx,
						 int skipy,
						 unsigned rowlength,
						 const void *pixels,
						 const void *depth)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, (GLfloat)SCREEN_WIDTH, (GLfloat)SCREEN_HEIGHT, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, skipx);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, skipy);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, rowlength);
			glRasterPos2i(x, y);
			//glDrawBuffer(GL_BACK);
			//Logger::Log("**********");
			glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			//Logger::Log("******C***");
			glDrawBuffer(GL_NONE);
			//Logger::Log("**********");
			//glDrawPixels(width, height, GL_DEPTH_COMPONENT, GL_FLOAT, depth);
			//Logger::Log("******D***");
			glDrawBuffer(GL_BACK);
			glPopAttrib();
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CRenderer::ScrollArea(int startx,
						   int starty,
						   unsigned width,
						   unsigned height,
						   int endx,
						   int endy)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, (GLfloat)SCREEN_WIDTH, (GLfloat)SCREEN_HEIGHT, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glRasterPos2i(endx, endy);
			glReadBuffer(GL_FRONT);
			glDrawBuffer(GL_BACK);
			glCopyPixels(startx, starty, width, height, GL_COLOR);
//			glDrawBuffer(GL_NONE);
//			glCopyPixels(startx, starty, width, height, GL_DEPTH);
			glPopAttrib();
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}