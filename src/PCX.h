/*
 * PCX.h
 *
 *  Created on: Apr 19, 2009
 *      Author: woodham
 */


#ifndef PCX_H_
#define PCX_H_

#include <GL/gl.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;



class PCX
{

	private:
		struct pcx_header_t;

		struct gl_texture_t;

	public:

		PCX(const char *filename);
		virtual ~PCX();

		static void ReadPCX8bits (long flen, char *buffer, pcx_header_t *header, char *pBuff, GLubyte *ptr, gl_texture_t *tex);

		gl_texture_t *getTexInfo();




	private:

		/* OpenGL texture info */
		struct gl_texture_t
		{
		  GLsizei width;
		  GLsizei height;

		  GLenum format;
		  GLint internalFormat;
		  GLuint id;

		  GLubyte *texels;

		};


		//#pragma pack(1)
		/* PCX header */
		struct pcx_header_t
		{
		  GLubyte manufacturer;
		  GLubyte version;
		  GLubyte encoding;
		  GLubyte bitsPerPixel;

		  GLushort xmin, ymin;
		  GLushort xmax, ymax;
		  GLushort horzRes, vertRes;

		  GLubyte palette[48];
		  GLubyte reserved;
		  GLubyte numColorPlanes;

		  GLushort bytesPerScanLine;
		  GLushort paletteType;
		  GLushort horzSize, vertSize;

		  GLubyte padding[54];

		};
		//#pragma pack(4)





		/* Texture id for the demo */
		GLuint texId;
		gl_texture_t *pcxtexinfo;
		pcx_header_t *pcxheader;


		typedef struct tagRGBTRIPLE			// rgbt
		{
			unsigned char	rgbtBlue;		// bleu
			unsigned char	rgbtGreen;		// vert
			unsigned char	rgbtRed;		// rouge

		} RGBTRIPLE, *PRGBTRIPLE;

};

#endif /* PCX_H_ */
