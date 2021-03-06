#include "grey2PesudColor.h"

unsigned char  *pBmp;			//pointer to BMP data
	  int   bmpWidth;		//width of the BMP image
	  int   bmpHeight;		//height of the BMP image
      RGBQUAD  *pColorTable;		//pointer to color table
	  int   biBitCount;		//number of bit per pixel

//import BMP data
void
readBMP(char* bmpName){
	//read binary mode
	FILE *fp = fopen(bmpName, "rb");
	if (fp == NULL){
		printf("read BMP file failed\n");
		exit(1);
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
	if (biBitCount == 8){
		pColorTable = (RGBQUAD*)malloc(sizeof(RGBQUAD)* 256);
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
		for (int i = 0; i < 256; i++){
			pColorTable[i].rgbBlue = (BYTE)i;
			pColorTable[i].rgbGreen = (BYTE)i;
			pColorTable[i].rgbRed = (BYTE)i;
			pColorTable[i].rgbReserved = 0;
		}
	}

	pBmp = (unsigned char*)malloc(sizeof(unsigned char) * lineByte * bmpHeight);
	fread(pBmp, 1, lineByte * bmpHeight, fp);

	fclose(fp);
	printf("BMP image loaded successfully!\n");
}

void
saveBMP(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	//no image
	if (imgBuf == NULL)
		exit(1);

	//the size of colortable of grey image is 256*4 = 1024 BYTES
	int colorTablesize = 0;
	if (biBitCount == 8){
		colorTablesize = 1024;
	}
		
	//BYTES per line
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	
	//open the file with wb mode
	FILE *fp = fopen(bmpName, "wb");
	if (fp == NULL) {
		printf("read BMP image failed");
		exit(1);
	}
	//fileheader informations
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;

	//size of BMP file
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize +
		lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits = 54 + colorTablesize;
	//write fileheader information into the BMP file
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	
	//infoheader informations
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte * height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;

	//write infoheader information into the BMP file
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	grey2PesudoColor(imgBuf, height, lineByte);
	//for Grey image 
	if (biBitCount == 8){
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	}
	//write BMP data into the file
	fwrite(imgBuf, height * lineByte, 1, fp);
	fclose(fp);
	printf("image saved\n");
	return;
}

static void
addColor(RGBQUAD* pColor, int i, BYTE R, BYTE G, BYTE B){
	pColor[i].rgbBlue = B;
	pColor[i].rgbGreen = G;
	pColor[i].rgbRed = R;
	pColor[i].rgbReserved = 0;
	return;
}

static int
getPartition(int ori, int numParti){
	return (int)((ori / 256.0) * numParti);
}

static int randomColorGenerator(){
	return rand() % 256;
}

static void
grey2PesudoColor(unsigned char* imgBuf, int height, int lineByte){
	enum { ColorNum = 4 };
	//self-defined color table
	//Red
	/*
	addColor(pColorTable, 0, 255, 0, 0);
	//Green
	addColor(pColorTable, 1, 0, 255, 0);
	//Blue
	addColor(pColorTable, 2, 0, 0, 255);
	*/

	//random generates color
	int i;
	for (i = 0; i < ColorNum; i++){
		BYTE randColor1 = randomColorGenerator();
		BYTE randColor2 = randomColorGenerator();
		BYTE randColor3 = randomColorGenerator();

		addColor(pColorTable, i, randColor1, randColor2, randColor3);
	}

	for (i = 0; i < height * lineByte; i++){
		int status = getPartition((int)*imgBuf, ColorNum);
		//change pixel index
		*imgBuf = status;
		imgBuf++;
	}
}
