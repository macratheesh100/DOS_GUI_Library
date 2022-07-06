  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  //	               Save Image And Open Image
#include <stdio.h>
#include <math.h>
#include <graphics.h>

#include "Wiredefs.h"
#include "mouse.h"
#include "Paint.h"
#include "LoadImg.h"
//  Save TR Paint BMP File

BOOL Save_BMP(TR_PAINT *p1,const char *DFileName)
{
	BITMAP_INFO bmpinfo;
	FILE *out,*SupImg;
	BOOL ret = TRUE;
	int i,j,Width,Height;
	UCHAR line[2256];
	struct viewporttype viewinfo;
	getviewsettings(&viewinfo);
	setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
	setviewport(p1->fx,p1->fy,p1->x1,p1->y1,CLIP_ON);

	SupImg=fopen("SuppImg.Dat","rb");
	if(SupImg==NULL) ret = FALSE;
	else {
	  out=fopen(DFileName,"wb");
	  if(out==NULL) ret = FALSE;
	     else {
		 fread(&bmpinfo,sizeof(bmpinfo),1,SupImg);
		 Width = abs(p1->x1-p1->fx);
		 Height= abs(p1->y1-p1->fy);
		 bmpinfo.BMP_Header.BWidth= Width;
		 bmpinfo.BMP_Header.BHeight= Height;
		 fwrite(&bmpinfo,sizeof(bmpinfo),1,out);
		 fseek(out,bmpinfo.BMP_Header.BitmapFileOFFBits,SEEK_SET);
		 hideMouse();
		 for (i=Height;i>0;i--)
		 {
			for(j=Width;j>0;j--)
			   line[j]=(getpixel(j,i)*15);
			fwrite(&line[0],sizeof(unsigned char),Width,out);
		 }
		 showMouse();
		 fclose(out);
	}
	 fclose(SupImg);
     }
     setviewport(p1->x,p1->y,p1->x1,p1->y1,CLIP_OFF);
     setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  return ret;
}

//  Open TR Paint BMP File
BOOL Open_BMP(TR_PAINT *p1,const char *SFileName)
{
	BITMAP_INFO bmpinfo;
	FILE *In;
	BOOL ret = FALSE;
	int i,j,Width,Height,ss;
	UCHAR byte[2256];
	struct viewporttype viewinfo;
	getviewsettings(&viewinfo);
	setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
	setviewport(p1->fx,p1->fy,p1->x1,p1->y1,CLIP_ON);

	In=fopen(SFileName,"rb");
	  if(In==NULL) ret = TRUE;
	     else {
		 fread(&bmpinfo,sizeof(bmpinfo),1,In);
		 Width = bmpinfo.BMP_Header.BWidth;
		 Height = bmpinfo.BMP_Header.BHeight;
		 fseek(In,bmpinfo.BMP_Header.BitmapFileOFFBits,SEEK_SET);
		 hideMouse();
		 for (i=Height;i>0;i--)
		 {
		    fread(&byte[0],sizeof(unsigned char),Width,In);
			for(j=Width;j>0;j--)
			   putpixel(j,i,byte[j]/15);
		 }
		 showMouse();
		 fclose(In);
	}
     setviewport(p1->x,p1->y,p1->x1,p1->y1,CLIP_OFF);
     setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  return ret;
}
