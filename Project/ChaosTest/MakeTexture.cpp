

#include "stdafx.h"
#include <fstream>
#include "FreeImage.h"

using namespace std;
using namespace Chaos;

static char res_buf[] = {1,2,3,4,5,6,7,8};

int main_MakeTexture(int argc, char* argv[])
{
	const char *szFilePath="Data/d2.bmp";
	const char *szTarFileName="res_d2";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib = nullptr;
	//pointer to the image data
	BYTE* bits = nullptr;
	//image width and height
	uint width=0, height=0;

	uint nBpp=0; 

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(szFilePath, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(szFilePath);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
	{
		CH_TRACE("[rd] error: can not load the texture. %s",szFilePath);
		return 1;
	}
	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, szFilePath);
	//if the image failed to load, return failure
	if(!dib)
	{
		CH_TRACE("[rd] error: call FreeImage_Load failed.");
		return 1;
	}

	nBpp = FreeImage_GetBPP(dib);

	if(nBpp != 32)
	{
		FIBITMAP *t = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(dib);
		dib = t;
	}
	nBpp = FreeImage_GetBPP(dib);


	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if( (width == 0) || (height == 0))
	{
		CH_TRACE("[rd] error: not a vaildate texture.");
		FreeImage_Unload(dib);
		return 1;
	}

	uint surfacePitch = FreeImage_GetPitch(dib);
	uint nBitmapBytes = width * height * nBpp/8;
	bits = new BYTE[nBitmapBytes];	
	FreeImage_ConvertToRawBits(bits,dib,surfacePitch,nBpp,FI_RGBA_RED_MASK,FI_RGBA_RED_MASK,FI_RGBA_RED_MASK,false);
	for(uint i=0;i<nBitmapBytes; i+=4)
	{
		swap(bits[i],bits[i+2]);
	}


	ofstream fout(szTarFileName,ios::out);
	fout<<"static const char "<<szTarFileName<<"[]={";
	for(uint i=0; i< nBitmapBytes; i++)
	{
		fout<<(int)bits[i]<<",";
		if(i%50==0)
		{
			fout<<std::endl;
		}
	}
	fout<<"};";
	fout.flush();
	fout.close();
	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	

	CH_SFDELARR(bits);

	return 0;
}