/*
 * MD2.h
 *
 *  Created on: Apr 1, 2009
 *      Author: woodham
 */

#ifndef MD2_H_
#define MD2_H_

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>


#include "PCX.h"

using namespace std;

class MD2
{
	public:
		MD2();
		MD2(const char * filename);
		virtual ~MD2();

		void Draw(int n, GLuint texid);

	private:
		/* MD2 header from http://tfc.duke.free.fr/coding/md2-specs-en.html */
		struct md2_header_t
		{
		  int ident;                  /* magic number: "IDP2" */
		  int version;                /* version: must be 8 */

		  int skinwidth;              /* texture width */
		  int skinheight;             /* texture height */

		  int framesize;              /* size in bytes of a frame */

		  int num_skins;              /* number of skins */
		  int num_vertices;           /* number of vertices per frame */
		  int num_st;                 /* number of texture coordinates */
		  int num_tris;               /* number of triangles */
		  int num_glcmds;             /* number of opengl commands */
		  int num_frames;             /* number of frames */

		  int offset_skins;           /* offset skin data */
		  int offset_st;              /* offset texture coordinate data */
		  int offset_tris;            /* offset triangle data */
		  int offset_frames;          /* offset frame data */
		  int offset_glcmds;          /* offset OpenGL command data */
		  int offset_end;             /* offset end of file */
		};

		/* Compressed vertex */
		struct md2_vertex_t
		{
		  unsigned char v[3];         /* position */
		  unsigned char normalIndex;  /* normal vector index */
		};

		/* Triangle info */
		struct md2_triangle_t
		{
		  unsigned short vertex[3];   /* vertex indices of the triangle */
		  unsigned short st[3];       /* tex. coord. indices */
		};

		/* Vector */
		typedef float vec3_t[3];

		/*frames*/
		struct md2_frame_t
		{
		  vec3_t scale;               /* scale factor */
		  vec3_t translate;           /* translation vector */
		  char name[16];              /* frame name */
		  struct md2_vertex_t *verts; /* list of frame's vertices */
		};

		/*Open GL commands*/
		struct md2_glcmd_t
		{
		  float s;                    /* s texture coord. */
		  float t;                    /* t texture coord. */
		  int index;                  /* vertex index */
		};

		/* Texture name */
		struct md2_skin_t
		{
		  char name[64];              /* texture file name */
		};

		/* Texture coords */
		struct md2_texCoord_t
		{
		  short s;
		  short t;
		};

		//vec3_t anorms_table[162];

		vec3_t * vertices;
		int num_vertices;
		md2_triangle_t * triangles;
		int num_triangles;
		md2_frame_t * frames;
		int * glcmds;
		int num_frames;
		int skinwidth;
		int skinheight;
		md2_skin_t * skins;
		md2_texCoord_t * texcoords;


};

#endif /* MD2_H_ */
