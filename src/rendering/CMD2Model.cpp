#include <stdio.h>
#include <math.h>
#include "rendering\CMD2Model.h"
#include "rendering\MD2Normals.h"
#include "rendering\CMeshBufferPool.h"

CMD2Model::CMD2Model() : CAnimatedMesh()
{
	poly_data = NULL;
	frame_nr = 0;
	frame_next_nr = 1;
	skin_index = 0;
	anim_ind = 0;
	old_time = 0.0;
	intrplt_verts = NULL;
}

CMD2Model::CMD2Model(const unsigned int id) : CAnimatedMesh()
{
	poly_data = NULL;
	frame_nr = 0;
	frame_next_nr = 1;
	skin_index = 0;
	anim_ind = 0;
	old_time = 0.0;
	intrplt_verts = NULL;
	LoadModel(id);
}

CMD2Model::~CMD2Model()
{
	if(intrplt_verts != NULL) delete [] intrplt_verts;
}

void CMD2Model::Render(void)
{
	int*	p = poly_data->glcmds;
	int		n;

	m_renderer->SetFrontFace(GL_CW);

	m_renderer->SetMaterial(NULL);
	m_renderer->SetTexture(&poly_data->skins[skin_index]);

	while((n = *(p++)) != 0)
	{
		if(n > 0) m_renderer->BeginRender(GL_TRIANGLE_STRIP);
		else
		{
			m_renderer->BeginRender(GL_TRIANGLE_FAN);
			n = -n;
		}
		
		for(int j = 0; j < n; j++, p += 3)
		{
			m_renderer->SetTexCoords((float*)p);
			m_renderer->SetNormal(&vect3d_t(
				md2_normals[poly_data->frames[frame_nr].norm_inds[p[2]]][0],
				md2_normals[poly_data->frames[frame_nr].norm_inds[p[2]]][1],
				md2_normals[poly_data->frames[frame_nr].norm_inds[p[2]]][2])
				);
			m_renderer->SetVertex(&intrplt_verts[p[2]]);
		}

		m_renderer->EndRender();
	}

	m_renderer->SetFrontFace(GL_CCW);
}

int CMD2Model::LoadModel(const unsigned int id)
{
	// foloseste CMeshBufferPool pentru a incarca cu maxima eficienta un nou model md2
	poly_data = (MD2Data *)(((BufferData *)(CMeshBufferPool::getInstance()->getBuffer(id)))->data);
	intrplt_verts = new vect3d_t[poly_data->num_vertices];
	for(int i = 0; i < poly_data->num_skins; i++)
	{
		m_renderer->LoadTexture(&poly_data->skins[i]);
	}
	return 1;
}

void CMD2Model::SetSkinIndex(const int i)
{
	if(i >= 0 && i <= poly_data->num_skins) skin_index = i;
}

void CMD2Model::NextFrame(float time)
{
	if(old_time == 0.0) old_time = time;
	if(time-old_time > (1.0 / (float)poly_data->animations[anim_ind].fps))
	{
		frame_nr++;
		if(frame_nr > poly_data->animations[anim_ind].end) frame_nr = poly_data->animations[anim_ind].start;
		frame_next_nr = frame_nr+1;
		if(frame_next_nr > poly_data->animations[anim_ind].end) frame_next_nr = poly_data->animations[anim_ind].start;
		old_time = time;
	}

	intrplt_perc = (float)poly_data->animations[anim_ind].fps*  (time - old_time);

	vect3d_t *aframev, *nframev;
	aframev = poly_data->frames[frame_nr].vertices;
	nframev = poly_data->frames[frame_next_nr].vertices;

	for(int i = 0; i < poly_data->num_vertices; i++)
	{
		intrplt_verts[i].x = (aframev[i].x+intrplt_perc*(nframev[i].x-aframev[i].x))*(float)MD2_SCALE;
		intrplt_verts[i].y = (aframev[i].y+intrplt_perc*(nframev[i].y-aframev[i].y))*(float)MD2_SCALE;
		intrplt_verts[i].z = (aframev[i].z+intrplt_perc*(nframev[i].z-aframev[i].z))*(float)MD2_SCALE;
	}
}

void CMD2Model::SetAnimation(anim_type_t anim_type)
{
	if(anim_type >= 0 && anim_type <= MD2_MAX_ANIM_TYPE) anim_ind = anim_type;
	else anim_ind = 0;
	frame_nr = poly_data->animations[anim_ind].start;
	if(frame_nr+1 > poly_data->animations[anim_ind].end) frame_next_nr = poly_data->animations[anim_ind].start;
	else frame_next_nr = frame_nr+1;
}