#if !defined( CANIMATEDMESH_H )
#define CANIMATEDMESH_H

#include "rendering\CMesh.h"

class CAnimatedMesh : public CMesh
{
private:
public:
	CAnimatedMesh();
	virtual ~CAnimatedMesh();
	virtual void	NextFrame(float) = 0;
	virtual void	SetAnimation(anim_type_t) = 0;
};

#endif