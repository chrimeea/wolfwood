#if !defined(MD2_STRUCTS_H)
#define MD2_STRUCTS_H

#include "vector.h"

#define MD2_MAX_ANIM_TYPE 15
#define MD2_MAGIC_NUMBER (844121161)
#define MD2_VERSION	8

typedef struct
{
   int magic;
   int version;
   int skinWidth;
   int skinHeight;
   int frameSize;
   int numSkins;
   int numVertices;
   int numTexCoords;
   int numTriangles;
   int numGlCommands;
   int numFrames;
   int offsetSkins;
   int offsetTexCoords;
   int offsetTriangles;
   int offsetFrames;
   int offsetGlCommands;
   int offsetEnd;
} md2_header;

typedef struct
{
   unsigned char vertex[3];
   unsigned char lightNormalIndex;
} md2_vertex;

typedef struct
{
	float		scale[3];
	float		translate[3];
	char		name[16];
	md2_vertex	vertices[1];
} md2_frame;

typedef struct
{
	vect3d_t*	vertices;
	int*		norm_inds;
} md2_anim_frame_t;

typedef struct
{
	unsigned int	start;
	unsigned int	end;
	char			fps;
} md2_animation_t;

struct MD2Data {
	md2_anim_frame_t*	frames;
	int*				glcmds;
	md2_animation_t		animations[MD2_MAX_ANIM_TYPE+1];
	int					num_frames;
	int					num_glcmds;
	int					num_skins;
	int					num_vertices;
	int					frame_size;
	CTextureMap*		skins;
};

#endif