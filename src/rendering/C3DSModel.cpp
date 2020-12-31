#include <memory.h>
#include <string.h>
#include "rendering\C3DSModel.h"
#include "rendering\CRenderer.h"
#include "rendering\3DSFormat_defines.h"

C3DSModel::C3DSModel()
{
    vertices=NULL;
    faces=NULL;
    subdivisions=NULL;
    materials=NULL;
    texcoords=NULL;
    n_vertices=0;
    n_faces=0;
    n_subdivisions=0;
    n_materials=0;
}

C3DSModel::C3DSModel(C3DSModel& r3dMesh)
{
    if(r3dMesh.vertices!=NULL && n_vertices!=0)
    {
        n_vertices=r3dMesh.n_vertices;
        vertices=new vect3d_t[n_vertices];
        memcpy(vertices,r3dMesh.vertices,n_vertices*sizeof(vect3d_t));
    }
    if(r3dMesh.texcoords!=NULL && n_vertices!=0)
    {
        texcoords=new float[2*n_vertices];
        memcpy(texcoords,r3dMesh.texcoords,n_vertices*2*sizeof(float));
    }
    if(r3dMesh.faces!=NULL && n_faces!=0)
    {
        n_faces=r3dMesh.n_faces;
        faces=new unsigned short[3*n_faces];
        memcpy(faces,r3dMesh.faces,n_faces*3*sizeof(unsigned short));
    }
    if(r3dMesh.materials!=NULL && n_materials!=0)
    {
        n_materials=r3dMesh.n_materials;
        materials=new CMaterial[n_materials];
        memcpy(materials,r3dMesh.materials,n_materials*sizeof(CMaterial));
    }
    if(r3dMesh.subdivisions!=NULL && n_subdivisions!=0)
    {
        n_subdivisions=r3dMesh.n_subdivisions;
        subdivisions=new MeshSubDivision[n_subdivisions];
        for(unsigned int i=0;i<n_subdivisions;i++)
        {
            subdivisions[i].mat_index=r3dMesh.subdivisions[i].mat_index;
            subdivisions[i].n_entries=r3dMesh.subdivisions[i].n_entries;
            subdivisions[i].faces_indices=new unsigned short[subdivisions[i].n_entries];
            memcpy(subdivisions[i].faces_indices,r3dMesh.subdivisions[i].faces_indices,
                subdivisions[i].n_entries*sizeof(unsigned short));
        }
    }
    n_vertices=r3dMesh.n_vertices;
    n_faces=r3dMesh.n_faces;
    n_subdivisions=r3dMesh.n_subdivisions;
    n_materials=r3dMesh.n_materials;
}

C3DSModel::~C3DSModel()
{
    if(materials!=NULL) delete [] materials;
    if(subdivisions!=NULL)
    {
        for(unsigned short i=0;i<n_subdivisions;i++)
        {
            if(subdivisions[i].faces_indices!=NULL)
                delete [] subdivisions[i].faces_indices;
        }
        delete [] subdivisions;
    }
	if(vertices!=NULL) delete [] vertices;
    if(texcoords!=NULL) delete [] texcoords;
    if(faces!=NULL) delete [] faces;
}

int C3DSModel::CountMaterials(FILE* f)
{
	long init_pos=ftell(f);
	rewind(f);

	long fsize=0;
//	char buff;
//	while(!feof(f)) fsize+=fread(&buff,1,1,f);
//	rewind(f);
	fseek(f,0,SEEK_END);
	fsize=ftell(f);

	unsigned int cnt=0;
	unsigned short chunk_id;
	unsigned long chunk_length;
	
	while(ftell(f)<fsize)
	{
		fread(&chunk_id,2,1,f);
		fread(&chunk_length,4,1,f);

		switch(chunk_id)
		{
		case CH_MAIN:
			break;
		case CH_3D_EDITOR:
			break;
		case CH_MATERIAL_BLOCK:
			cnt++;
			if(chunk_length>6) fseek(f,chunk_length-6,SEEK_CUR);
			break;
		default:
			if(chunk_length>6) fseek(f,chunk_length-6,SEEK_CUR);
			break;
		}
	}
	fseek(f,init_pos,SEEK_SET);
	return cnt;
}

void C3DSModel::LoadAllTextures()
{
    for(unsigned short i=0;i<n_materials;i++)
    {
        if(materials[i].texture1_present==true)
            m_renderer->LoadTexture(&materials[i].texture1);
    }
}

void C3DSModel::Render()
{
    for(unsigned short i=0;i<n_subdivisions;i++)
    {

        m_renderer->SetMaterial(&materials[i]);
        if(materials[i].texture1_present)
            m_renderer->SetTexture(&materials[i].texture1);
		else
			m_renderer->SetTexture(NULL);
        m_renderer->BeginRender(GL_TRIANGLES);
        for(unsigned short j=0;j<subdivisions[i].n_entries;j++)
        {
            m_renderer->SetNormal(&face_normals[subdivisions[i].faces_indices[j]]);
            if(materials[i].texture1_present)
                m_renderer->SetTexCoords(&texcoords[2*faces[3*subdivisions[i].faces_indices[j]]]);
            m_renderer->SetVertex(&vertices[faces[3*subdivisions[i].faces_indices[j]]]);

            m_renderer->SetNormal(&face_normals[subdivisions[i].faces_indices[j]]);
            if(materials[i].texture1_present)
                m_renderer->SetTexCoords(&texcoords[2*faces[3*subdivisions[i].faces_indices[j]+1]]);
            m_renderer->SetVertex(&vertices[faces[3*subdivisions[i].faces_indices[j]+1]]);

            m_renderer->SetNormal(&face_normals[subdivisions[i].faces_indices[j]]);
            if(materials[i].texture1_present)
                m_renderer->SetTexCoords(&texcoords[2*faces[3*subdivisions[i].faces_indices[j]+2]]);
            m_renderer->SetVertex(&vertices[faces[3*subdivisions[i].faces_indices[j]+2]]);
        }
        m_renderer->EndRender();
    }
}

int C3DSModel::LoadModel(const char* file)
{
	FILE* pfile=fopen(file,"rb");
	if(!pfile) return 0;

	char buff;
	long fsize=0;
	while(!feof(pfile)) fsize+=fread(&buff,1,1,pfile);
	rewind(pfile);

	unsigned int counter=-1;
	unsigned short chunk_id;
	unsigned long chunk_length;
	float* color_array=NULL;
	int* percent_int;
	CTextureMap* active_texture=NULL;
 
	n_subdivisions=n_materials=CountMaterials(pfile);
    materials=new CMaterial[n_materials];
    subdivisions=new MeshSubDivision[n_subdivisions];
	
	while(ftell(pfile)<fsize)
	{
		fread(&chunk_id,2,1,pfile);
		fread(&chunk_length,4,1,pfile);

		switch(chunk_id)
		{
		case CH_RGB_BYTE:
			{
				unsigned char rgb[3];
				fread(rgb,1,3,pfile);
				for(int i=0;i<3;i++) color_array[i]=(float)rgb[i]/(float)255.0;
				color_array[3]=1.0;
				break;
			}
		case CH_PERCENT_INT:
			{
				fread(percent_int,2,1,pfile);
				break;
			}
		case CH_MAIN:
			break;
		case CH_3D_EDITOR:
			break;
		case CH_OBJECT_BLOCK:
			{
				char c;
				do { c=fgetc(pfile); } while(c!='\0');
				break;
			}
		case CH_TRIANGULAR_MESH:
			break;
		case CH_VERTICES_LIST:
			{
				fread(&n_vertices,2,1,pfile);
			    vertices=new vect3d_t[n_vertices];
				for(unsigned short i=0;i<n_vertices;i++)
				{
					fread(&vertices[i].x,4,1,pfile);
					fread(&vertices[i].y,4,1,pfile);
					fread(&vertices[i].z,4,1,pfile);
				}
				break;
			}
		case CH_FACES:
			{
				unsigned short flags;
				fread(&n_faces,2,1,pfile);
				faces=new unsigned short[3*n_faces];
				for(unsigned short i=0;i<3*n_faces;i+=3)
				{
					fread(&faces[i],2,3,pfile);
					fread(&flags,2,1,pfile);
				}
				break;
			}
		case CH_FACES_MATERIAL_LIST:
			{
				char matname[MATERIAL_MAX_NAME_LENGTH]="\0";
				char c;
				int k=0;
				do {
					c=fgetc(pfile);
					k+=_snprintf(matname+k,MATERIAL_MAX_NAME_LENGTH,"%c",c);
				} while(c!='\0');
				for(unsigned short i=0;i<n_materials;i++)
				{
					if(strcmp(materials[i].name,matname)==0) break;
				}
				fread(&subdivisions[i].n_entries,2,1,pfile);
				subdivisions[i].faces_indices=new unsigned short[subdivisions[i].n_entries];
				fread(subdivisions[i].faces_indices,2,subdivisions[i].n_entries,pfile);
				subdivisions[i].mat_index=i;
				break;
			}
		case CH_MAPPING_COORDS:
			fread(&n_texcoords,2,1,pfile);
			texcoords=new float[2*n_texcoords];
			fread(texcoords,4,2*n_texcoords,pfile);
			break;
		case CH_MATERIAL_BLOCK:
				counter++;
				break;
		case CH_MATERIAL_NAME:
			{
				char c;
				int k=0;
				do
				{
					c=fgetc(pfile);
					k+=_snprintf(materials[counter].name+k,MATERIAL_MAX_NAME_LENGTH,"%c",c);
				} while(c!='\0');
				break;
			}
		case CH_MATERIAL_AMBIENT_COLOR:
				color_array=materials[counter].ambient_color;
				break;
		case CH_MATERIAL_DIFFUSE_COLOR:
				color_array=materials[counter].diffuse_color;
				break;
		case CH_MATERIAL_SPECULAR_COLOR:
				color_array=materials[counter].specular_color;
				break;
		case CH_MATERIAL_SHININESS_PERCENT:
				percent_int=&materials[counter].shininess;
				break;
		case CH_TEXTURE_MAP_1:
			active_texture=&materials[counter].texture1;
			materials[counter].texture1_present=true;
			break;
		case CH_MAP_NAME:
			{
				char c;
				int k=0;
				do
				{
					c=fgetc(pfile);
					k+=_snprintf(active_texture->file_name+k,_MAX_FNAME,"%c",c);
				} while(c!='\0');
				break;
			}
		case CH_CAMERA:
			{
				float vect[3];
				fread((float*)&vect,4,3,pfile);
				camera_pos=vect3d_t(vect[0],vect[1],vect[2]);
				fread((float*)&vect,4,3,pfile);
				camera_target=vect3d_t(vect[0],vect[1],vect[2]);
				fread((float*)vect,4,2,pfile);
				break;
			}
		default:
			if(chunk_length>6) fseek(pfile,chunk_length-6,SEEK_CUR);
			break;
		}
	}

	fclose(pfile);

	//Calculate face normals for loaded mesh
	//And store vertex normals
    face_normals=new vect3d_t[n_faces];
    normals=new vect3d_t[n_vertices];
	int k=-1;
	for(unsigned short i=0;i<3*n_faces;i+=3)
	{
		calcnormal(vertices[faces[i]],vertices[faces[i+1]],vertices[faces[i+2]],
			face_normals[++k]);
		normals[faces[i]]=face_normals[k];
		normals[faces[i+1]]=face_normals[k];
		normals[faces[i+2]]=face_normals[k];
	}

	return 1;
}
