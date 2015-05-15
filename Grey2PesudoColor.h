#ifndef _GREY2PESUDCOLOR_H_
#define _GREY2PESUDCOLOR_H_

static void addColor(RGBQUAD* pColor, int i, BYTE R, BYTE G, BYTE B);
static int getPartition(int ori, int numParti);
static void grey2PesudoColor(unsigned char* imgBuf, int height, int lineByte);
void readBMP(char* bmpName);
void saveBMP(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);

#endif
