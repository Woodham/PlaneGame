/*
 * BSP.cpp
 *
 *  Created on: Apr 21, 2009
 *      Author: woodham
 */

#include "BSP.h"

BSP::BSP(const char * filename)
{

	ifstream bspfile;

	bspfile.open(filename, ios::in | ios::binary);


	bsp_header * bspheader = (struct bsp_header *) malloc(sizeof(struct bsp_header));

	bspfile.read((char *) bspheader, sizeof(struct bsp_header));

	if(bspheader->magic == 'I' + ('B'<<8) + ('S'<<16) + ('P'<<24))
	{
		cout << bspheader->version << endl;
	}else{
		cerr << "Error: BSP file not valid" << endl;
	}

	//cout << bspheader->lump << endl;

	this->novertices = bspheader->lump[2].length / 12;
	this->noedges = bspheader->lump[11].length / 4;
	this->nofaces = bspheader->lump[6].length / 20;
	this->nofaceedges = bspheader->lump[12].length / 4;
	this->noleaves = bspheader->lump[8].length /28;
	this->noleaffaces = bspheader->lump[9].length /2;
	this->notextures = bspheader->lump[5].length / 76;

	this->vertices = (point3f *) malloc(bspheader->lump[2].length);
	this->edges = (bsp_edge *) malloc(bspheader->lump[11].length);
	this->faces = (bsp_face *) malloc(bspheader->lump[6].length);
	this->faceedges = (unsigned int *) malloc(bspheader->lump[12].length);
	this->leaves = (bsp_leaf *) malloc(bspheader->lump[8].length);
	this->leaffaces = (unsigned short *) malloc(bspheader->lump[9].length);
	this->texinfo = (bsp_texinfo *) malloc(bspheader->lump[5].length);

	bspfile.seekg(bspheader->lump[2].offset, ios::beg);
	bspfile.read((char *) vertices, bspheader->lump[2].length);

	bspfile.seekg(bspheader->lump[11].offset, ios::beg);
	bspfile.read((char *) edges, bspheader->lump[11].length);

	bspfile.seekg(bspheader->lump[6].offset, ios::beg);
	bspfile.read((char *) faces, bspheader->lump[6].length);

	bspfile.seekg(bspheader->lump[12].offset, ios::beg);
	bspfile.read((char *) faceedges, bspheader->lump[12].length);

	bspfile.seekg(bspheader->lump[8].offset, ios::beg);
	bspfile.read((char *) leaves, bspheader->lump[8].length);

	bspfile.seekg(bspheader->lump[9].offset, ios::beg);
	bspfile.read((char *) leaffaces, bspheader->lump[9].length);

	bspfile.seekg(bspheader->lump[5].offset, ios::beg);
	bspfile.read((char *) texinfo, bspheader->lump[5].length);


//	for (int i = 0; i < notextures; i++)
//	{
//		cout << texinfo[i].texture_name << endl;
//
//	}

//	cout << notextures << endl;
//	cout << nofaces << endl;
//
//	cout << nofaces / notextures << endl;

	//  point3f * vert = (point3f*)this->vertices;

//	  int vCount = bspheader->lump[2].length / sizeof(point3f);
//	  for (int i = 0; i < vCount; i++, vert++)
//	  {
//	    cout << (*vert).x << " " << (*vert).y << " " << (*vert).z << endl;
//	  }


	//cout << this->vertices[5].x << endl;

	//bsp_lump vertices = ;



}

void BSP::Draw()
{


	//point3f * vert = this->vertices;

//	int num_leaves;
	 // glPushMatrix();

	  /* Number of leaves */
	//  num_leaves = this->noleaves;

	  /* Start at second leaf */
	  bsp_leaf leaf;

	  /* For each leaf in the map */
	  for (int l = 1; l < this->noleaves; l++)
	  {

		  leaf = this->leaves[l];

		// cout << leaf.num_leaf_faces << endl;

	    /* For each leaf face in the leaf */
	    for (int lf = 0; lf < leaf.num_leaf_faces; lf++)
	    {
	      unsigned short leaf_face;
	      bsp_face face;

	  //    cout << leaf.first_leaf_face << endl;

	      /* Get the index of the face from the leaf face table */
	      leaf_face = this->leaffaces[leaf.first_leaf_face + lf];

	      /* Use the index to get the face from the face table */
	      face = this->faces[leaf_face];

	      //cout << leaf_face << endl;


	      glPushMatrix();
	      glBegin(GL_LINES);

	      /* For each edge in the face */
	      for (int f = 0; f < face.num_edges; f++)
	      {
	    	//  glBegin(GL_POLYGON);
			//  cout<< " GOT TO HERE" << endl;

	        int face_edge;
	        int edge_index;
	        bsp_edge edge;
	        GLfloat verti[] = {0.0f, 0.0f, 0.0f};
	        point3f vert;
	       // short v1 = 0, v2 = 1;

	        /* Get the index of the edge from the face edge table */
	        face_edge = this->faceedges[face.first_edge + f];

	        edge_index = face_edge;

	        //cout << texinfo


	        //cout << edge_index << endl;

	        if (edge_index >= 0)
	        {

	        //  edge_index = -edge_index;

		        /* Use the index to get the edge from the edge table */
	        	edge = this->edges[edge_index];

		        /* Get the vert from the first index in the face */
		        vert = this->vertices[edge.a];

		        verti[0] = vert.x;
		        verti[1] = vert.y;
		        verti[2] = vert.z;

		      // cout << verti[2] << endl;

		        /* Draw it */
		        glVertex3fv(verti);

		        /* Get the vert from the second index in the face */
		        vert = this->vertices[edge.b];

		        verti[0] = vert.x;
		        verti[1] = vert.y;
		        verti[2] = vert.z;

		       // cout << verti[1] << endl;

		        /* Draw it */
		        glVertex3fv(verti);

		       // glEnd();

	        }else{

	        	//glBegin(GL_LINES);

	        	 edge_index = -edge_index;

			        /* Use the index to get the edge from the edge table */
		        	edge = this->edges[edge_index];

			        /* Get the vert from the first index in the face */
			        vert = this->vertices[edge.b];

			        verti[0] = vert.x;
			        verti[1] = vert.y;
			        verti[2] = vert.z;

			        /* Draw it */
			        glVertex3fv(verti);

			        /* Get the vert from the second index in the face */
			        vert = this->vertices[edge.a];

			        verti[0] = vert.x;
			        verti[1] = vert.y;
			        verti[2] = vert.z;

			        /* Draw it */
			        glVertex3fv(verti);

			      //  glEnd();

	        }


	      }

	      glEnd();
	      glPopMatrix();


	    }

	  }

	 // glPopMatrix();



}

BSP::~BSP()
{
	// TODO Auto-generated destructor stub
}
