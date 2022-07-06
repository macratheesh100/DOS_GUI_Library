  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  //   			 Design Tools

#include <conio.h>
#include <string.h>
#include <graphics.h>
#include <assert.h>
#include <alloc.h>

#include "DgnTool.h"
#include "mouse.h"

 MOUSE Mouse;
 int Index;
 MENU_POSTION M;
 IN_FRAME IN;
 UINT16 MWidth;
 void far* MENU_MEM[16];
void Window_Button(int mx,int my,int mx1,int my1,BOOL Bool,UCHAR *STR)
{
   int x=mx;
   int y=my;
   int x1=mx1;
   int y1=my1;
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1,y1);
   setcolor(0);
   rectangle(x,y,x1,y1);
   setcolor(WHITE);
   line(x,y,x1,y);
   line(x,y,x,y1);
   settextstyle(STATUS_FONT,HORIZ_DIR,TITLE_FONT_SIZE);
   if(Bool==TRUE)
     setcolor(BLACK);
   else
     setcolor(DARKGRAY);
   outtextxy(x1-10,y+4,STR);
}

//   Tool For MAINWindow

MOUSE_COOR WINDOW_CLOSE_ACTIVATE()
{
  MOUSE_COOR Mouse_Coor;
  Mouse_Coor.Sx=TITLE.x1-20;
  Mouse_Coor.Sy=TITLE.y+4;
  Mouse_Coor.Ex=TITLE.x1-6;
  Mouse_Coor.Ey=TITLE.y+17;
return Mouse_Coor;
}

MOUSE_COOR WINDOW_MIN_ACTIVATE()
{
  MOUSE_COOR Mouse_Coor;
  Mouse_Coor.Sx=TITLE.x1-40;
  Mouse_Coor.Sy=TITLE.y+4;
  Mouse_Coor.Ex=TITLE.x1-25;
  Mouse_Coor.Ey=TITLE.y+17;
return Mouse_Coor;
}

// UINT8 Mz1,Mw1;
FRAME Frame_Window(int x,int y,int x1,int y1,UCHAR *text)
{
 FRAME f1;
 UINT16 z1,w1;
 size_t Buffer;
 UINT16 Bx,By,Bx1,By1;
 int i;
 assert(x1 <= getmaxx());
 assert(y1 <= getmaxy());
 TITLE.x=0; TITLE.y=0; TITLE.x1=x1-x; TITLE.y1=y1-y;
 TITLE.Wx=x;TITLE.Wy=y;TITLE.Wx1=x1;TITLE.Wy1=y1;
 f1.x=x;f1.y=y;f1.x1=x1;f1.y1=y1;
 f1.Cx=x1-20;f1.Cy=y+4;f1.Cx1=x1-6;f1.Cy1=y+17;
 setviewport(x,y,x1,y1,CLIP_ON);
 Index=0;
 Tab_Toggle=TRUE;
 Bx=TITLE.x;By=TITLE.y;Bx1=TITLE.x1;By1=TITLE.y1;
 z1=Bx1-Bx;
 w1=By1-By;
 z1=z1/MEM_BLOCKS;
 w1=w1/MEM_BLOCKS;
 for(i=0;i<MEM_BLOCKS-1;i++)
 {
    f1.Blocks[i][0]=Bx;
    f1.Blocks[i][1]=By;
    f1.Blocks[i][2]=Bx1;
    By=By+w1;
    f1.Blocks[i][3]=By;
 }
    f1.Blocks[MEM_BLOCKS-1][0]=Bx;
    f1.Blocks[MEM_BLOCKS-1][1]=By;
    f1.Blocks[MEM_BLOCKS-1][2]=Bx1;
    f1.Blocks[MEM_BLOCKS-1][3]=By1;
 hideMouse();
 for(i=0;i<MEM_BLOCKS;i++)
 {
   Buffer=imagesize(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3]);
   f1.WIN_MEM[i]=(UCHAR far*) farmalloc(Buffer);
   if(f1.WIN_MEM[i]==NULL)
    {   MsgBox("Not Enough Memory",0);
	closegraph();
	restorecrtmode();
	Exit();
    }
   getimage(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3],f1.WIN_MEM[i]);
   putimage(f1.Blocks[i][0],f1.Blocks[i][1],f1.WIN_MEM[i],XOR_PUT);
 }
 Normal_Frame(TITLE.x,TITLE.y,TITLE.x1,TITLE.y1);
 Normal_Frame_Title(text);
 Window_Button(TITLE.x1-20,TITLE.y+4,TITLE.x1-6,TITLE.y+17,TRUE,"X");
 Window_Button(TITLE.x1-40,TITLE.y+4,TITLE.x1-25,TITLE.y+17,FALSE,"-");
 showMouse();
 return f1;
}

// UINT8 Mz1,Mw1;

FRAME Frame_EDIT_Window(int x,int y,int x1,int y1,UCHAR *text)
{
 FRAME f1;
 UINT16 z1,w1;
 size_t Buffer;
 UINT16 Bx,By,Bx1,By1;
 int i;
 struct viewporttype viewinfo;

 assert(x1 <= getmaxx());
 assert(y1 <= getmaxy());

 TITLE.x=0; TITLE.y=0; TITLE.x1=x1-x; TITLE.y1=y1-y;
 TITLE.Wx=x;TITLE.Wy=y;TITLE.Wx1=x1;TITLE.Wy1=y1;
 f1.x=x;f1.y=y;f1.x1=x1;f1.y1=y1;
 getviewsettings(&viewinfo);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
 setviewport(x,y,x1,y1,CLIP_ON);
 Index=0;
 Tab_Toggle=TRUE;
 Bx=TITLE.x;By=TITLE.y;Bx1=TITLE.x1;By1=TITLE.y1;
 z1=Bx1-Bx;
 w1=By1-By;
 z1=z1/EDIT_MEM;
 w1=w1/EDIT_MEM;
 for(i=0;i<EDIT_MEM-1;i++)
 {
    f1.Blocks[i][0]=Bx;
    f1.Blocks[i][1]=By;
    f1.Blocks[i][2]=Bx1;
    By=By+w1;
    f1.Blocks[i][3]=By-1;
 }
    f1.Blocks[EDIT_MEM-1][0]=Bx;
    f1.Blocks[EDIT_MEM-1][1]=By;
    f1.Blocks[EDIT_MEM-1][2]=Bx1;
    f1.Blocks[EDIT_MEM-1][3]=By1;
 hideMouse();
 for(i=0;i<EDIT_MEM;i++)
 {
   Buffer=imagesize(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3]);
   f1.WIN_MEM[i]=(UCHAR far*) farmalloc(Buffer);
   if(f1.WIN_MEM[i]==NULL)
    {   MsgBox("Not Enough Memory",0);
	closegraph();
	restorecrtmode();
	Exit();
    }
   getimage(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3],f1.WIN_MEM[i]);
//   putimage(f1->Blocks[i][0],f1->Blocks[i][1],f1->WIN_MEM[i],XOR_PUT);
 }
 Frame(TITLE.x,TITLE.y,TITLE.x1,TITLE.y1);
 Frame_Title(text);
 Window_Button(TITLE.x1-20,TITLE.y+4,TITLE.x1-6,TITLE.y+17,TRUE,"X");
 Window_Button(TITLE.x1-40,TITLE.y+4,TITLE.x1-25,TITLE.y+17,FALSE,"-");
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
 showMouse();
 return f1;
}

void CLOSE_EDIT_FRAME(FRAME *CLOSE)
{
 int i;
 hideMouse();
 setviewport(CLOSE->x,CLOSE->y,CLOSE->x1,CLOSE->y1,CLIP_ON);
 clearviewport();
 for(i=0;i<EDIT_MEM;i++)
  putimage(CLOSE->Blocks[i][0],CLOSE->Blocks[i][1],CLOSE->WIN_MEM[i],XOR_PUT);
 setviewport(CLOSE->x,CLOSE->y,CLOSE->x1,CLOSE->y1,CLIP_OFF);
 setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
 for(i=0;i<EDIT_MEM;i++)
   farfree(CLOSE->WIN_MEM[i]);
 showMouse();
}

void Normal_Frame_Title(UCHAR *text)
{
   setfillstyle(SOLID_FILL, BLUE);
   bar(TITLE.x,TITLE.y,TITLE.x1,TITLE.y+TITLE_HEIGHT);
   setcolor(WHITE);
   rectangle(TITLE.x,TITLE.y,TITLE.x1-2,TITLE.y+TITLE_HEIGHT);
   setcolor(BLACK);
   line(TITLE.x1,TITLE.y,TITLE.x1,TITLE.y+TITLE_HEIGHT);
   line(TITLE.x1-1,TITLE.y,TITLE.x1-1,TITLE.y+TITLE_HEIGHT);
   setcolor(WHITE);
   settextstyle(TITLE_FONT,HORIZ_DIR,TITLE_FONT_SIZE);
   outtextxy(TITLE.x+5,TITLE.y-(textheight(text)/4),text);
}

void INIT_Window(int x,int y,int x1,int y1,UCHAR *text)
{
 assert(x1 <= getmaxx());
 assert(y1 <= getmaxy());
 TITLE.x=0; TITLE.y=0; TITLE.x1=x1-x; TITLE.y1=y1-y;
 TITLE.Wx=x;TITLE.Wy=y;TITLE.Wx1=x1;TITLE.Wy1=y1;
 setviewport(x,y,x1,y1,CLIP_ON);
 Frame(TITLE.x,TITLE.y,TITLE.x1,TITLE.y1);
 Frame_Title(text);
}

void CLOSE_FRAME(FRAME *CLOSE)
{
 int i;
 hideMouse();
 setviewport(CLOSE->x,CLOSE->y,CLOSE->x1,CLOSE->y1,CLIP_ON);
 clearviewport();
 for(i=0;i<MEM_BLOCKS;i++)
  putimage(CLOSE->Blocks[i][0],CLOSE->Blocks[i][1],CLOSE->WIN_MEM[i],XOR_PUT);
 setviewport(CLOSE->x,CLOSE->y,CLOSE->x1,CLOSE->y1,CLIP_OFF);
 setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
 for(i=0;i<MEM_BLOCKS;i++)
   farfree(CLOSE->WIN_MEM[i]);
 showMouse();
}

void Internal_Menu_Frame(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1-2,y1-2);
   setcolor(0);
   rectangle(x,y,x1,y1);
   setcolor(WHITE);
   line(x1,y,x1,y1);
   line(x,y1,x1,y1);
}

void Frame_Title(UCHAR *text)
{
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   setfillstyle(SOLID_FILL, BLUE);
   bar(TITLE.x,TITLE.y,TITLE.x1,TITLE.y+TITLE_HEIGHT);
   setcolor(WHITE);
   rectangle(TITLE.x,TITLE.y,TITLE.x1,TITLE.y+TITLE_HEIGHT);
   rectangle(TITLE.x+1,TITLE.y+1,TITLE.x1-1,TITLE.y+TITLE_HEIGHT+1);
   settextstyle(TITLE_FONT,HORIZ_DIR,TITLE_FONT_SIZE);
   Hlight_Frame(TITLE.x+8,TITLE.y+8,TITLE.x+17,TITLE.y+18);
   setfillstyle(SOLID_FILL,GREEN);
   bar(TITLE.x+9,TITLE.y+9,TITLE.x+15,(TITLE.y+17)-1);
   Hlight_Frame(TITLE.x+4,TITLE.y+5,TITLE.x+14,TITLE.y+15);
   setfillstyle(SOLID_FILL,12);
   bar(TITLE.x+5,TITLE.y+6,TITLE.x+13,(TITLE.y+15)-1);
   setcolor(WHITE);
   setusercharsize(7,13, 2, 5);
   outtextxy(TITLE.x+20,TITLE.y-(textheight(text)/4)+5,text);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}

void Frame(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1-1,y1-1);
   setcolor(WHITE);
   rectangle(x,y,x1,y1);
   rectangle(x+1,y+1,x1-1,y1-1);
   setcolor(WHITE);
   line(x,y,x1,y);
   line(x+1,y+1,x1-1,y+1);
   line(x,y,x,y1);
   line(x+1,y+1,x+1,y1-1);
}
void Internal_Frame(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1-2,y1-2);
   setcolor(0);
   rectangle(x,y,x1,y1);
   rectangle(x+1,y+1,x1-1,y1-1);
   setcolor(WHITE);
   line(x1,y,x1,y1);
   line(x1-1,y+1,x1-1,y1-1);
   line(x,y1,x1,y1);
   line(x+1,y1-1,x1-1,y1-1);
}

FRAME Message_Frame(int x,int y,int x1,int y1,UCHAR *text)
{
 FRAME f1;
 UINT16 z1,w1;
 size_t Buffer;
 UINT16 Bx,By,Bx1,By1;
 int i;
 assert(x1 <= getmaxx());
 assert(y1 <= getmaxy());
 Index=0;
 TITLE.x=0; TITLE.y=0; TITLE.x1=x1-x; TITLE.y1=y1-y;
 TITLE.Wx=x;TITLE.Wy=y;TITLE.Wx1=x1;TITLE.Wy1=y1;
 f1.x=x;f1.y=y;f1.x1=x1;f1.y1=y1;
 f1.Cx=x1-20;f1.Cy=y+4;f1.Cx1=x1-6;f1.Cy1=y+17;
 setviewport(x,y,x1,y1,CLIP_ON);
 Bx=TITLE.x;By=TITLE.y;Bx1=TITLE.x1;By1=TITLE.y1;
 z1=Bx1-Bx;
 w1=By1-By;
 z1=z1/MEM_BLOCKS;
 w1=w1/MEM_BLOCKS;
 for(i=0;i<MEM_BLOCKS-1;i++)
 {
    f1.Blocks[i][0]=Bx;
    f1.Blocks[i][1]=By;
    f1.Blocks[i][2]=Bx1;
    By=By+w1;
    f1.Blocks[i][3]=By;
 }
    f1.Blocks[MEM_BLOCKS-1][0]=Bx;
    f1.Blocks[MEM_BLOCKS-1][1]=By;
    f1.Blocks[MEM_BLOCKS-1][2]=Bx1;
    f1.Blocks[MEM_BLOCKS-1][3]=By1;
 hideMouse();
 for(i=0;i<MEM_BLOCKS;i++)
 {
   Buffer=imagesize(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3]);
   f1.WIN_MEM[i]=(UCHAR far*) farmalloc(Buffer);
   if(f1.WIN_MEM[i]==NULL)
    {   MsgBox("Not Enough Memory",0);
	closegraph();
	restorecrtmode();
	Exit();
    }
   getimage(f1.Blocks[i][0],f1.Blocks[i][1],f1.Blocks[i][2],f1.Blocks[i][3],f1.WIN_MEM[i]);
   putimage(f1.Blocks[i][0],f1.Blocks[i][1],f1.WIN_MEM[i],XOR_PUT);
 }
 Normal_Frame(TITLE.x,TITLE.y,TITLE.x1,TITLE.y1);
 Frame_Title(text);
 Window_Button(TITLE.x1-20,TITLE.y+4,TITLE.x1-6,TITLE.y+17,TRUE,"X");
 Window_Button(TITLE.x1-40,TITLE.y+4,TITLE.x1-25,TITLE.y+17,FALSE,"-");
 showMouse();
 return f1;
}

void Normal_Frame(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1,y1);
   setcolor(WHITE);
   rectangle(x,y,x1,y1);
   setcolor(BLACK);
   line(x1,y,x1,y1);
   line(x1-1,y,x1-1,y1);
   line(x,y1,x1,y1);
   line(x,y1-1,x1,y1-1);
}

void Internal_Menu_Window(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL,DARKGRAY);
   bar(x,y,x1-2,y1-2);
   setcolor(0);
   rectangle(x,y,x1,y1);
   rectangle(x+1,y+1,x1-1,y1-1);
   setcolor(WHITE);
   line(x1,y,x1,y1);
   line(x1-1,y+1,x1-1,y1-1);
   line(x,y1,x1,y1);
   line(x+1,y1-1,x1-1,y1-1);
   IN.x=x;
   IN.y=y;
   IN.x1=x1-2;
   IN.y1=y1-2;
}

IN_FRAME getIN()
{
   IN_FRAME I;
   I.x=IN.x+2;
   I.y=IN.y+2;
   I.x1=IN.x1-1;
   I.y1=IN.y1-1;
 return I;
}

void Status_Bar(UCHAR* Status,UCHAR *DATE_TIME)
{
 Frame(TITLE.x,TITLE.y1-Status_Bar_Height,TITLE.x1-2,TITLE.y1);
 Internal_Text_Frame(TITLE.x+3,TITLE.y1-Status_Bar_Height,TITLE.x1/2,TITLE.y1-1,Status);
 Internal_Text_Frame((TITLE.x1/2)+1,TITLE.y1-Status_Bar_Height,(TITLE.x1/2)+100,TITLE.y1-1,"BTS TEAM");
 Internal_Text_Frame(((TITLE.x1/2)+100)+1,TITLE.y1-Status_Bar_Height,TITLE.x1-2,TITLE.y1-1,DATE_TIME);
}
void Internal_Text_Frame(int x,int y,int x1,int y1,UCHAR *text)
{
  Internal_Frame(x,y,x1,y1);
  settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
  setcolor(BLACK);
  outtextxy(x+5,y+5,text);
}
	  // Menu Creating Frame

MENU menuHead(int x,int y,UCHAR *txt)
{
   MENU m1;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   m1.MHeight=22;
   m1.MWidth=100;
   m1.MTx=x;
   m1.MTy=y;
   m1.itemCount=0;
   m1.CLine=0;
   m1.Count=0;
   strcpy(m1.menuTitle,txt);
   settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
   setusercharsize(4,9, 2, 4);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   bar(x,y,x+textwidth(txt)+20,y+textheight(txt)-2);
   setcolor(BLACK);
   outtextxy(x,y-3,txt);
   m1.MTW=x+textwidth(txt);
   m1.MTH=y+textheight(txt)-2;
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
  return m1;
}

MENU addItem(MENU m1,UCHAR *str,BOOL Bool)
{
  struct textsettingstype textinfo;
  gettextsettings(&textinfo);
  strcpy(m1.menuItem[m1.itemCount],str);

  settextstyle(TRIPLEX_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
   if(m1.MWidth<textwidth(str))
      m1.MWidth=textwidth(str)+20;
  setusercharsize(4,9, 2, 4);
  settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
  settextjustify(LEFT_TEXT,TOP_TEXT);
  m1.Active[m1.itemCount]=Bool;
  if(strcmp(m1.menuItem[m1.itemCount],"-")==0)
   m1.CLine++;
   else
   {m1.Count++;m1.Index[m1.Count]=m1.itemCount;}
   m1.itemCount++;
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
  return m1;
}
//   Remake Menu Head
void REMake_Menu_Head(MENU m1[],int Num)
{
   int i=0;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
   setusercharsize(4,9, 2, 4);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   for(i=0;i<Num;i++)
   {
     bar(m1[i].MTx,m1[i].MTy,m1[i].MTx+textwidth(m1[i].menuTitle)+20,m1[i].MTy+textheight(m1[i].menuTitle)-2);
     setcolor(BLACK);
     outtextxy(m1[i].MTx,m1[i].MTy-3,m1[i].menuTitle);
   }
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}

MENU_POSTION showMenu(MENU m1)
{
 UINT16 z1,w1;
 int Ix,Iy,Ix1,Iy1;
 size_t Buffer;
 UINT16 Bx,By,Bx1,By1;
 int NM=0;
 int i,x,y,x1,y1,k=0,q=0;
 struct textsettingstype textinfo;
 gettextsettings(&textinfo);
 hideMouse();
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(m1.MTx,m1.MTy,m1.MTx+textwidth(m1.menuTitle),m1.MTy+16);
 settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
 setusercharsize(4,9, 2, 4);
 Internal_Menu_Frame(m1.MTx,m1.MTy,m1.MTx+textwidth(m1.menuTitle),m1.MTy+16);
 setcolor(BLACK);
 outtextxy(m1.MTx,m1.MTy-2,m1.menuTitle);

 x=m1.MTx;
 y=m1.MTy+18;
 x1=m1.MTx+m1.MWidth;
 y1=m1.MTy+(m1.MHeight*(m1.itemCount-m1.CLine))+19;

 assert(x1 <= getmaxx());
 assert(y1 <= getmaxy());

 m1.x=0; m1.y=0; m1.x1=x1-x; m1.y1=y1-y;
 m1.Wx=x;m1.Wy=y;m1.Wx1=x1;m1.Wy1=y1;

 setviewport(x,y,x1,y1,CLIP_ON);
 Bx=m1.x;By=m1.y;Bx1=m1.x1;By1=m1.y1;
 z1=Bx1-Bx;
 w1=By1-By;
 z1=z1/MENU_BLOCKS;
 w1=w1/MENU_BLOCKS;
 for(i=0;i<MENU_BLOCKS-1;i++)
 {
    m1.Blocks[i][0]=Bx;
    m1.Blocks[i][1]=By;
    m1.Blocks[i][2]=Bx1;
    By=By+w1;
    m1.Blocks[i][3]=By-1;
 }
    m1.Blocks[MENU_BLOCKS-1][0]=Bx;
    m1.Blocks[MENU_BLOCKS-1][1]=By;
    m1.Blocks[MENU_BLOCKS-1][2]=Bx1;
    m1.Blocks[MENU_BLOCKS-1][3]=By1;
 for(i=0;i<MENU_BLOCKS;i++)
 {
   Buffer=imagesize(m1.Blocks[i][0],m1.Blocks[i][1],m1.Blocks[i][2],m1.Blocks[i][3]);
   MENU_MEM[i]=(UCHAR far*) farmalloc(Buffer);
   if(MENU_MEM[i]==NULL)
    {   MsgBox("Not Enough Memory",0);
	closegraph();
	restorecrtmode();
	Exit();
    }
   getimage(m1.Blocks[i][0],m1.Blocks[i][1],m1.Blocks[i][2],m1.Blocks[i][3],MENU_MEM[i]);
 }

 Normal_Frame(0,0,m1.MWidth,(m1.MHeight*(m1.itemCount-m1.CLine)+1));
 Ix=5;Iy=textheight(m1.menuItem[i])+7;
  k=0;
  for(i=0;i<m1.itemCount;i++)
  {
   settextstyle(SMALL_FONT,HORIZ_DIR,5);
   setcolor(BLACK);
    if(strcmp(m1.menuItem[k],"-")==0)
    { CrossLine(Ix-2,(i*Iy),m1.MWidth-8);k=k+1;q=q+1;}
    if(!m1.Active[k])
    {
	setcolor(WHITE);
	outtextxy(Ix+1,(i*Iy)+1,m1.menuItem[k]);
	setcolor(DARKGRAY);
	outtextxy(Ix,(i*Iy),m1.menuItem[k]);
    }else{
     setcolor(BLACK);
     outtextxy(Ix,(i*Iy),m1.menuItem[k]);}
     k++;
  }
  NM=m1.itemCount-m1.CLine;
  showMouse();
  settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
  settextjustify(LEFT_TEXT,TOP_TEXT);
  while(Mouse.Button==1) Mouse=mouseStatus();
	M=HandleMenu(NM,m1);
 return M;
}
//	outtextxy(m1.x+15,tm->y1+9+i*20,H[i]);

void CrossLine(int x,int y,int Width)
{
   setcolor(BLACK);
   line(x,y,x+Width,y);
   setcolor(WHITE);
   line(x,y+1,x+Width,y+1);
   setcolor(BLACK);
}


//	int Index=-1;
MENU_POSTION HandleMenu(int n,MENU tm)
{
	int i;
	char Key,str[3];
	int x,x1,y1;
	int Mx,Mx1,My1;
	int Cx,Cy;
	struct textsettingstype textinfo;
	gettextsettings(&textinfo);
	setcolor(0);
	i=1;
	x=2;
	x1=tm.MWidth-3;
	y1=tm.MHeight;

	Mx=tm.MTx;
	Mx1=tm.MTx+tm.MWidth-3;
	My1=tm.MHeight;
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
	setusercharsize(6,10, 1, 2);
	M.Bool=TRUE;
	M.EFLAG=FALSE;
	M.Flag=3;
	Key=0;
	M.MENU_INDEX=40;
	while(TRUE)
	{
		Mouse=mouseStatus();
		if(kbhit())
		{
		   i=0;
		  while(TRUE)
		  {
		   if(kbhit())
		   {
		    if(Key==UP_KEY || Key==DOWN_KEY)
		    Xorbar(x,(i*y1)-20,x1,(18+i*y1)-20,BROWN);
		    Key=getch();
		    if(Key==UP_KEY)
		    {if(i<=1)i=n;
		     else
		     i--;}
		    else
		    if(Key==DOWN_KEY)
		      {	if(i>=n)i=1;
			else
			i++;
			}
		    else
		    if(Key==ENTER_KEY)
		      {M.EFLAG=TRUE;
			if(tm.Active[tm.Index[i]]==FALSE)
			   M.MENU_INDEX=-1;
			 else
			   M.MENU_INDEX=i;
			 M.Bool=TRUE;
			goto Ex1;
		    }
		    else
		    if(Key==LEFT_KEY)
		    { M.Bool=FALSE;M.Flag=FALSE; goto Ex1;}
		    else
		    if(Key==RIGHT_KEY)
		    { M.Bool=FALSE;M.Flag=TRUE; goto Ex1;}
		    if(Key==UP_KEY || Key==DOWN_KEY)
		       Xorbar(x,(i*y1)-20,x1,(18+i*y1)-20,BROWN);
		   }
		   PollMouseStatus(&Cx,&Cy);
		   if(Cx>Mx && Cy >My1+20 && Cx <Mx1 && Cy < (My1+18+n*20))
		    {Xorbar(x,(i*y1)-20,x1,(18+i*y1)-20,BROWN);break;}

		    Mouse=mouseStatus();
		    if(Mouse.Button==1|| Key==ESC_KEY)
		      goto xxxx;
		 }
		}
		if(Mouse.Button==1||Key==ESC_KEY)
		{M.Bool=TRUE;M.EFLAG=TRUE;break;}
		if(i==n)
		 i=0;
		 i++;
		      xxxx:
			Mouse=mouseStatus();
			if(MouseOn1(Mx,(i*My1)+20,Mx1,(18+i*y1)+20))
			{
			    Xorbar(x,(i*y1)-20,x1,(18+i*y1)-20,BROWN);
			    while(MouseOn1(Mx,(i*My1)+20,Mx1,(18+i*y1)+20)) {
			      Mouse=mouseStatus();
				//if(Mouse.Button==1)
				if(objectAction_Click())
				{
				     if(tm.Active[tm.Index[i]]==FALSE)
				       M.MENU_INDEX=-1;
				     else
				       M.MENU_INDEX=i;
				     goto Ex1;
				}
				if(kbhit()) break;
			    }
			    Xorbar(x,(i*y1)-20,x1,(18+i*y1)-20,BROWN);
			}
	}
     Ex1:
     hideMenu(tm);
     settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
     settextjustify(LEFT_TEXT,TOP_TEXT);
return M;
}


BOOL MouseOn1(int cx,int cy,int cx1,int cy1)
{
 int flag=0;
 Mouse=mouseStatus();
 if(Mouse.x>cx && Mouse.x<cx1 && Mouse.y>cy && Mouse.y<cy1) flag=1;
 return flag;
}

BOOL CloseWindow(FRAME *t)
{
 int flag=0;
 Mouse=mouseStatus();
 if(Mouse.Button==1)
    if(Mouse.x>=t->Cx && Mouse.x<=t->Cx1 && Mouse.y>=t->Cy && Mouse.y<=t->Cy1) flag=1;
 return flag;
}

void Close_Hlight(FRAME *t)
{
 int x1=(t->x1-t->x1)+t->x1-t->x;
 int y=t->y-t->y;
 hideMouse();
 Xorbar(x1-20,y+4,x1-6,y+17,YELLOW);
 showMouse();
 while(WinClose(t))
 {
	Mouse=mouseStatus();
	if(Mouse.Button!=0) break;
	if(kbhit()) break;
 }
 hideMouse();
 Xorbar(x1-20,y+4,x1-6,y+17,YELLOW);
 showMouse();
}

int WinClose(FRAME *t)
{
 int flag=0;
 if(Mouse.x>=t->Cx && Mouse.x<=t->Cx1 && Mouse.y>=t->Cy && Mouse.y<=t->Cy1) flag=1;
 return flag;
}

void Hlight_Frame(int x,int y,int x1,int y1)
{
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(x,y,x1,y1);
   setcolor(WHITE);
   rectangle(x,y,x1,y1);
   setcolor(BLACK);
   line(x1,y,x1,y1);
   line(x,y1,x1,y1);
}

void menuHlight(MENU *t)
{
 struct textsettingstype textinfo;
 gettextsettings(&textinfo);
 hideMouse();
 Hlight_Frame(t->MTx,t->MTy,t->MTW,t->MTH+3);
 settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
 setusercharsize(4,9, 2, 4);
 setcolor(BLACK);
 outtextxy(t->MTx+1,t->MTy-3,t->menuTitle);
 showMouse();
 while(MouseOn(t))
 {
	Mouse=mouseStatus();
	if(Mouse.Button!=0) break;
	if(kbhit()) break;
 }
 hideMouse();
 setcolor(7);
 settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
 setusercharsize(4,9, 2, 4);
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(t->MTx,t->MTy,t->MTW,t->MTH+3);
 setcolor(BLACK);
 outtextxy(t->MTx,t->MTy-3,t->menuTitle);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
 showMouse();
}

void EXit_Hlight(MOUSE_COOR *t)
{
 hideMouse();
 Xorbar(t->Sx,t->Sy,t->Ex,t->Ey,YELLOW);
 showMouse();
 while(WindowEx(t))
 {
	Mouse=mouseStatus();
	if(Mouse.Button!=0) break;
	if(kbhit()) break;
 }
 hideMouse();
 Xorbar(t->Sx,t->Sy,t->Ex,t->Ey,YELLOW);
 showMouse();
}

int WindowEx(MOUSE_COOR *t)
{
 int flag=FALSE;
 if(Mouse.x>=t->Sx && Mouse.x<=t->Ex && Mouse.y>=t->Sy && Mouse.y<=t->Ey) flag=TRUE;
 return flag;
}

void hideMenu(MENU CLOSE)
{
 int i;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
 if(MENU_MEM[0]!=NULL)
 {
   hideMouse();
   setviewport(CLOSE.Wx,CLOSE.Wy,CLOSE.Wx1,CLOSE.Wy1,CLIP_ON);
   clearviewport();
   for(i=0;i<MENU_BLOCKS;i++)
     putimage(CLOSE.Blocks[i][0],CLOSE.Blocks[i][1],MENU_MEM[i],XOR_PUT);
   setviewport(CLOSE.Wx,CLOSE.Wy,CLOSE.Wx1,CLOSE.Wy1,CLIP_OFF);
   for(i=0;i<MENU_BLOCKS;i++)
     farfree(MENU_MEM[i]);
   setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
   settextstyle(MENU_FONT,HORIZ_DIR,MENU_FONT_SIZE);
   setusercharsize(4,9, 2, 4);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   bar(CLOSE.MTx,CLOSE.MTy,CLOSE.MTx+textwidth(CLOSE.menuTitle),CLOSE.MTy+16);
   setcolor(BLACK);
   outtextxy(CLOSE.MTx,CLOSE.MTy-2,CLOSE.menuTitle);
   setviewport(0,0,getmaxx(),getmaxy(),CLIP_OFF);
   showMouse();
 }
 else
   MsgBox("Mem Error",0);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}

void Xorbar(int sx,int sy,int ex,int ey,int c)
{
 int i;
 setwritemode(1);
 setcolor(c);
 hideMouse();
 for(i=sy;i<=ey;i++)
   line(sx,i,ex,i);
 showMouse();
 setcolor(BLACK);
 setwritemode(0);
}
