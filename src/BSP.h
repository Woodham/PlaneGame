/*
 * BSP.h
 *
 *  Created on: Apr 21, 2009
 *      Author: woodham
 */

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#ifndef BSP_H_
#define BSP_H_

class BSP
{
	public:
		BSP(const char * filename);
		virtual ~BSP();

		void Draw();

	private:


		struct point3f
		{

		    float x;
		    float y;
		    float z;

		};

		struct point3s
		{

		    short x;
		    short y;
		    short z;
		};


		struct bsp_lump
		{

		    unsigned int    offset;     // offset (in bytes) of the data from the beginning of the file
		    unsigned int    length;     // length (in bytes) of the data

		};

		struct bsp_header
		{

			unsigned int    magic;      // magic number ("IBSP")
			unsigned int    version;    // version of the BSP format (38)

		    bsp_lump  lump[19];   // directory of the lumps

		};

		struct bsp_face
		{

		    unsigned short   plane;             // index of the plane the face is parallel to
		    unsigned short   plane_side;        // set if the normal is parallel to the plane normal

		    unsigned int   first_edge;        // index of the first edge (in the face edge array)
		    unsigned short   num_edges;         // number of consecutive edges (in the face edge array)

		    unsigned short   texture_info;      // index of the texture info structure

		    char    lightmap_syles[4]; // styles (bit flags) for the lightmaps
		    unsigned int   lightmap_offset;   // offset of the lightmap (in bytes) in the lightmap lump

		};

		struct bsp_plane
		{

		    point3f   normal;      // A, B, C components of the plane equation
		    float     distance;    // D component of the plane equation
		    unsigned int    type;        // ?

		};

		struct bsp_node
		{

			unsigned int   plane;             // index of the splitting plane (in the plane array)

		    int    front_child;       // index of the front child node or leaf
		    int    back_child;        // index of the back child node or leaf

		    point3s  bbox_min;          // minimum x, y and z of the bounding box
		    point3s  bbox_max;          // maximum x, y and z of the bounding box

		    unsigned short   first_face;        // index of the first face (in the face array)
		    unsigned short num_faces;         // number of consecutive edges (in the face array)

		};


		struct bsp_leaf
		{

			unsigned int   brush_or;          // ?

			unsigned short   cluster;           // -1 for cluster indicates no visibility information
			unsigned short   area;              // ?

		    point3s  bbox_min;          // bounding box minimums
		    point3s  bbox_max;          // bounding box maximums

		    unsigned short   first_leaf_face;   // index of the first face (in the face leaf array)
		    unsigned short   num_leaf_faces;    // number of consecutive edges (in the face leaf array)

		    unsigned short   first_leaf_brush;  // ?
		    unsigned short   num_leaf_brushes;  // ?

		};

		struct bsp_texinfo
		{

		    point3f  u_axis;
		    float    u_offset;

		    point3f  v_axis;
		    float    v_offset;

		    unsigned int   flags;
		    unsigned int   value;

		    char     texture_name[32];

		    unsigned int   next_texinfo;

		};


		struct bsp_vis_offset
		{

			unsigned int pvs;   // offset (in bytes) from the beginning of the visibility lump
			unsigned int phs;   // ?

		};

		struct bsp_edge
		{
			unsigned short a;
			unsigned short b;
		};


		point3f * vertices;
		bsp_edge * edges;
		bsp_face * faces;
		unsigned int * faceedges;
		bsp_leaf * leaves;
		unsigned short * leaffaces;
		bsp_texinfo * texinfo;


		int novertices;
		int noedges;
		int nofaces;
		int nofaceedges;
		int noleaves;
		int noleaffaces;
		int notextures;



};

#endif /* BSP_H_ */
