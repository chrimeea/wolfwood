#if !defined( CMESH_H )
#define CMESH_H

#define MESH_FOLDER "models\\"

#include "rendering\CRenderer.h"

typedef enum
{
	ANIM_STAND=0,
	ANIM_RUN,
	ANIM_ATTACK,
	ANIM_PAIN,
	ANIM_JUMP,
	ANIM_FLIP,
	ANIM_SALUTE,
	ANIM_TAUNT,
	ANIM_WAVE,
	ANIM_SPOINT,
	ANIM_CRSTAND,
	ANIM_CRWALK,
	ANIM_CRATTACK,
	ANIM_CRPAIN,
	ANIM_CRDEATH,
	ANIM_DEATH
} anim_type_t;

struct MeshData {
	vect3d_t*	vertices;
};

class CMesh
{
private:
protected:

	CRenderer*			m_renderer;

public:
private:
public:

	CMesh();
	CMesh(CRenderer* const);
	virtual ~CMesh();

	int				AssignRenderer( CRenderer* const p_renderer)
						{ return ((m_renderer=p_renderer)!=NULL?1:0); }
	virtual void	Render(void) = 0;
	virtual int		LoadModel(const unsigned int) = 0;
};

#endif