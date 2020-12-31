#include "corona.h"
#include <iostream>
#include <string>
#include <fstream>

#define ERROR 0
#define OK 1
#define CROP_W 500
#define CROP_H 500
#define CHNS 4

using namespace std;
using namespace corona;

int main()
{
	char img_str[100], *temp_str;
	cout << "Nume imagine de fundal (fara extensie si punct): "; cin >> img_str;

	temp_str = new char[100];
	sprintf(temp_str, "%s.jpg", img_str);

	Image *img = OpenImage(temp_str);

	if(img == NULL)
	{
		cerr << "\nEroare : nu pot incarca imaginea '" << img_str << "' !\n";
		return ERROR;
	}

	delete[] temp_str;

	PixelFormat pf = img->getFormat();
	switch(pf)
	{
	case PF_R8G8B8 :
		{
			if((img = ConvertImage(img, PF_R8G8B8A8)) == 0)
			{
				cerr << "Eroare : nu pot converti imaginea in format rgba - 32bps.\n";
				delete img;
				return ERROR;
			}
			break;
		}
	default :
		{
			cerr << "Eroare : formatul fisierului nerecunoscut.\n";
			delete img;
			return ERROR;
		}
	}

	cout << "Imaginea incarcata cu success.\n";

	int width = img->getWidth();
	int height = img->getHeight();
	unsigned char *p = (unsigned char *)img->getPixels();
	unsigned char *newp = NULL, *ptr = NULL;
	int x, y, k = 0;

	for(y = 0; y < height; y += CROP_H)
		for(x = 0; x < width; x += CROP_W)
		{
			int lim_x = x + (x + CROP_W > width ? width - x : CROP_W);
			int lim_y = y + (y + CROP_H > height ? height - y : CROP_H);
			
			newp = (unsigned char *)malloc((lim_x - x) * (lim_y - y) * CHNS);
			ptr = newp;

			for(int j = lim_y - 1; j >= y; j--)
			{
				memcpy((unsigned char *)ptr, 
					(unsigned char *)&p[(j * width + x) * CHNS], 
					(lim_x - x) * CHNS);
				ptr += (lim_x - x) * CHNS;
			}
		/*
			for(int j = y; j < lim_y; j++)
			{
				memcpy((void *)ptr, (const void *)&p[(j * width + x) * CHNS], (lim_x - x) * CHNS);
				ptr += (lim_x - x) * CHNS;
			}
		*/
			Image *newimg = CreateImage(lim_x - x, lim_y - y, PF_R8G8B8A8, newp);
			char new_str[100];
			sprintf(new_str, "%s_%02d.png", img_str, k);
			if(SaveImage(new_str, FF_PNG, newimg) == false)
			{
				cerr << "Eroare : nu pot salva o imagine partiala.\n";
				free(newp);
				delete newimg;
				delete img;
				return ERROR;
			}

			free(newp);
			delete newimg;

			float *zbuff = new float[(lim_x - x) * (lim_y - y)];
			for(int w = 0; w < (lim_x - x) * (lim_y - y); w++) zbuff[w] = 0.5;
			sprintf(new_str, "z%s_%02d.z", img_str, k);
			ofstream out(new_str);
			out.write((const char *)zbuff, (lim_x - x) * (lim_y - y) * sizeof(float));
			out.close();
			delete [] zbuff;

			k++;
		}

	delete img;

	cout << "Termiat cu success.\n";

	return OK;
}