/*
 * PCX.cpp
 *
 *  Created on: Apr 19, 2009
 *      Author: woodham
 */

#include "PCX.h"

PCX::PCX(const char *filename)
{

	std::ifstream file;
	char *buffer = NULL;
	int bitcount; // nombre de bits par pixel
	GLubyte *ptr = NULL;

	file.open(filename, std::ios::in | std::ios::binary);

	if (file.fail())
		cerr << "FAIL" << endl;//	return false;


	file.seekg(0, std::ios::end);
	long flen = file.tellg();
	file.seekg(0, std::ios::beg);

	buffer = new char[flen];
	file.read(buffer, flen);
	char *pBuff = buffer;

	file.close();

	this->pcxheader = (pcx_header_t *) pBuff;
	pBuff = (char *) &buffer[128];

	if (this->pcxheader->manufacturer != 10)
	{
		delete[] buffer;

		cerr << "Error: PCX Manufacturer not correct" << endl;

	}

	this->pcxheader->xmax = this->pcxheader->xmax - this->pcxheader->xmin + 1;
	this->pcxheader->ymax = this->pcxheader->ymax - this->pcxheader->ymin + 1;

	if ((this->pcxheader->xmax <= 0) || (this->pcxheader->ymax <= 0))
	{
		delete[] buffer;
		cerr << "Error: PCX Size not correct" << endl;
	}

	this->pcxtexinfo = (gl_texture_t *) malloc(sizeof(struct gl_texture_t));
	this->pcxtexinfo->width = this->pcxheader->xmax;
	this->pcxtexinfo->height = this->pcxheader->ymax;
	this->pcxtexinfo->format = GL_RGB;
	this->pcxtexinfo->internalFormat = 3;
	this->pcxtexinfo->texels = new GLubyte[this->pcxtexinfo->width * this->pcxtexinfo->height * this->pcxtexinfo->internalFormat];

	ptr = &this->pcxtexinfo->texels[0];

	bitcount = this->pcxheader->bitsPerPixel * this->pcxheader->numColorPlanes;

	switch (bitcount)
	{
		case 1:
		{
			cerr << "Error: PCX 1 bit not supported" << endl;

			break;
		}

		case 4:
		{
			cerr << "Error: PCX 4 bit not supported" << endl;

			break;
		}

		case 8:
		{

			ReadPCX8bits(flen, buffer, this->pcxheader, pBuff, ptr, this->pcxtexinfo);

			break;
		}

		case 24:
		{

			cerr << "Error: PCX 24 bit not supported" << endl;

			break;
		}

		default:
		{
			delete[] buffer;
		}
	}

	delete[] buffer;

}


void PCX::ReadPCX8bits (long flen, char *buffer, pcx_header_t *header, char *pBuff, GLubyte *ptr, gl_texture_t *tex)
{

	char *ptrPal = &buffer[flen - 769];
	RGBTRIPLE *palette = NULL;
	unsigned char rle_count = 0;
	unsigned char rle_value = 0;

	if (*(ptrPal++) != 12)
	{
		cerr << "Error: PCX Palette not correct" << endl;
		delete[] buffer;
	}

	palette = (RGBTRIPLE *) ptrPal;

	for (int y = 0; y < (int) (tex->height); y++)
	{
		ptr = &tex->texels[(tex->height - (y + 1)) * tex->width * 3];

		int bytes = header->bytesPerScanLine;

		while (bytes--)
		{
			if (rle_count == 0)
			{
				if ((rle_value = *(pBuff++)) < 0xc0)
				{
					rle_count = 1;
				}
				else
				{
					rle_count = rle_value - 0xc0;
					rle_value = *(pBuff++);
				}
			}

			rle_count--;
			ptr[0] = (GLubyte) palette[rle_value].rgbtBlue;
			ptr[1] = (GLubyte) palette[rle_value].rgbtGreen;
			ptr[2] = (GLubyte) palette[rle_value].rgbtRed;
			ptr += 3;

		}
	}


}

PCX::gl_texture_t *PCX::getTexInfo()
{
	//gl_texture_t *tex = pcxtexinfo;

	return pcxtexinfo;

}

PCX::~PCX()
{
	// TODO Auto-generated destructor stub
}







