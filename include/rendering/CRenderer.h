#if !defined( CRENDERER_H )
#define CRENDERER_H

#include <stdio.h>
#include "rendering\CTextureMap.h"
#include "rendering\CMaterial.h"
#include "rendering\CLight.h"
#include "rendering\vector.h"
#include "rendering\FontSet.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

typedef struct
{
	float s,t;
} texcoord_t;

class CRenderer
{
private:

    static			CRenderer* renderer;
    CLight			global_light;
	FontSet *fontSet;
	char			gl_version[5];
	unsigned char	bit_vertex_array_refcnt;
	bool			render_to_pos;

public:

private:

    CRenderer();
    ~CRenderer();

	int				IsExtensionSupported(char*);
	void			InitGLExtensions();
    void			SetGlobalLight();

public:

    static CRenderer* GetInstance();

	static void Close() { delete renderer; };

    void InitializeGL();
    void ResizeScene(int,int);
    void BeginScene();
    void EndScene();
    void BeginRender(unsigned);
    void EndRender();
	void Translate(vect3d_t);
	void Rotate(float,vect3d_t);
    void SetTexture(CTextureMap*);
    void SetMaterial(CMaterial*);
    void SetLight(CLight*);
    void SetVertex(vect3d_t*);
    void SetTexCoords(float*);
	void SetTexCoords(texcoord_t*);
    void SetNormal(vect3d_t*);
    int	 LoadTexture(CTextureMap*);
	void SetFrontFace(int);
	void BeginRenderToPos(float,float);
	void EndRenderToPos();
	void DrawGrid();
	void ExportGLExtensionsToTXT();
	void DrawArea(int, int, unsigned, unsigned, int, int, unsigned, const void *, const void *);
	void ScrollArea(int, int, unsigned, unsigned, int, int);
	void DrawText(int, int, unsigned, unsigned, unsigned, const char *);
};

#endif