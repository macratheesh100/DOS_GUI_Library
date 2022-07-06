  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/

#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

#include "Wiredefs.h"
#include "mouse.h"
#include "DgnTool.h"
#include "Paint.h"

void _setButtonColor(PBUTTON B1,COLOR Color)
{
  hideMouse();
   Hlight_Frame(B1.x,B1.y,B1.x1,B1.y1);
   setfillstyle(SOLID_FILL,Color);
   bar(B1.x+2,B1.y+2,B1.x1-2,B1.y1-2);
  showMouse();
}

PBUTTON _PButton(FRAME *f1,int x,int y,int x1,int y1,int Attrib,int Color)
{
  PBUTTON B1;
   hideMouse();
    B1.fx=f1->x;
    B1.fy=f1->y;
    B1.fx1=f1->x1;
    B1.fy1=f1->y1;
    B1.x=x; B1.y=y; B1.x1=x1;B1.y1=y1;
    B1.tabIndex=Index;
    B1.Color=Color;
    Index++;
  if(Attrib==0) {
    Hlight_Frame(x,y,x1,y1);
  }else
  if(Attrib==1) {
    Internal_Menu_Frame(x,y,x1,y1);
    setfillstyle(SOLID_FILL,Color);
    bar(x+1,y+1,x1-1,y1-1);
  }else
  if(Attrib==2) {
    Hlight_Frame(x,y,x1,y1);
    setfillstyle(SOLID_FILL,Color);
    bar(x+2,y+2,x1-2,y1-2);
  }
  showMouse();
  return B1;
}

BOOL CButton_Action(PBUTTON *But1)
{
  BOOL bool=FALSE;
  char ch=0;
  int Cx,Cy;
  struct viewporttype viewinfo;
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(But1->x,But1->y,But1->x1,But1->y1,CLIP_ON);
  But1->Bool=TRUE;
   while(TRUE)
   {
      Mouse=mouseStatus();
      PollMouseStatus(&Cx,&Cy);
       if(Cx < Mouse.x || Cx > Mouse.x || Cy < Mouse.y || Cy > Mouse.y || Mouse.Button==1)
	{But1->Bool=TRUE;  break;}
      if(kbhit())
      {
	 ch=getch();
	 if(ch==ENTER_KEY)
	  { if(But1->Bool==TRUE)
	      {
		bool=TRUE;
		break;}
	  }
	  else
	 if(ch==ESC_KEY)
	  {But1->Bool=TRUE;Tab_Toggle=FALSE; break;}
	  else
	 if(ch==TAB_KEY || ch==LEFT_KEY || ch==RIGHT_KEY)
	 {But1->Bool=TRUE;  break;}
      }
  }
 setviewport(But1->x,But1->y,But1->x1,But1->y1,CLIP_OFF);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
 return bool;
}

