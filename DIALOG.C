  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 		 Tool For Creating Window Components
#include <dos.h>
#include <mem.h>
#include <conio.h>
#include <alloc.h>
#include <graphics.h>
#include <string.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys\stat.h>

#include "DgnTool.h"
#include "WireDefs.h"
#include "mouse.h"
#define  VERTICAL  TRUE
 char *s;
 char *legal;
 size_t size;
 void *buf;
 BUFFER focus;
 WINDOW_FRAME TITLE;
 CURSOR TCUR;
 FOCUS Focus;
 BOOL Tab_Toggle;
 OLDTEXT oldText;
 WINDOW_PORT Window;
	   //  TOOL FOR  TEXTBOX

void InitStatus()
{
  Focus.Bool=FALSE;
  Tab_Toggle=TRUE;
  MWidth=0;
  s = (UCHAR *) malloc(MAXINPUT);
  if(s==NULL)
  { MsgBox("MEMORY ERROR",0);
  Exit(); }
  legal = (UCHAR *) malloc(MAXINPUT);
  if(legal==NULL)
  { MsgBox("MEMORY ERROR",0);
  Exit(); }
}

TEXTBOX ActionText(TEXTBOX *t1)
{
   int ch;
   BOOL Flag=FALSE;
   int x=0,y=6;
   int Cpos=0;
   int Min=0,SMin=0;
   int maxlength=50;
   int MAXWORD;//MAXINPUT+1;
   int len =strlen(t1->getText) , pos = len, insert = TRUE;
   struct viewporttype viewinfo;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1->tx,t1->ty,t1->tx1,t1->ty1,CLIP_ON);
   settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
   x = textwidth(t1->getText);
   t1->Bool=FALSE;
   setcolor(BLACK);
   MAXWORD=(t1->Size/8);
   strcpy(s,NULL);
   if(strcmp(t1->getText,NULL)!=0)
    {  strcpy(s,t1->getText);
       if(strlen(s)<t1->Size/8)
	   Cpos=strlen(s);
       else
	   Cpos=(t1->Size/10)-1;
    }
    Xorbar(x,y,x,(y+13),WHITE);
    do
   {
      Mouse=mouseStatus();
      if((Mouse.x < t1->tx || Mouse.x > t1->tx1 || Mouse.y < t1->ty || Mouse.y > t1->ty1) && Mouse.Button == 1)
      {
	   Xorbar(x,y,x,(y+13),WHITE);
	   t1->Bool=TRUE;
	   *t1=setText(*t1,s);
	   break; }
     if(kbhit())
     {
	 Xorbar(x,y,x,(y+13),WHITE);
	 switch(ch=getkey())
	 {
	   case ESC_KEY:
	   t1->Bool=TRUE;
	   Tab_Toggle=FALSE;
	   *t1=setText(*t1,s);
	   break;
	   case TAB_KEY:
	      t1->Bool=TRUE;
	      *t1=setText(*t1,s);
	     goto EX;
	   case RIGHTKEY:
	   if (pos < len)
	   {
	     pos++;
	    if(SMin>0 && pos >MAXWORD)
	    {
	     movmem(&s[SMin+1], legal, MAXWORD);
	     legal[strlen(legal)]='\0';
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(*t1);
	     outtextxy(0,y,legal);
	      if(SMin!=(len-SMin)&& pos<len-1)
		SMin++;
	     Flag=TRUE;
	     x=t1->Size-8;
	    }
	    else
	    { Cpos++;
	     x+=8;}
	   }
	   break;
	   case LEFTKEY:
	   if (pos > 0)
	   {
	     pos--;
	    if(SMin>0 && Cpos<=1 && pos <MAXWORD)
	    {
	     movmem(&s[SMin-1], legal, MAXWORD);
	     legal[strlen(legal)]='\0';
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(*t1);
	     outtextxy(0,y,legal);
	     Flag=TRUE;
	      if(SMin!=1)
		   SMin--;
	     Cpos=0;
	     x=1;
	    }
	    else
	    { Cpos--;
	     x-=8;}
	   }
	   break;
	   case DELKEY:
	   if (pos < len)
	   {
	     movmem(&s[pos + 1], &s[pos], len - pos);
	     len--;
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(*t1);
	     outtextxy(0,y,s);
	     Flag=TRUE;
	   }
	   break;
	   case ENTER_KEY:
	     t1->Bool=FALSE;
	     goto EX;
	   case BACK_SPACE:
	   if(pos>0)
	   {
	      movmem(&s[pos], &s[pos - 1], len - pos + 1);
	       pos--;
	       len--;
	      if(Min>0 && pos >MAXWORD)
	      {
		movmem(&s[(pos-Cpos)], legal,MAXWORD);
		legal[strlen(legal)]='\0';
		settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
		clearText(*t1);
		outtextxy(0,y,legal);
		Min--;
		SMin=Min;
		x=(Cpos*8);
	      }else
	      {
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(*t1);
	      outtextxy(0,y,s);
	      Flag=TRUE;
		  Cpos--;
		  x-=8;
	      }
	   }
	   break;
	  default:
	  if (((ch >= ' ') && (ch <= '~')) && (len < maxlength))
	  {
	      if (insert)
	      {
		 memmove(&s[pos + 1], &s[pos], len - pos + 1);
		 len++;
	      }
	      else if (pos >= len)
	      len++;
	      s[pos++] = ch;
	      s[len] = '\0';


	    if(Cpos>MAXWORD-1)
	     { x=t1->Size-8;
	       Cpos=MAXWORD+1;
	      movmem(&s[(pos-MAXWORD)],legal,MAXWORD);
	      legal[strlen(legal)]='\0';
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(*t1);
	      outtextxy(0,y,legal);
	      Min++;
	      SMin=Min-1;
	     }
	     else
	     {
	      Cpos++;
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(*t1);
	      outtextxy(0,y,s);
	      Flag=TRUE;
	      x=x+8;
	    }
	 }
	 break;
	}

	if(Cpos>MAXWORD-1)
	  x=t1->Size-8;
	Xorbar(x,y,x,(y+13),WHITE);
     }
  s[len] = 0;
  }while(ch != ESC);
  EX:
  if(Flag==TRUE && s!=NULL)
     *t1=setText(*t1,s);
   setviewport(t1->tx,t1->ty,t1->tx1,t1->ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   return *t1;
}
  // Mouse for text
BOOL  TextBox_Click(TEXTBOX *t)
{
 int flag=0;
 if(Mouse.x>=t->tx && Mouse.x<=t->tx1 && Mouse.y>=t->ty && Mouse.y<=t->ty1)
  if(Mouse.Button == 1)
    flag=1;
  return flag;
}

TEXTBOX ActionPWText(TEXTBOX t1)
{
   int ch;
   BOOL Flag=FALSE;
   int x=0,y=6,i;
   char PW[50];
   int Cpos=0;
   int Min=0,SMin=0;
   int maxlength=50;
   int MAXWORD;//MAXINPUT+1;
   int len =strlen(t1.getText) , pos = len, insert = TRUE;
   struct viewporttype viewinfo;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_ON);
   settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
   x=textwidth(t1.getText);
   t1.Bool=FALSE;
   setcolor(BLACK);
   MAXWORD=(t1.Size/8);
   strcpy(s,NULL);
   strcpy(PW,NULL);
   if(strcmp(t1.getText,NULL)!=0)
    {  strcpy(s,t1.getText);
       Cpos=strlen(s);
      for(i=0;i<strlen(s);i++)
	strcat(PW,"*");
    }
    Xorbar(x,y,x,(y+13),WHITE);
    do
   {
      Mouse=mouseStatus();
      if((Mouse.x < t1.tx || Mouse.x > t1.tx1 || Mouse.y < t1.ty || Mouse.y > t1.ty1) && Mouse.Button == 1)
      {
	   Xorbar(x,y,x,(y+13),WHITE);
	   t1.Bool=TRUE;
	   strcpy(t1.getText,s);
	   break; }
     if(kbhit())
     {
	 Xorbar(x,y,x,(y+13),WHITE);
	 switch(ch=getkey())
	 {
	   case ESC_KEY:
	   t1.Bool=TRUE;Tab_Toggle=FALSE;
	   t1=setText(t1,s);
	   break;
	   case TAB_KEY:
	      t1.Bool=TRUE;
	      strcpy(t1.getText,s);
	     goto EX;
	   case RIGHTKEY:
	   if (pos < len)
	   {
	     pos++;
	    if(SMin>0 && pos >MAXWORD)
	    {
	     movmem(&PW[SMin+1], legal, MAXWORD);
	     legal[strlen(legal)]='\0';
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(t1);
	     outtextxy(0,y,legal);
	      if(SMin!=(len-SMin)&& pos<len-1)
		SMin++;
	     Flag=TRUE;
	     x=t1.Size-8;
	    }
	    else
	    { Cpos++;
	     x+=8;}
	   }
	   break;
	   case LEFTKEY:
	   if (pos > 0)
	   {
	     pos--;
	    if(SMin>0 && Cpos<=1 && pos <MAXWORD)
	    {
	     movmem(&PW[SMin-1], legal, MAXWORD);
	     legal[strlen(legal)]='\0';
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(t1);
	     outtextxy(0,y,legal);
	     Flag=TRUE;
	      if(SMin!=1)
		   SMin--;
	     Cpos=0;
	     x=1;
	    }
	    else
	    { Cpos--;
	     x-=8;}
	   }
	   break;
	   case DELKEY:
	   if (pos < len)
	   {
	     movmem(&s[pos + 1], &s[pos], len - pos);
	     movmem(&PW[pos + 1], &PW[pos], len - pos);
	     len--;
	     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	     clearText(t1);
	     outtextxy(0,y,PW);
	     Flag=TRUE;
	   }
	   break;
	   case ENTER_KEY:
	     t1.Bool=FALSE;
	     goto EX;
	   case BACK_SPACE:
	   if(pos>0)
	   {
	      movmem(&s[pos], &s[pos - 1], len - pos + 1);
	      movmem(&PW[pos], &PW[pos - 1], len - pos + 1);
	       pos--;
	       len--;
	      if(Min>0 && pos >MAXWORD)
	      {
		movmem(&PW[(pos-Cpos)], legal,MAXWORD);
		legal[strlen(legal)]='\0';
		settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
		clearText(t1);
		outtextxy(0,y,legal);
		Min--;
		SMin=Min;
		x=(Cpos*8);
	      }else
	      {
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(t1);
	      outtextxy(0,y,PW);
	      Flag=TRUE;
		  Cpos--;
		  x-=8;
	      }
	   }
	   break;
	  default:
	  if (((ch >= ' ') && (ch <= '~')) && (len < maxlength))
	  {
	      if (insert)
	      {
		 memmove(&s[pos + 1], &s[pos], len - pos + 1);
		 memmove(&PW[pos + 1], &PW[pos], len - pos + 1);
		 len++;
	      }
	      else if (pos >= len)
	      len++;
	      PW[pos]='*';
	      s[pos++] = ch;

	      PW[len]='\0';
	      s[len] = '\0';

	    if(Cpos>MAXWORD-1)
	     { x=t1.Size-8;
	       Cpos=MAXWORD+1;
	      movmem(&PW[(pos-MAXWORD)],legal,MAXWORD);
	      legal[strlen(legal)]='\0';
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(t1);
	      outtextxy(0,y,legal);
	      Min++;
	      SMin=Min-1;
	     }
	     else
	     {
	      Cpos++;
	      settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
	      clearText(t1);
	      outtextxy(0,y,PW);
	      Flag=TRUE;
	      x=x+8;
	    }
	 }
	 break;
	}

	if(Cpos>MAXWORD-1)
	  x=t1.Size-8;
	Xorbar(x,y,x,(y+13),WHITE);
     }
  s[len] = 0;
  }while(ch != ESC);
  EX:
  if(Flag==TRUE && s!=NULL)
     strcpy(t1.getText,s);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   return t1;
}

TEXTBOX setText(TEXTBOX t1,UCHAR* txt)
{
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_ON);
   t1=clearText(t1);
   settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
   outtextxy(0,6,txt);
   strcpy(t1.getText,txt);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  return t1;
}
	 // Clearing the text
TEXTBOX clearText(TEXTBOX t1)
{
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_ON);
   setfillstyle(SOLID_FILL,WHITE);
   setcolor(WHITE);
   bar(0,2,t1.tx1-t1.tx-1,t1.ty1-t1.ty-4);
   setcolor(BLACK);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   strcpy(t1.getText,"");
   return t1;
}

void WORD_HIDE(TEXTBOX t1,int x,int y)
{
  struct viewporttype viewinfo;
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_ON);
  setfillstyle(SOLID_FILL,WHITE);
  setcolor(WHITE);
  bar(x,y-2,x+10,y+25);
  setcolor(BLACK);
  setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_OFF);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
}

TEXTBOX TextBox(int tx,int ty,UCHAR *txt,UINT16 Size)
{
   int tx1;
   int ty1;
   TEXTBOX t1;
   t1.tx=TITLE.Wx+tx+2;
   t1.ty=TITLE.Wy+ty;
   t1.tx1=TITLE.Wx+Size+tx-4;
   t1.ty1=TITLE.Wy+ty+TEXT_SIZE-2;
   t1.Size=Size;
   t1.fx=tx;
   t1.fy=ty;
   tx1=tx+Size-2;
   t1.tabIndex=Index;
   t1.Bool=FALSE;
   strcpy(t1.getText,"");
   Index++;
   setcolor(12);
   ty1=ty+TEXT_SIZE;
   setfillstyle(SOLID_FILL,WHITE);
   bar(tx,ty,tx1-2,ty1-2);
   setcolor(DARKGRAY);
   rectangle(tx,ty,tx1,ty1);
   rectangle(tx+1,ty+1,tx1-1,ty1-1);
   setcolor(WHITE);
   line(tx1-1,ty+1,tx1-1,ty1-1);
   line(tx+1,ty1-1,tx1-1,ty1-1);
   line(tx1,ty,tx1,ty1);
   line(tx,ty1,tx1,ty1);
   settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
   setcolor(BLACK);
   outtextxy(tx+5,ty,txt);
   return t1;
}
void Label(int x,int y,const char *txt)
{
   int x1; //x+strlen(txt)*6;
   int y1=y+20;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   settextstyle(LABEL_FONT,HORIZ_DIR,LABEL_FONT_SIZE);
   hideMouse();
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   x1=textwidth(txt);
   bar(x,y,x1,y1);
   setcolor(BLACK);
   setusercharsize(5,11, 3,6);
   outtextxy(x,y,txt);
   showMouse();
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}

 int getMaxx()
 {
  struct viewporttype viewinfo;
  getviewsettings(&viewinfo);
  return (viewinfo.right-viewinfo.left)-3;
 }

int getMaxy()
{
 struct viewporttype viewinfo;
 getviewsettings(&viewinfo);
 return (viewinfo.bottom-viewinfo.top)-3;
}

BOOL Button_Action(BUTTON But1)
{
  BOOL bool=FALSE;
  char ch=0;
  int Cx,Cy;
  struct viewporttype viewinfo;
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(But1.x,But1.y,But1.x1,But1.y1,CLIP_ON);
  But1.Bool=TRUE;
   while(TRUE)
   {
    Mouse=mouseStatus();
    if((Mouse.x < But1.x && Mouse.x > But1.x1 && Mouse.y < But1.y && Mouse.y > But1.y1) || Mouse.Button == 1)
	{ But1.Bool=TRUE; Focus.Bool = FALSE; break;}
      if(kbhit())
      {
	 ch=getch();
	 if(ch==ENTER_KEY)
	  { if(But1.Bool==TRUE)
	      {
		Button_Push(But1);
		 delay(10);
		Button_Release(But1);
		bool=TRUE;
		break;}
	  }
	  else
	 if(ch==ESC_KEY)
	  {But1.Bool=TRUE;Tab_Toggle=FALSE; break;}
	  else
	 if(ch==TAB_KEY || ch==LEFT_KEY || ch==RIGHT_KEY)
	 {But1.Bool=TRUE;  break;}
      }
//      else

  }
 setviewport(But1.x,But1.y,But1.x1,But1.y1,CLIP_OFF);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
 return bool;
}

void Button_Release(BUTTON b1)
{
   hideMouse();
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(b1.fx,b1.fy,b1.fx1-1,b1.fy1-1);
   setcolor(BLACK);
   rectangle(b1.fx,b1.fy,b1.fx1,b1.fy1);
   rectangle(b1.fx+1,b1.fy+1,b1.fx1-1,b1.fy1-1);
   setcolor(WHITE);
   line(b1.fx,b1.fy,b1.fx1,b1.fy);
   line(b1.fx+1,b1.fy+1,b1.fx1-1,b1.fy+1);
   line(b1.fx,b1.fy,b1.fx,b1.fy1);
   line(b1.fx+1,b1.fy+1,b1.fx+1,b1.fy1-1);
   setcolor(BLACK);
   settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy((b1.fx+b1.fx1)/2,(b1.fy+b1.fy1)/2,b1.getText);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   showMouse();
}

void Button_Push(BUTTON b1)
{
   hideMouse();
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(b1.fx,b1.fy,b1.fx1-1,b1.fy1-1);
   setcolor(WHITE);
   rectangle(b1.fx,b1.fy,b1.fx1,b1.fy1);
   rectangle(b1.fx+1,b1.fy+1,b1.fx1-1,b1.fy1-1);
   setcolor(BLACK);
   line(b1.fx,b1.fy,b1.fx1,b1.fy);
   line(b1.fx+1,b1.fy+1,b1.fx1-1,b1.fy+1);
   line(b1.fx,b1.fy,b1.fx,b1.fy1);
   line(b1.fx+1,b1.fy+1,b1.fx+1,b1.fy1-1);
   setcolor(BLACK);
   settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy((b1.fx+b1.fx1)/2,(b1.fy+b1.fy1)/2,b1.getText);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   showMouse();
}

BUTTON Button(int Bx,int By,int Bx1,int By1,UCHAR *txt)
{
   BUTTON b1;
   struct textsettingstype textinfo;
  hideMouse();
   gettextsettings(&textinfo);
   b1.x=TITLE.Wx+Bx;
   b1.y=TITLE.Wy+By;
   b1.x1=TITLE.Wx+Bx1;
   b1.y1=TITLE.Wy+By1;
   b1.fx=Bx;
   b1.fy=By;
   b1.fx1=Bx1;
   b1.fy1=By1;
   b1.Bool=FALSE;
   b1.tabIndex=Index;
   Index++;
   strcpy(b1.getText,txt);
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   bar(Bx,By,Bx1-1,By1-1);
   setcolor(BLACK);
   rectangle(Bx,By,Bx1,By1);
   rectangle(Bx+1,By+1,Bx1-1,By1-1);
   setcolor(WHITE);
   line(Bx,By,Bx1,By);
   line(Bx+1,By+1,Bx1-1,By+1);
   line(Bx,By,Bx,By1);
   line(Bx+1,By+1,Bx+1,By1-1);
   setcolor(BLACK);
   settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy((Bx+Bx1)/2,(By+By1)/2,txt);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
  showMouse();
  return b1;
}
BOOL getToggle()
{  return Tab_Toggle;
}

LISTBOX addList(LISTBOX l1,UCHAR *str)
{
   int x=2,y1=0;
   int i;
   struct viewporttype viewinfo;
  hideMouse();
   if(l1.Count<20)
   {
     getviewsettings(&viewinfo);
     setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
     setviewport(l1.tx,l1.ty,l1.tx1,l1.ty1,CLIP_ON);
     l1.Count=l1.Count+1;
     strcpy(l1.listText[l1.Count],str);
     settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
     for(i=1;i<=l1.Count;i++)
       y1=y1+15;
     setcolor(BLACK);
     outtextxy(x+2,y1+2,l1.listText[l1.Count]);
     setviewport(l1.tx,l1.ty,l1.tx1,l1.ty1,CLIP_OFF);
     setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  }
  showMouse();
 return l1;
}
LISTBOX clearList(LISTBOX l1)
{
   struct viewporttype viewinfo;
   hideMouse();
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(l1.tx,l1.ty,l1.tx1,l1.ty1,CLIP_ON);
   setfillstyle(SOLID_FILL,WHITE);
   setcolor(WHITE);
   bar(1,0,l1.tx1-l1.tx,l1.ty1-l1.ty-2);
   setlinestyle(DOTTED_LINE,1, 1);
   setcolor(BLUE);
   rectangle(3,2,l1.tx1-l1.tx-2,14);
   setviewport(l1.tx,l1.ty,l1.tx1,l1.ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   setcolor(BLACK);
   setlinestyle(SOLID_LINE,1, 1);
   l1.Count=0;
   strcpy(l1.getText,"");
   showMouse();
   return l1;
}

LISTBOX setList(LISTBOX t1,UCHAR* txt)
{
   struct viewporttype viewinfo;
  hideMouse();
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_ON);
   settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
   setfillstyle(SOLID_FILL,WHITE);
   bar(1,0,t1.tx1-t1.tx,13);
   outtextxy(3,3,txt);
   strcpy(t1.listText[0],txt);
   strcpy(t1.getText,txt);
   setlinestyle(DOTTED_LINE,1, 1);
   setcolor(BLUE);
   rectangle(1,1,t1.tx1-t1.tx-2,14);
   setviewport(t1.tx,t1.ty,t1.tx1,t1.ty1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   setcolor(BLACK);
   setlinestyle(SOLID_LINE,1, 1);
  showMouse();
  return t1;
}

BOOL  ListBox_Click(LISTBOX *t)
{
 int flag=0;
 if(Mouse.x>=t->tx && Mouse.x<=t->tx1 && Mouse.y>=t->ty && Mouse.y<=t->ty1)
  if(Mouse.Button == 1)
    flag=1;
  return flag;
}

LISTBOX ActionList(LISTBOX b1)
{
   char ch;
   int x=2,y=0;
   int Value=0;
   BOOL Break = FALSE;
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(b1.tx,b1.ty,b1.tx1,b1.ty1,CLIP_ON);
   Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
   b1.Bool=FALSE;
   while(TRUE)
   {
      Mouse=mouseStatus();
      if((Mouse.x < b1.tx || Mouse.x > b1.tx1 || Mouse.y < b1.ty || Mouse.y > b1.ty1) && Mouse.Button == 1) {
	   Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
	   b1.Bool=TRUE; break;
      }
     if(kbhit())
     {
	ch=getch();
	 Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
	 if(ch==TAB_KEY)
	  {strcpy(b1.getText,NULL);b1.Bool=TRUE; break; }
	 else
	 if(ch==ESC_KEY)
	  {b1.Bool=TRUE;Tab_Toggle=FALSE; break;}
	 else
	 if(ch==UP_KEY)
	  { y=y-15;Value--;}
	 if(ch==DOWN_KEY)
	  {y=y+15;Value++;}
	 else
	 if(ch==ENTER_KEY)
	 {
	  if(Value<=b1.Count && Value !=0)
	     {  strcpy(b1.getText,b1.listText[Value]);
		b1.listValue = Value;
		settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
		setfillstyle(SOLID_FILL,WHITE);
		bar(1,0,b1.tx1-b1.tx,13);
		setlinestyle(DOTTED_LINE,1, 1);
		setcolor(BLUE);
		rectangle(1,1,b1.tx1-b1.tx-2,14);
		outtextxy(3,4,b1.getText);
		break;
	     }
	 }
	 if(b1.Count<Value)
	   Value=0;
	 if(y > (15*b1.Count) || y>b1.Maxy)
	   { y=0; Value=0;}
	 else
	 if(y<=0)
	  { y=0;Value=0;}
	Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
     }else {
     Mouse=mouseStatus();
     if((Mouse.x > b1.tx && Mouse.x < b1.tx1 && Mouse.y > b1.ty && Mouse.y < b1.ty1) && Mouse.Button == 1) {
	Value++;
	if(b1.Count<Value)
	   Value=0;
	Mouse=mouseStatus();
	if(MouseOn1(b1.tx,b1.ty+(Value*15),b1.tx1,b1.ty+(Value*15)+13))
	{
	    Xorbar(2,(Value*15),x+b1.Width,(Value*15)+13,YELLOW);
	    while(MouseOn1(b1.tx,b1.ty+(Value*15),b1.tx1,b1.ty+(Value*15)+13)) {
	      Mouse=mouseStatus();
	      if(Mouse.Button==0)
	      {
		  if(Value<=b1.Count && Value !=0)
		  {  strcpy(b1.getText,b1.listText[Value]);
		     b1.listValue = Value;
		     settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
		     setfillstyle(SOLID_FILL,WHITE);
		     bar(1,0,b1.tx1-b1.tx,13);
		     setlinestyle(DOTTED_LINE,1, 1);
		     setcolor(BLUE);
		     rectangle(1,1,b1.tx1-b1.tx-2,14);
		     setlinestyle(SOLID_LINE,1, 1);
		     outtextxy(3,4,b1.getText);
		     Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
		     Break = TRUE;
		     break;
		  }
	      }
	      if(kbhit()) break;
	    }
	    Xorbar(2,(Value*15),x+b1.Width,(Value*15)+13,YELLOW);
	   if(Break == TRUE) {
	      Xorbar(x,y,x+b1.Width,(y+13),YELLOW);
	      b1.Bool=TRUE;
	      break;
	   }
	}
      }
    }
  }
  setviewport(b1.tx,b1.ty,b1.tx1,b1.ty1,CLIP_OFF);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  setcolor(BLACK);
  setlinestyle(SOLID_LINE,1, 1);
  return b1;
}
BOOL ShowFocus(FRAME f1,int x,int y,int Size)
{
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(f1.x,f1.y,f1.x1,f1.y1,CLIP_ON);
   hideMouse();
   Xorbar(x,y,x+Size,(y+10),YELLOW);
   if(Focus.Bool==TRUE)
       HideFocus(Focus.x,Focus.y,0);
   Focus.x=x;
   Focus.y=y;
   size=Size;
   Focus.Bool=TRUE;
   showMouse();
   setviewport(f1.x,f1.y,f1.x1,f1.y1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  return FALSE;
}
void HideFocus(int x,int y,int f)
{
    Xorbar(x,y,x+size,(y+10),YELLOW);
  if(f == 1)
    Xorbar(x,y,x+size,(y+10),YELLOW);
}

LISTBOX ListBox(int lx,int ly,int lx1,int ly1,UCHAR *txt)
{
   LISTBOX List1;
   List1.tx=TITLE.Wx+lx+1;
   List1.ty=TITLE.Wy+ly+12;
   List1.tx1=TITLE.Wx+lx1-2;
   List1.ty1=TITLE.Wy+ly1-2;
   List1.fx=lx;
   List1.fy=ly;
   List1.Maxx=lx1;
   List1.Maxy=ly1-ly-25;
   List1.Count=0;
   List1.Width=(lx1-lx-6);
   List1.tabIndex=Index;
   Index++;
   List1.Bool=FALSE;
   setfillstyle(SOLID_FILL,WHITE);
   settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
   setcolor(BLACK);
   outtextxy(lx,ly,txt);
   ly=ly+10;
   bar(lx,ly,lx1-2,ly1-2);
   setcolor(DARKGRAY);
   rectangle(lx,ly,lx1,ly1);
   rectangle(lx+1,ly+1,lx1-1,ly1-1);
   setcolor(WHITE);
   line(lx1-1,ly+1,lx1-1,ly1-1);
   line(lx+1,ly1-1,lx1-1,ly1-1);
   line(lx1,ly,lx1,ly1);
   line(lx,ly1,lx1,ly1);
   setlinestyle(DOTTED_LINE,1, 1);
   setcolor(BLUE);
   rectangle(lx+3,ly+2,lx1-2,ly+14);
   setcolor(BLACK);
   setlinestyle(SOLID_LINE,1, 1);

  return List1;
}
BOOL MsgBox(UCHAR* str,int Attrib)
{
 FRAME Msg;
 BUTTON B1,B2;
 BOOL b1;
 struct viewporttype viewinfo;
 struct textsettingstype textinfo;
 int Msg_Width,Msg_Height;
 int ret=0,Indx=1;
 int x,y;
 gettextsettings(&textinfo);
 getviewsettings(&viewinfo);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
 setviewport(0,0,getmaxx(),getmaxy(),CLIP_ON);
 settextstyle(STATUS_FONT,HORIZ_DIR,STATUS_FONT_SIZE);
 Msg_Width=textwidth(str)+100;
 Msg_Height=textheight(str)+80;
 x=(getmaxx()/2)-(Msg_Width/2);
 y=(getmaxy()/2)-(Msg_Height/2)-40;
 setviewport(x,y,x+Msg_Width,y+Msg_Height,CLIP_ON);

  Msg=Message_Frame(x,y,x+Msg_Width,y+Msg_Height,"Message Box:-");
   setcolor(BLACK);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(Msg_Width/2,Msg_Height/2,str);
   Tab_Toggle=TRUE;
   if(Attrib==2)
   {
     hideMouse();
     B1=Button((Msg_Width/2)-60,Msg_Height-30,(Msg_Width/2),(Msg_Height-40)+30,"Yes");
     B2=Button((Msg_Width/2)+5,Msg_Height-30,(Msg_Width/2)+65,(Msg_Height-40)+30,"No");
     showMouse();
     while(getToggle()==TRUE)
     {
      if(kbhit())
       { Indx++;
	if(Indx>=3)Indx=0;
	 if(B2.tabIndex==Indx)
	 {
	    B2.Bool=ShowFocus(Msg,B2.fx+2,B2.fy+5,55);
	    b1=Button_Action(B2);
	    if(b1==TRUE)
	    {
	       ret=5;
	       goto Exit1;
	    }
	 }
	 else
	 if(B1.tabIndex==Indx)
	 {
	    B1.Bool=ShowFocus(Msg,B1.fx+2,B1.fy+5,55);
	    b1=Button_Action(B1);
	    if(b1==TRUE)
	      {ret= 6; goto Exit1;}
	 }}else               // Mouse
	 if(ButtonPress(&B1)) {
	   ret= 5; goto Exit1;
	 }
	 else
	 if(ButtonPress(&B2)) {
	   ret= 6; goto Exit1;
	 }
	 else
	 if(CloseWindow(&Msg))
	    goto Exit1;
	 else
	 if(ButtonChk(&B1))
	   ButtonHlight(&B1);
	 else
	 if(WinClose(&Msg))
	    Close_Hlight(&Msg);
	 else
	 if(ButtonChk(&B2))
	   ButtonHlight(&B2);
      }
   }
   else{ hideMouse();
    B1=Button((Msg_Width/2)-32,Msg_Height-30,(Msg_Width/2)+32,(Msg_Height-40)+30,"OK");
    showMouse();
    while(TRUE)
    {
	 if(kbhit())
	   break;
	 if(ButtonPress(&B1)) {
	   ret= 6; goto Exit1;
	 }
	 else
	 if(ButtonChk(&B1))
	   ButtonHlight(&B1);
	 else
	 if(CloseWindow(&Msg))
	    goto Exit1;
	 else
	 if(WinClose(&Msg))
	    Close_Hlight(&Msg);
    }
  }
 Exit1:
 CLOSE_FRAME(&Msg);
 setviewport(x,y,x+Msg_Width,y+Msg_Height,CLIP_OFF);
 setviewport(0,0,getmaxx(),getmaxy(),CLIP_OFF);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
 settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
 settextjustify(LEFT_TEXT,TOP_TEXT);
 Focus.Bool=FALSE;
 return ret;
}

BOOL ButtonPress(BUTTON *t)
{
 int flag=0;
 char ch;
 Mouse=mouseStatus();
 if(Mouse.Button==1)
    if(Mouse.x>=t->x && Mouse.x<=t->x1 && Mouse.y>=t->y && Mouse.y<=t->y1) {
      Button_Push(*t);
      Xorbar(t->fx+2,t->fy+2,t->fx1-2,t->fy1-2,YELLOW);
      while(TRUE)
      {
	 if(kbhit()) {
	    if(getkey()==ESC)
	      break;
	  }
	 Mouse=mouseStatus();
	 if(Mouse.x>t->x && Mouse.x<t->x1 && Mouse.y>t->y && Mouse.y<t->y1 && getMBReleaseStatus()==0 )
	  {Button_Release(*t); flag=1; break;}
	 else
	  if((Mouse.x<t->x || Mouse.x>t->x1) || (Mouse.y<t->y || Mouse.y>t->y1))// &&getMBPressStatus()==0)
	  { Button_Release(*t); flag=0;
	   break;}
      }
  }
 return flag;
}

void ButtonHlight(BUTTON *t)
{
 hideMouse();
 Xorbar(t->fx+2,t->fy+2,t->fx1-2,t->fy1-2,YELLOW);
 showMouse();
 while(ButtonChk(t))
 {
	Mouse=mouseStatus();
	if(Mouse.Button!=0) break;
	if(kbhit()) break;
 }
 hideMouse();
 Xorbar(t->fx+2,t->fy+2,t->fx1-2,t->fy1-2,YELLOW);
 showMouse();
}

int ButtonChk(BUTTON *t)
{
 int flag=0;
 if(Mouse.x>=t->x && Mouse.x<=t->x1 && Mouse.y>=t->y && Mouse.y<=t->y1) flag=1;
 return flag;
}

void Scroll(int x,int y,int Width,int Height,int Attrib)
{
   BUTTON But1,But2;
   char cc[2];
   BUTTON But3,But4;
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   if(Attrib==VERTICAL)
   {
     bar(x,y,Width,Height);
     But1=Button(x,y,x+15,y+16,"");
     But2=Button(x,(Height-17),x+15,Height-1,"");
   }
   else
   {
     bar(x,y,Width,Height);
     cc[0]=17;
     cc[1]='\0';
     But3=Button(x,y,x+16,y+15,cc);
     But4=Button(Width-35,y,Width-19,y+15,"");
   }
}

void fileCopy(const char *dfile,const char *Sfile)
{
   char ch;
   FILE *inhandle,*outhandle;
   outhandle = fopen(dfile,"wb");
   if(outhandle == NULL)
   { MsgBox("File Cannot be Saved",0);
   }
   else
    {
       inhandle=fopen(Sfile,"rb");
       if(inhandle == NULL)
       {MsgBox("Cannot be open a input file",0);}
	else
	while(!feof(inhandle))
	{
	   ch = fgetc(inhandle);
	   fputc(ch,outhandle);
	}
  }
   fclose(inhandle);
   fclose(outhandle);
}