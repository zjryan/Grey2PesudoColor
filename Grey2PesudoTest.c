#include "grey2PesudoColor.h"

int main(){
	readBMP("C:\\Cppproj\\Grey2PesudColor\\testbmp1.bmp");
	saveBMP("C:\\Cppproj\\Grey2PesudColor\\modifiedBMP1.bmp", pBmp, bmpWidth, bmpHeight,
		biBitCount, pColorTable);
	free(pBmp);
	pBmp = NULL;
	free(pColorTable);
	pColorTable = NULL;
	return 0;
}
