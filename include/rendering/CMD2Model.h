#if !defined( CMD2_MODEL_H )
#define CMD2_MODEL_H

#include "rendering\CAnimatedMesh.h"
#include "rendering\CTextureMap.h"
#include "rendering\CRenderer.h"
#include "rendering\CMeshBufferPool.h"
#include "rendering\MD2Structs.h"

#define MD2_SCALE	1.0

class CMD2Model : public CAnimatedMesh
{
private:
	MD2Data				*poly_data;
	int					skin_index;
	int					anim_ind;
	float				old_time;
	unsigned int		frame_nr,frame_next_nr;
	float				intrplt_perc;
	vect3d_t*			intrplt_verts;
public:
	CMD2Model();
	CMD2Model(const unsigned int id);
	~CMD2Model();
	void	Render(void);
	int		LoadModel(const unsigned int id);
	void	SetSkinIndex(const int);
	void	NextFrame(float);
	void	SetAnimation(anim_type_t);
};

#endif