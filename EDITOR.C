  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 			Tools For Text Editor
#include <io.h>
#include <conio.h>
#include <mem.h>
#include <string.h>
#include <alloc.h>
#include <stdio.h>
#include <graphics.h>

#include <fcntl.h>
#include <sys\stat.h>

#include "DgnTool.h"
#include "Editor.h"
#include "mouse.h"

#define   MAXI     50

 EDITOR *Step_Up(EDITOR *Edit,int LINE,int pos);
 EDITOR *Step_Down(EDITOR *Edt,int LINE,int pos,int step);
 void clearEdt(EDITOR *t1,int x,int y,int width,int height);
 int textStyle = DEFAULT_FONT;
 int textSize  = 1;
 int textColor =BLACK;
 int textBKColor =WHITE;
 int Height = 10;
 int Width = 8;
 int i;

 void setFontStyle(THEME F_Style)
 { textStyle = F_Style.textFont;
   textSize = F_Style.textSize;
   settextstyle(textStyle,HORIZ_DIR,textSize);
   Height  = textheight("A");
   Width   = textwidth("A");
 }

 void setFColor(THEME F_Color)
 { textColor = F_Color.FColor;
   textBKColor = F_Color.BKColor;
 }

void editPData(int x,int y,int x1,int y1)
{
  EDITOR *Edt;
  Edt = (EDITOR*) malloc(sizeof(EDITOR*)*sizeof(EDITOR*));
  if(Edt == NULL) {
    MsgBox("Memory Error",0);
    return;
  }
  Edt->x  = x;
  Edt->y  = y;
  Edt->x1 = x1;
  Edt->y1 = y1;
  Edt->ENDLINE=0;
  Edt->LINE=0;
  Edt->CPos=0;
  Edt->ROW_Flag[0]=FALSE;
  strcpy(Edt->Edit_Array[0],NULL);
  Edt->TRWord[0].textColor = BLACK;
  Edt->TRWord[0].textStyle = TEXTBOX_FONT;
  Edt->TRWord[0].textSize  = TEXTBOX_FONT_SIZE;
  Edt->TRWord[0].textHeight = 10;
  Edt->TRWord[0].textWidth  = 8;
  ActionPEdit(*(&Edt));
  free(Edt);
}

void ActionPEdit(EDITOR *Edt)
{
   int ch;
   int Cx,Cy;
   int maxlength=EDITLEN-1;
   unsigned int x=0,y=0;
   char ptr[MAXINPUT];
   char str[2];
   int len =0 , pos = len, insert = TRUE,Tlen=0;
   int LINE=0;
   int Sx,Sy,Sx1;
   BOOL SFlag=FALSE;
   struct viewporttype viewinfo;
   struct textsettingstype textinfo;
   gettextsettings(&textinfo);
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(Edt->x,Edt->y,Edt->x1,Edt->y1,CLIP_ON);
   settextstyle(textStyle,HORIZ_DIR,textSize);
   strcpy(s,NULL);
   Edt->Sx=0;
   Edt->Ex=0;
   pos=0;
   y=0;
   setcolor(textColor);
   Xorbar(x,y,x+1,(y+Height-1),WHITE);
   do
   {
     PollMouseStatus(&Cx,&Cy);
     if(Cx < Edt->x || Cy  < Edt->y || Cx >  Edt->x1 || Cy > Edt->y1)
       if(objectAction_Click()){
	  Xorbar(x,y,x+1,(y+Height-1),WHITE);
       break;}
     if(kbhit())
     {
	 Xorbar(x,y,x+1,(y+Height-1),WHITE);
	 switch(ch=getkey())
	 {
	   case CTRLRIGHTKEY:
	    if(SFlag==TRUE)
	    {
	       if (pos < len && s !=NULL)
	       {
	       clearEdt(Edt,0,y,(strlen(s)+1)*Width,Height);
	       outtextxy(0,y,s);
	       if(x<Sx1)
		{ Sx1=x-2;Sx=x;Edt->Sx=pos;}
		  Sx1=Sx1+Width;
		  Xorbar(Sx,y,Sx1,(y+Height-1),YELLOW);
		  Edt->Ex=pos;
		  Edt->LINE=LINE;
		  pos++; x+=Width;
		}
		 else
		   SFlag=FALSE;
	    }
	    else
	    if(SFlag==FALSE && pos<len)
	    { SFlag=TRUE;Sx=x;Sx1=x;Edt->Sx=pos;}
	   break;
	   case CTRLLEFTKEY:
	    if(SFlag==TRUE)
	    {
	       if (pos > 0 && s!=NULL)
	       {
		 clearEdt(Edt,0,y,(strlen(s)+1)*Width,Height);
		 outtextxy(0,y,s);
	       if(x>Sx1)
		{ Sx1=x;Sx=x;Edt->Sx=pos;}
		  Sx1=Sx1-Width;
		  Xorbar(Sx,y,Sx1,(y+Height-1),YELLOW);
		  Edt->Ex=pos;
		  Edt->LINE=LINE;
		  pos--; x-=Width;
		 }
		 else
		   SFlag=FALSE;
	    }
	    else
	    if(SFlag==FALSE && pos<=len)
	    { SFlag=TRUE;Sx=x;Sx1=x;Edt->Sx=pos;}
	   break;
	   case ESC_KEY:
	     Xorbar(x,y,x+1,(y+Height-1),WHITE);
	     setcolor(BLACK);
	   break;
	   case TAB_KEY:
	   break;
	   case RIGHTKEY:
	   if (pos < len && s !=NULL)
	    { pos++; x += Width;}
	   break;
	   case LEFTKEY:
	   if (pos > 0 && s!=NULL)
	   {  pos--; x -= Width;}
	   break;
	   case UPKEY:
	     if(LINE!=0)
	     {
	       y=y-Height;
	       strcpy(Edt->Edit_Array[LINE],s);
	       LINE--;
	       strcpy(s,Edt->Edit_Array[LINE]);
	       len=strlen(s);
	       Edt->LINE=LINE;
		if(len<pos)
		 {pos=len; x=pos*Width;}
	     }
	   break;
	   case DOWNKEY:
	      if(LINE<Edt->ENDLINE)
	      {
		y+=Height;
		strcpy(Edt->Edit_Array[LINE],s);
		LINE++;
		strcpy(s,Edt->Edit_Array[LINE]);
		Edt->LINE=LINE;
		len=strlen(s);
		if(len<pos)
		  {pos=len;x=pos*Width;}
	      }
	   break;
	   case ENDKEY:
	     if(pos<len+1)
	     {
	      pos=strlen(s);
	      x=pos*Width;}
	   break;
	   case HOMEKEY:
	   if(pos<len+1)
	   {  pos=0;
	      x=0;}
	   break;
	   case DELKEY:
	   if(Edt->ENDLINE>=0 && LINE<=Edt->ENDLINE || (LINE>0 && pos>0))
	   {
	      if(pos < len)
	      {
		movmem(&s[pos + 1], &s[pos], len - pos);
		len--;
		settextstyle(textStyle,HORIZ_DIR,textSize);
		clearEdt(Edt,0,y,(len+1)*Width,Height);
		outtextxy(0,y,s);
		Edt->LINE=LINE;
		strcpy(Edt->Edit_Array[LINE],s);
	      }
	      else
	      if(pos==len && LINE<Edt->ENDLINE)
	      {
		strcpy(Edt->Edit_Array[LINE],s);
		strcat(s,Edt->Edit_Array[LINE+1]);
		len=strlen(s);
		settextstyle(textStyle,HORIZ_DIR,textSize);
		if(len>75)
		{
		 strcpy(legal,NULL);
		 movmem(&s[0], legal,EDITLEN-1);
		 clearEdt(Edt,0,y,(73+1)*Width,Height);
		 legal[EDITLEN-1]='\0';
		 outtextxy(0,y,legal);
		 strcpy(Edt->Edit_Array[LINE],legal);
		 Edt->LINE=LINE;
		 len=strlen(legal);

		 Tlen=strlen(s);
		 strcpy(legal,NULL);
		 movmem(&s[EDITLEN-1], legal,(Tlen-EDITLEN-3));
		 legal[(Tlen-EDITLEN-3)]='\0';
		 clearEdt(Edt,0,y+Height,(73+1)*Width,Height);
		 outtextxy(0,y+Height,legal);
		 strcpy(Edt->Edit_Array[LINE+1],legal);
		}
		else
		{
		  clearEdt(Edt,0,y,(len+1)*Width,Height);
		  clearEdt(Edt,0,y+Height,(len+1)*Width,Height);
		  outtextxy(0,y,s);
		  strcpy(Edt->Edit_Array[LINE],s);
		  Edt->LINE=LINE;
		  if(LINE!=Edt->ENDLINE)
		  {
		   Edt= Step_Up(Edt,LINE+1,y);Edt->ENDLINE--;
		  }
	       }
	      }
	   }
	   break;
	   case ENTER_KEY:
	    if(Edt->ENDLINE==LINE && Edt->ENDLINE < Edt->y1/Height)
	    {
	      strcpy(Edt->Edit_Array[LINE],s);
	      Edt->TRWord[LINE].textColor = textColor;
	      Edt->TRWord[LINE].textStyle = textStyle;
	      Edt->TRWord[LINE].textSize  = textSize;
	      Edt->TRWord[LINE].textHeight = textheight(s)+2;
	      Edt->TRWord[LINE].textWidth  = textwidth("W");
	      LINE++;
	      Edt->TRWord[LINE].textColor = textColor;
	      Edt->TRWord[LINE].textStyle = textStyle;
	      Edt->TRWord[LINE].textSize  = textSize;
	      Edt->TRWord[LINE].textHeight = textheight("A")+2;
	      Edt->TRWord[LINE].textWidth  = textwidth("A");
	      y=y+Edt->TRWord[LINE].textHeight;
	      x=0;
	      pos=0;
	      len=0;
	      strcpy(s,NULL);
	      Edt->ROW_Flag[LINE]=TRUE;
	      Edt->ENDLINE++;
	      Edt->LINE=LINE;
	      strcpy(Edt->Edit_Array[LINE],NULL);
	    }else
	      if(LINE<=Edt->ENDLINE && pos<strlen(Edt->Edit_Array[LINE])+1 && Edt->ENDLINE<35)//Edt->ROW_Flag[LINE]==TRUE)
	      {
		strcpy(s,Edt->Edit_Array[LINE]);
		strcpy(ptr,Edt->Edit_Array[LINE]);
		movmem(&s[0],s, len - pos+1);
		s[pos]='\0';
		len=strlen(Edt->Edit_Array[LINE]);
		strcpy(Edt->Edit_Array[LINE],s);
		settextstyle(textStyle,HORIZ_DIR,textSize);
		clearEdt(Edt,0,y,(len+1)*Width,Height);
		outtextxy(0,y,s);

		if(LINE<=Edt->ENDLINE)
		  {  Edt->ENDLINE++;
		     Edt->ROW_Flag[LINE]=TRUE;
		     Edt=Step_Down(Edt,LINE,y,Edt->ENDLINE);
		  }

		strcpy(s,ptr);
		movmem(&s[pos], s, len - pos + 1);
		y+=Height;
		len=strlen(Edt->Edit_Array[LINE]);
		LINE++;
		strcpy(Edt->Edit_Array[LINE],s);
		clearEdt(Edt,0,y,(len+1)*Width,Height);
		settextstyle(textStyle,HORIZ_DIR,textSize);
		outtextxy(0,y,s);
		len=strlen(s);
		x=0;
		Edt->LINE=LINE;
		pos=0;
	      }
	   break;
	   case BACK_SPACE:
	   if(LINE>=0 || pos >0)
	   {
	      if (pos > 0)
	      {
		 movmem(&s[pos], &s[pos - 1], len - pos + 1);
		 pos--;
		 len--;
		 settextstyle(textStyle,HORIZ_DIR,textSize);
		 clearEdt(Edt,0,y,(len+1)*Width,Height);
		 outtextxy(0,y,s);
		 Edt->LINE=LINE;
		 strcpy(Edt->Edit_Array[LINE],s);
		 x-=Width;
	      }
	      else
	      if(LINE!=0)
	      {
	       y=y-Height;
	       strcpy(Edt->Edit_Array[LINE],s);
	       LINE--;
	       strcat(Edt->Edit_Array[LINE],s);
	       strcpy(s,Edt->Edit_Array[LINE]);
	       len=strlen(s);
	       pos=strlen(Edt->Edit_Array[LINE+1]);
	       pos=len-pos;
	       x=pos*Width;
	       settextstyle(textStyle,HORIZ_DIR,textSize);
	       clearEdt(Edt,0,y,len*Width,Height);
	       outtextxy(0,y,s);
	       strcpy(Edt->Edit_Array[LINE],s);
	       Edt->LINE=LINE;
		if(LINE!=Edt->ENDLINE)
		  { Edt= Step_Up(Edt,LINE+1,y);
		   Edt->ENDLINE--;}
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
	      str[0] = ch;
	      str[1] = '\0';
	      s[len] = '\0';
	     settextstyle(textStyle,HORIZ_DIR,textSize);
	     Edt->TRWord[LINE].textHeight = textheight(str);
	     Edt->TRWord[LINE].textWidth  = textwidth("W");
	     clearEdt(Edt,0,y,strlen(s)*Width,Height);
	     setcolor(textColor);
	     outtextxy(0,y,s);
	     x=x+textwidth(str);
	     strcpy(Edt->Edit_Array[LINE],s);
	 }
	 else
	   if(Edt->ENDLINE==LINE && Edt->ENDLINE < 20  && (len>=maxlength))
	    {
	      strcpy(Edt->Edit_Array[LINE],s);
	      LINE++;
	      y=y+Height;
	      x=0;
	      pos=0;
	      len=0;
	      strcpy(s,NULL);
	      Edt->ENDLINE++;
	      Edt->LINE=LINE;
	      strcpy(Edt->Edit_Array[LINE],NULL);
	    }
	break;
	}
	if(x>Edt->x1-Edt->x)
	  x=(Edt->x1-Edt->x);
	Xorbar(x,y,x+1,(y+Height-1),WHITE);
     }
   s[len] = 0;
  }while(ch != ESC);
   EX:
   Edt->ROW_Flag[Edt->ENDLINE]=FALSE;
   Edt->CPos=pos;
   setviewport(Edt->x,Edt->y,Edt->x1,Edt->y1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   settextstyle(textinfo.font,HORIZ_DIR,textinfo.charsize);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}

EDITOR *Step_Up(EDITOR *Edt,int LINE,int pos)
{
    int i=LINE;
    int len,tlen=0;
    setviewport(Edt->x,Edt->y,Edt->x1,Edt->y1,CLIP_ON);
    while(i<Edt->ENDLINE)
    {
       pos=pos+Height;
       strcpy(Edt->Edit_Array[i],Edt->Edit_Array[i+1]);
       len=strlen(Edt->Edit_Array[i]);
	if(len<tlen)
	 clearEdt((EDITOR*)&Edt,0,pos,(tlen+1)*Width,Height);
	 else {clearEdt((EDITOR*)&Edt,0,pos,(len+1)*Width,Height);tlen=len+1;}
       outtextxy(0,pos,Edt->Edit_Array[i]);
       Edt->ROW_Flag[i]=TRUE;
       i++;
    }
   len=strlen(Edt->Edit_Array[i+1]);
   pos=pos+10;
	if(len<tlen)
	 clearEdt((EDITOR*)&Edt,0,pos,(tlen+1)*Width,Height);
	 else {clearEdt((EDITOR*)&Edt,0,pos,(len+1)*Width,Height);tlen=len+1;}
   Edt->ROW_Flag[i-1]=FALSE;
return Edt;
}

EDITOR *Step_Down(EDITOR *Edt,int LINE,int pos,int step)
{
    int i=step;
    setviewport(Edt->x,Edt->y,Edt->x1,Edt->y1,CLIP_ON);
    pos=pos+Height;
    clearEdt(Edt,0,pos,Width,Height);
    while(i!=(LINE+1))
    {
       strcpy((char*)Edt->Edit_Array[i],Edt->Edit_Array[i-1]);
       Edt->ROW_Flag[i]=TRUE;
       i--;
    }
    Edt->ROW_Flag[step+1]=FALSE;
    i++;
    while(i<Edt->ENDLINE+1)
    {
       pos=pos+10;
       clearEdt(Edt,0,pos,598,Height);
       outtextxy(0,pos,Edt->Edit_Array[i]);
       i++;
    }
 Edt->ROW_Flag[i-1]=FALSE;
 return Edt;
}

void clearEdt(EDITOR *t1,int x,int y,int width,int height)
{
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(t1->x,t1->y,t1->x1,t1->y1,CLIP_ON);
   setfillstyle(SOLID_FILL,textBKColor);
   setcolor(textBKColor);
   if((width/Width) > t1->x1-t1->x)
    bar(x,y,(t1->x1-t1->x),y+height-2);
    else
    bar(x,y,width,y+height-2);
   setcolor(textColor);
   setviewport(t1->x,t1->y,t1->x1,t1->y1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
}

