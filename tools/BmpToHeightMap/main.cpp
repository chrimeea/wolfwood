#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "corona.h"

typedef unsigned char byte;
byte* height_map=NULL;

void main()
{
    corona::Image* image=corona::OpenImage("HeightMap.BMP");
    if(!image)
	{
		fprintf(stderr,"ERROR loading bmp!");
		exit(1);
	}
    int width=image->getWidth();
    int height=image->getHeight();
	corona::PixelFormat format = image->getFormat();
	switch (format)
	{
	case corona::PF_R8G8B8:
		printf("Format OK : r8g8b8.\n");
		break;
	default:
		image=corona::ConvertImage(image,corona::PF_R8G8B8);
		if(image!=NULL)
		{
			printf("File conversion to R8G8B8 done.\n");
		}
		else
		{
			fprintf(stderr,"ERROR in file format conversion. Terminating program.!");
			exit(1);
		}
		break;
	}

    byte* p=(byte*)image->getPixels();

	FILE* pf=fopen("map.map","wb");
	if(!pf)
	{
		fprintf(stderr,"ERROR opening map file.");
		exit(1);
	}

	unsigned short w=width-1,h=height-1;
	fwrite(&w,2,1,pf);
	fwrite(&h,2,1,pf);

	height_map=new byte[width*height];

	for (int i = 0; i < width * height; i++)
	{
		byte r=*p++;
		byte g=*p++;
		byte b=*p++;
		byte color=(r+g+b)/3;
		height_map[i]=color;
		fwrite(&color,1,1,pf);
	}

	unsigned char texid;
	unsigned char walk=1;
	char str_tileset[10]="\0";
	strcpy(str_tileset,"ts_green");
	fwrite(str_tileset,strlen(str_tileset)+1,1,pf);

	int k=0;
	for(i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
/*			k=i*width+j;
			if(height_map[k]>=0 && height_map[k]<=30)
				texid=0;
			else if(height_map[k]>30 && height_map[k]<=60)
				texid=1;
			else if(height_map[k]>60 && height_map[k]<=68)
				texid=2;
			else if(height_map[k]>68) texid=3;
*/
			texid=0;
			fwrite(&texid,1,1,pf);
			fwrite(&walk,1,1,pf);
		}

	delete image;
	fclose(pf);
}