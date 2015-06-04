#ifndef _GREY2PESUDCOLOR_H_
#define _GREY2PESUDCOLOR_H_
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

extern unsigned char  *pBmp;			    //pointer to BMP data
extern			     int   bmpWidth;	  	//width of the BMP image
extern			     int   bmpHeight;	  	//height of the BMP image
extern		   RGBQUAD  *pColorTable;		//pointer to color table
extern			     int   biBitCount;		//number of bit per pixel

static void addColor(RGBQUAD* pColor, int i, BYTE R, BYTE G, BYTE B);
static int getPartition(int ori, int numParti);
static void grey2PesudoColor(unsigned char* imgBuf, int height, int lineByte);
extern void readBMP(char* bmpName);
extern void saveBMP(char *bmpName, unsigned char *imgBuf, int width, int height, 
	int biBitCount, RGBQUAD *pColorTable);

#endif
