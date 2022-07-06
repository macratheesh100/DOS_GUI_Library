  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  //   			 Loading *.Bmp File
#include <stdio.h>
#include <conio.h>
#include <graphics.h>

#include "Wiredefs.h"
#include "DgnTool.h"
#include "LoadImg.h"

 double PIX_PERCENT;
 struct VgaModeInfoBlock Mode_Info;
 unsigned int bankshift;
 BITMAP_INFO bmpinfo;
 int oldmode;
 char far*sptr;
 int maxx,maxy;
 int xres,yres;
 int bytespl;
 int cbank;
 void (far *bankswitch)(void);

//  Loading image

   // ******************* Loading the Image *********************//

BOOL Load_BMP(int x,int y,CCHAR *fileName)
{
	RGB  Pal[COLORS];
	FILE *Bitmap_File;
	BOOL ret=FALSE;
	int gdriver, gmode, errorcode;
	int Width,Height;
	int i,j,c;
	int bank;
	UCHAR byte[500];
	UINT16 k;
	long add;
	x=0;
	y=0;
	if(IsValidBitmap(fileName)){
	  Bitmap_File=fopen(fileName,"rb");
	  if (Bitmap_File==NULL)
	  {  MsgBox("Cannot open Bitmap File: Error",0);
	     vCloseGraph();
	     return ret;
	  }
	  fread(&bmpinfo,sizeof(bmpinfo),1,Bitmap_File);
	  fseek(Bitmap_File,bmpinfo.BMP_Header.BitmapFileOFFBits,SEEK_SET);
	  Width=bmpinfo.BMP_Header.BWidth;
	  Height=bmpinfo.BMP_Header.BHeight;
	  x=(Maxx/2)-(Width/2)-2;
	  y=(Maxy/2)-(Height/2)-2;
	  for(i=0;i<=COLORS;i++)
	  {
		Pal[i].Red=bmpinfo.BMP_Colors[i].Red/4;
		Pal[i].Green=bmpinfo.BMP_Colors[i].Green/4;
		Pal[i].Blue=bmpinfo.BMP_Colors[i].Blue/4;
	  }
	  VGA_Init_Graph(VGA_LOAD);
	  ret=TRUE;
	  setBitmapWidth(1000);
	  setPalette(Pal);
	  for(i=0;i<Height;i++)
	  {
		fread(&byte[0],sizeof(unsigned char),Width,Bitmap_File);
		for(j=0;j<Width;j++)
		{
			c=(int)byte[j];
			add=(long)(y+Height-i)*bytespl+x+j;
			bank=(int)(add >> 16);
			if(cbank!=bank)
			{
				cbank=bank;
				bank <<=bankshift;
				asm mov bx,0;
				asm mov dx,bank;
				bankswitch();
				asm mov bx,1;
				bankswitch();
		       }
		       *(sptr+(add & 0XFFFF))=(char)c;
		}
	  }
    getch();
    fclose(Bitmap_File);
    vCloseGraph();
   }
   return ret;
}


BOOL IsValidBitmap(CCHAR *FileName)
{
	BOOL ret=TRUE;
	FILE *fp;
	fp=fopen(FileName,"rb");
	if(fp==NULL){
	  MsgBox("Unable to Open the File",0);
	  ret=FALSE;
	 }else {
		fread(&bmpinfo,sizeof(bmpinfo),1,fp);
		fclose(fp);
		if(!(bmpinfo.BMP_Header.BitmapFileType[0]=='B' && bmpinfo.BMP_Header.BitmapFileType[1]=='M')){
		MsgBox("Not a valid BMP File",0);
		ret=FALSE;
		}else {
		     if(!(bmpinfo.BMP_Header.BitCompression==0)){
			  MsgBox("Not a valid BMP File",0);
			  ret=FALSE;
			}else{
			     if(!(bmpinfo.BMP_Header.BCount==8)){
				  MsgBox("Not a valid BMP File",0);
				  ret=FALSE;
			     }
		      }
	      }
      }
   return ret;
}

void setBitmapWidth(int Width)
{
	union REGS in,out;
	in.x.ax=0x4f06;
	in.x.bx=0x0000;
	in.x.cx=Width;
	int86(0x10,&in,&out);
	bytespl=(int)out.x.bx;
	maxy=(int)out.x.dx;
	maxx=(int)out.x.cx;
	return;
}

void setPalette(RGB Pal[COLORS])
{
	union  REGS reg;
	struct SREGS inreg;
	reg.x.ax=0x1012;
	segread(&inreg);
	inreg.es=inreg.ds;
	reg.x.bx=0;
	reg.x.cx=COLORS;
	reg.x.dx=(int)&Pal[0];
	int86x(0x10,&reg,&reg,&inreg);
	return;
}

void VGA_Init_Graph(int GMode)
{
	setVesaMode(GMode);
	setBitmapWidth(xres);
	return;
}

int GetSvgaModeInfo(int mode,struct  VgaModeInfoBlock  far *buffer)
{
	struct REGPACK reg;
	reg.r_ax = 0x4f01;
	reg.r_es = FP_SEG(buffer);
	reg.r_di = FP_OFF(buffer);
	reg.r_cx = mode;
	intr(0x10,&reg);
	if(reg.r_ax  != 0x004f )
		return 1 ;
	else
		return 0;
}

int getVesaMode(void)
{
	union REGS in,out;
	in.x.ax=0x4f03;
	int86(0x10,&in,&out);
	return out.x.bx;
}

void setVesaMode(int Mode)
{
	struct REGPACK reg;
	oldmode=getVesaMode();
	reg.r_ax = 0x4f02;
	reg.r_bx = Mode;
	intr(0x10,&reg);
	GetSvgaModeInfo(getVesaMode(),&Mode_Info);
	xres=Mode_Info.XResolution;
	yres=Mode_Info.YResolution;
	maxx=xres;
	bytespl=Mode_Info.BytesPerScanLine;
	bankshift=0;
	while((unsigned)(64>>bankshift)!=Mode_Info.WindowGranularity)
		bankshift++;
	bankswitch=Mode_Info.WinFuncPtr;
	cbank=-1;
	sptr=(char far *)(((long)0xA000)<<16 | 0);
	return;
}

void vCloseGraph(void)
{
	VGA_Init_Graph(oldmode);
	maxx=xres;
	return;
}
