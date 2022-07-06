  /*****************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 			    About us
#include <dos.h>
#include <conio.h>
#include <graphics.h>

#include "DgnTool.h"
#include "mouse.h"

void Text2D(int x,int y,int size,char *text,int color1,int color2);

void About(int attr)
{
  int i;
  FRAME f1;
  f1=Frame_Window(160,110,440,350,"About us");
  Text2D(50,30,3,PROJECT_TITLE,LIGHTBLUE,WHITE);
  Text2D(20,70,1,"Developed By",BLUE,WHITE);
  Text2D(60,95,3,"     Ratheesh",GREEN,WHITE);
  Text2D(5,140,1,"macratheesh@gmail.com",RED,WHITE);
  Text2D(5,170,1,"macratheesh@gmail.com",9,WHITE);
  Text2D(5,200,1,"ratheesh@picksourcecode.com",9,WHITE);
 if(attr==WAIT)
 {
  while(TRUE)
  {
	     Mouse=mouseStatus();
	     if(CloseWindow(&f1))
		 goto Exit;
	     else
	     if(WinClose(&f1))
	       Close_Hlight(&f1);
	     if(kbhit())
		goto Exit;
  }
 }else
  delay(2000);
  Exit:
  CLOSE_FRAME(&f1);
}

void Text2D(int x,int y,int size,char *text,int color1,int color2)
{
  int i;
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,size);
  setcolor(color1);
  for(i=5;i<8;i++)
   outtextxy(x+i,y+i,text);
   setcolor(color2);
   outtextxy(x+i,y+i,text);
}