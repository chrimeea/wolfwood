#include "rendering/CMesh.h"

CMesh::CMesh()
{
	m_renderer=NULL;
}

CMesh::CMesh(CRenderer* const p_renderer)
{
	AssignRenderer(p_renderer);
}

CMesh::~CMesh()
{
}
