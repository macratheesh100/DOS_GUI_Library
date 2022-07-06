#include "Wiredefs.h"
#include  "DgnTool.h"

typedef struct{
	UCHAR  BitmapFileType[2];
	UINT32 BitmapFileSize;
	UINT16 BitmapFileRes1;
	UINT16 BitmapFileRes2;
	UINT32 BitmapFileOFFBits;
	UINT32 BitmapSize;
	UINT32 BWidth;
	UINT32 BHeight;
	UINT16 BitmapPlanes;
	UINT16 BCount;
	UINT32 BitCompression,BitmapSizeImage,bixpelspermeter,biypelspermeter;
	UINT32 biclrused,biclrimportant;
}BMPHEADER;

typedef struct{
	UCHAR Blue;
	UCHAR Green;
	UCHAR Red;
	UCHAR RGB_Reserved;
}RGB_QUAD;

typedef struct{
	BMPHEADER BMP_Header;
	RGB_QUAD   BMP_Colors[256];
}BITMAP;

typedef struct{
     int x;
     int y;
     int x1;
     int y1;
     int fx;
     int fy;
     int fx1;
     int fy1;
     int tabIndex;
     int Color;
     BOOL But_Bool;
     UCHAR getText[30];
     BOOL Bool;
}PBUTTON;

 int Text_Font(int x,int y);
 THEME Text_Color(int x,int y);
 void setDrawColor(THEME);
 PBUTTON PButton(FRAME *f1,int x,int y,int x1,int y1,int Attrib,int Color);
 BOOL CButton_Action(PBUTTON *But1);
 BOOL Button_Click(PBUTTON *B1);

 void setButtonColor(PBUTTON B1,COLOR Color);
 void Action_Paint_Edit(EDITOR *Edt,int Attrib);
 void XOR_draw(int x,int y,int x1,int y1,int Attrib);
 void PButton_Release(PBUTTON B1);
 void PButton_Push(PBUTTON B1);
 void Draw_Pen(void);
 BOOL Save_BMP(EDITOR *p1,const char *DFileName);
 BOOL Open_BMP(int x,int y,int x1,int y1,const char *SFileName);

