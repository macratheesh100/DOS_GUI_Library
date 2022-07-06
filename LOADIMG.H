#ifndef   _LOADING_H
#include  <graphics.h>
#include  <dos.h>

#include  "Wiredefs.h"

#define   VGA_LOAD     0x101
#define   ROWS         250
#define   COLS         250
#define   COLORS       255
#define   TEMP_BMP    "Temp.bmp"
#define   Maxx         640
#define   Maxy         480
#define   MAX   1000

 extern union REGS i,o;

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
	UINT32 BitCompression;
	UINT32 BitmapSizeImage;
	UINT32 bixpelspermeter;
	UINT32 biypelspermeter;
	UINT32 biclrused;
	UINT32 biclrimportant;
}BMPHEADER;

struct VgaModeInfoBlock
{
	UINT16  ModeAttributes;
	UCHAR WinAAttributes;
	UCHAR WinBAttributes;
	UINT16  WindowGranularity;
	UINT16  WinSize;
	UINT16  WinASegment;
	UINT16  WinBSegment;
	void (far *WinFuncPtr)(void);
	UINT16  BytesPerScanLine;
	UINT16  XResolution;
	UINT16  YResolution;
	UCHAR XCharSize;
	UCHAR YCharSize;
	UCHAR NumberOfPlanes;
	UCHAR BitsPerPixel;
	UCHAR NumberOfBanks;
	UCHAR MemoryModel;
	UCHAR BankSize;
	UCHAR NumberOfImagePages;
	UCHAR Reserved1;
	UCHAR RedMaskSize;
	UCHAR RedMaskPosition;
	UCHAR GreenMaskSize;
	UCHAR GreenMaskPosition;
	UCHAR BlueMaskSize;
	UCHAR BlueMaskPosition;
	UCHAR ReservedMaskSize;
	UCHAR ReservedMaskPosition;
	UCHAR DirectScreenModeInfo;
	UCHAR Reserved2[216];
};

typedef struct{
	UCHAR Blue;
	UCHAR Green;
	UCHAR Red;
	UCHAR RGB_Reserved;
}RGB_QUAD;

typedef struct{
	BMPHEADER BMP_Header;
	RGB_QUAD   BMP_Colors[COLORS];
}BITMAP_INFO;


typedef struct{
	char Red;
	char Green;
	char Blue;
}RGB;

// extern double PIX_PERCENT = 0.10;
 extern struct VgaModeInfoBlock Mode_Info;
 extern unsigned int bankshift;
 extern int oldmode;
 extern char far*sptr;
 extern int maxx,maxy;
 extern int xres,yres;
 extern int bytespl;
 extern int cbank;
 extern void (far *bankswitch)(void);
 extern	BITMAP_INFO bmpinfo;

void vCloseGraph(void);
void setBitmapWidth(int Width);
BOOL Load_BMP(int x,int y,CCHAR *fileName);
void setPalette(RGB Pal[COLORS]);
void VGA_Init_Graph(int GMode);
void setVesaMode(int Mode);
int GetSvgaModeInfo(int mode,struct  VgaModeInfoBlock  far *buffer);
int getVesaMode(void);
BOOL IsValidBitmap(CCHAR *FileName);
BOOL Load_BMP(int x,int y,CCHAR *fileName);


#define   _LOADING_H
#endif

