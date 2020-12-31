#if !defined( C3DSModel_H )
#define C3DSModel_H

#include "rendering\CMesh.h"

struct MeshSubDivision
{
    unsigned int	mat_index;
    unsigned short			n_entries;
    unsigned short*			faces_indices;
};
class C3DSModel:public CMesh
{
private:

    vect3d_t*	vertices;
    float*		texcoords;
    unsigned short*		faces;
    vect3d_t*	face_normals;
	vect3d_t*	normals;
    unsigned short		n_vertices;
	unsigned short		n_texcoords;
    unsigned short		n_faces;

public:

    CMaterial*			materials;
    MeshSubDivision*	subdivisions;
    unsigned short		n_subdivisions;
    unsigned short		n_materials;
	vect3d_t			camera_pos;
	vect3d_t			camera_target;

private:
	int		CountMaterials(FILE*);
public:
    C3DSModel();
    C3DSModel(C3DSModel&);
    ~C3DSModel();
	int		LoadModel(const char*);
    void	LoadAllTextures();
    void	Render();
};

#endif