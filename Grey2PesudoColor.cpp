#include <fstream>
#include <iostream>
#include <Windows.h>
#include <stdio.h>

using namespace std;

unsigned char  *pBmp;			//pointer to BMP data
int   bmpWidth;		        //width of the BMP image
int   bmpHeight;	      	//height of the BMP image
RGBQUAD  *pColorTable;	  //pointer to color table
int   biBitCount;	      	//number of bit per pixel

//import BMP data
bool
readBMP(char* bmpName){
	//read binary mode
	FILE *fp = fopen(bmpName, "rb");
	if (fp == NULL){
		cout << "read BMP file failed" << endl;
		return 0;
	}

	//ignore bitmapfile header
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//read BMP data information 
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//such as width,height and biBitCount

	bmpHeight = head.biHeight;
	bmpWidth = head.biWidth;
	biBitCount = head.biBitCount;

	//compute # bytes used each line 
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//size of biBitCount(2 Bytes)
	//Grey:1 bit	16-color:4 bits		256-color:16 bits
	
	//create color table for Grey,16-color,256-color BMP image
	switch (biBitCount){
	case 1:{
			   pColorTable = new RGBQUAD[2];
			   fread(pColorTable, sizeof(RGBQUAD), 2, fp);
			   break;
	}
	case 4:{
			   pColorTable = new RGBQUAD[16];
			   fread(pColorTable, sizeof(RGBQUAD), 16, fp);
			   break;
	}
	case 8:{
			   pColorTable = new RGBQUAD[256];
			   fread(pColorTable, sizeof(RGBQUAD), 256, fp);
			   break;
	}
	default:break;
	}

	pBmp = new unsigned char[lineByte * bmpHeight];
	fread(pBmp, 1, lineByte * bmpHeight, fp);

	fclose(fp);
	cout << "BMP image loaded successfully!" << endl;
	return 1;
}
