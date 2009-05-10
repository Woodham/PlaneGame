/*
 * MD2.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: woodham
 */

#include "MD2.h"



MD2::MD2(const char * filename)
{

	ifstream md2file;
	md2file.open(filename, ios::in | ios::binary);

	// C stuff
	md2_header_t * md2header = (struct md2_header_t *) malloc(sizeof(struct md2_header_t));

	// it involves evil casting.  Would be much happier if this was byte *.
	md2file.read((char *) md2header, sizeof(struct md2_header_t));

	if ((md2header->ident != 844121161) || (md2header->version != 8))
	{
		/* Error! */
		cerr << "Error: MD2 bad version or identifier" << endl;
	}

	// Get data.

	this->skins = (md2_skin_t *) calloc(md2header->num_skins, sizeof(struct md2_skin_t));
	this->texcoords = (md2_texCoord_t *) calloc(md2header->num_st, sizeof(struct md2_texCoord_t));
	this->triangles = (md2_triangle_t *) calloc(md2header->num_tris, sizeof(struct md2_triangle_t));
	this->num_triangles = md2header->num_tris;
	this->frames = (md2_frame_t *) calloc(md2header->num_frames, sizeof(struct md2_frame_t));
	this->glcmds = (int *) calloc(md2header->num_glcmds, sizeof(int));
	this->vertices = (vec3_t *) calloc(md2header->num_vertices, sizeof(vec3_t));
	this->num_frames = md2header->num_frames;
	this->skinwidth = md2header->skinwidth;
	this->skinheight = md2header->skinheight;

	md2file.seekg(md2header->offset_st, ios::beg);
	md2file.read((char *) texcoords, sizeof(struct md2_texCoord_t) * md2header->num_st);

	md2file.seekg(md2header->offset_tris, ios::beg);
	md2file.read((char *) triangles, sizeof(struct md2_triangle_t) * md2header->num_tris);

	md2file.seekg(md2header->offset_glcmds, ios::beg);
	md2file.read((char *) glcmds, sizeof(int) * md2header->num_glcmds);

	md2file.seekg(md2header->offset_frames, ios::beg);

	for (int i = 0; i < md2header->num_frames; ++i)
	{

		this->frames[i].verts = (md2_vertex_t *) calloc(md2header->num_vertices, sizeof(struct md2_vertex_t));

		md2file.read((char *) this->frames[i].scale, sizeof(vec3_t));
		md2file.read((char *) this->frames[i].translate, sizeof(vec3_t));
		md2file.read((char *) this->frames[i].name, sizeof(char) * 16);
		md2file.read((char *) this->frames[i].verts, sizeof(md2_vertex_t) * md2header->num_vertices);

		//cout << i + 1 << ")  " << this->frames[i].scale << " " << this->frames[i].translate << " " << this->frames[i].name << " " << this->frames[i].verts << endl;

		//cout << this->frames[i].verts->v[1] << endl;

	}

	free(md2header);
	md2file.close();

}

void MD2::Draw(int n, GLuint texid)
{

	  int i, j;
	  GLfloat s, t;
	  vec3_t v;
	  md2_frame_t * pframe;
	  md2_vertex_t * pvert;

	  vec3_t anorms_table[162] = {
	  #include "anorms.h"
	  };


	  if ((n < 0) || (n > this->num_frames - 1))
	  {
		  cerr << "Invalid frame number " << n << " of " << this->num_frames << endl;
	  }else
	  {
		  glPushMatrix();
			  glBegin(GL_TRIANGLES);
			  for(i = 0; i < this->num_triangles; i++)
			  {
				  for (j = 0; j < 3; j++)
					  {
						pframe = &this->frames[n];
						pvert = &pframe->verts[this->triangles[i].vertex[j]];

						/* Compute texture coordinates */
						s = (GLfloat)this->texcoords[this->triangles[i].st[j]].s / this->skinwidth;
						t = (GLfloat)this->texcoords[this->triangles[i].st[j]].t / this->skinheight;

						/* Pass texture coordinates to OpenGL */
						glTexCoord2f (s, -t);

						/* Normal vector */
						glNormal3fv (anorms_table[pvert->normalIndex]);

						v[0] = (pframe->scale[0] * pvert->v[0]) + pframe->translate[0];
						v[1] = (pframe->scale[1] * pvert->v[1]) + pframe->translate[1];
						v[2] = (pframe->scale[2] * pvert->v[2]) + pframe->translate[2];

						glVertex3fv (v);
					  }
			  }
			  glEnd();
			  glPopMatrix();
		  }
	  }




MD2::~MD2()
{
	// TODO Auto-generated destructor stub
}
