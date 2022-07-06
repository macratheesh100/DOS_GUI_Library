  /*****************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/

#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>

#include "Wiredefs.h"
#include "mouse.h"
#include "DgnTool.h"
#include "Paint.h"

#define   COLOR_BUT   1

 PBUTTON C_But[17];
 PBUTTON CF_But,CB_But;

// Font Size

THEME Text_Font(int x,int y)
{
  FRAME f1;
  THEME TFont;
  LISTBOX List1,List2;
  BUTTON  But1,But2;
  int Indx=-1,BF1,i,ch;
  f1=Frame_Window(x,y,x+220,y+210,"Fonts");

  List1 = ListBox(4,25,95,200,"Size");
  List2 = ListBox(100,25,150,200,"Fonts");

  But1 = Button(155,155,215,175,"Ok");
  But2 = Button(155,180,215,200,"Cancel");

  List1= addList(List1,"Default _F");
  List1= addList(List1,"Sans Serif");
  List1= addList(List1,"Small _Font");
  List1= addList(List1,"Triplex _F");

  for(i=1;i<=10;i++)
  {
    itoa(i,s,10);
    List2= addList(List2,s);
  }
  showMouse();
  TFont.textFont = 1;
  TFont.textSize = 1;
  while(getToggle()==TRUE)
  {
      if(kbhit())
	 ch = getch();
	 if(getToggle()==TRUE && (ch ==TAB_KEY || ch == ESC_KEY))
	 {
	  Indx++; ch=0;
	   if(Indx>=5) Indx=0;
	    if(List1.tabIndex==Indx)
	    {
	       List1.Bool=ShowFocus(f1,List1.fx,List1.fy,45);
		  while(List1.Bool!=TRUE)
		  {
		   if(kbhit())
		   {
		    List1 = ActionList(List1);
		    if(strcmp(List1.getText,NULL)!=0)
			TFont.textFont = List1.listValue;
		    }
		   }
	    }
	    else
	    if(List2.tabIndex==Indx)
	    {
	      List2.Bool=ShowFocus(f1,List2.fx,List2.fy,45);
		  while(List2.Bool!=TRUE)
		  {
		   if(kbhit())
		   {
		    List2 = ActionList(List2);
		    if(strcmp(List2.getText,NULL)!=0)
		       TFont.textSize = atoi((char*)List2.getText);
		    }
		   }
	    }
	    else
	    if(But1.tabIndex==Indx)
	    {
	      But1.Bool=ShowFocus(f1,But1.fx+2,But1.fy+5,55);
	      BF1=Button_Action(But1);
	      if(BF1==TRUE) {
		Focus.Bool=FALSE;
		CLOSE_FRAME(&f1);
		return TFont;}
	    }
	   else
	   if(But2.tabIndex==Indx)
	   {
	    But2.Bool=ShowFocus(f1,But2.fx+2,But2.fy+5,55);
	    BF1=Button_Action(But2);
	    if(BF1==TRUE) {
		 TFont.textSize = 1;
		 TFont.textFont = 1;
		 Focus.Bool=FALSE;
		 CLOSE_FRAME(&f1);
		return TFont;}
	   }
	}
	if(ListBox_Click(&List1)) {
	    List1.Bool=ShowFocus(f1,List1.fx,List1.fy,45);
	    List1 = ActionList(List1);
	    if(strcmp(List1.getText,NULL)!=0)
		 TFont.textFont = List1.listValue;
	}
	else
	if(ListBox_Click(&List2)) {
	    List2.Bool=ShowFocus(f1,List2.fx,List2.fy,45);
	    List2 = ActionList(List2);
	     if(strcmp(List2.getText,NULL)!=0)
		 TFont.textSize = atoi((char*)List2.getText);
	}
	else
	 if(ButtonPress(&But1)) {
		Focus.Bool=FALSE;
		CLOSE_FRAME(&f1);
		return TFont;
	 }
	 else
	 if(ButtonChk(&But1))
	   ButtonHlight(&But1);
	 else
	 if(ButtonPress(&But2)) {
		 TFont.textSize = 1;
		 TFont.textFont = 1;
		 Focus.Bool=FALSE;
		 CLOSE_FRAME(&f1);
		return TFont;
	 }
	 else
	 if(ButtonChk(&But2))
	   ButtonHlight(&But2);
	 else
	 if(CloseWindow(&f1)) {
	     CLOSE_FRAME(&f1);
	     TFont.textSize = 1;
	     TFont.textFont = 1;
	     return TFont;
	 }
	 else
	 if(WinClose(&f1))
	    Close_Hlight(&f1);

       if(getToggle() == FALSE) {
	  Focus.Bool=FALSE;
	  CLOSE_FRAME(&f1);
	 return TFont; }
  }
  return TFont;
}

// Text color

THEME Text_Color(int x,int y)
{
  FRAME f1;
  THEME TColor;
  BUTTON  But1,But2;
  int Indx=-1,BF1,i,ch;
  int Color= BLACK;
  int j,ind= 0;
  int OLD_COLOR = BLACK;
  int BKColor = WHITE;
  int B_COLOR = WHITE;
  f1=Frame_Window(x,y,x+120,y+210,"Color");

  hideMouse();
  CrossLine(4,26,75);
   for(j=32;j<80;j=j+15)
     for(i=10;i<63;i=i+15) {
	C_But[ind] = _PButton(&f1,i,j,i+13,j+13,COLOR_BUT,ind);
	ind++;
       }
   But1 = Button(55,155,115,175,"Ok");
   But2 = Button(55,180,115,200,"Cancel");

   CB_But = _PButton(&f1,30,110,60,130,2,15);
   CF_But = _PButton(&f1,10,100,40,120,2,0);
   CrossLine(4,140,75);

  showMouse();
  while(getToggle()==TRUE)
  {
	if(kbhit()) {
	  Indx++;
	   if(Indx>=18)
	   Indx=0;
	 for(i=0;i<16;i++) {
	    if(C_But[i].tabIndex==Indx) {
	      C_But[i].Bool=ShowFocus(f1,C_But[i].x+1,C_But[i].y+1,11);
	      BF1=CButton_Action(&C_But[i]);
	      if(BF1==TRUE) {
		Color  = C_But[i].Color;
		_setButtonColor(CF_But,Color);
		break; }
	       }
	    }
	    if(But1.tabIndex==Indx)
	    {
	      But1.Bool=ShowFocus(f1,But1.fx+2,But1.fy+5,55);
	      BF1=Button_Action(But1);
	      if(BF1==TRUE) {
		Focus.Bool=FALSE;
		TColor.FColor = Color;
		TColor.BKColor = BKColor;
		CLOSE_FRAME(&f1);
		return TColor;}
	    }
	   else
	   if(But2.tabIndex==Indx)
	   {
	    But2.Bool=ShowFocus(f1,But2.fx+2,But2.fy+5,55);
	    BF1=Button_Action(But2);
	    if(BF1==TRUE) {
		 Color = 0;
		 Focus.Bool=FALSE;
		 CLOSE_FRAME(&f1);
		return TColor; }
	   }
	}
	Mouse=mouseStatus();
  if(Mouse.x>=f1.x && Mouse.x<=f1.x1 && Mouse.y>=f1.y && Mouse.y<=f1.y1-100){
      if(getMBPressStatus()==1 ) {
       for(i=0;i<16;i++)
	if(Button_Click(&C_But[i])) {
	       Color=C_But[i].Color;
	     if(Color!=OLD_COLOR)
	     {
	       _setButtonColor(CF_But,Color);
	       OLD_COLOR=Color;
	       setcolor(Color);
	       break;}
	  }
      }else
      if(getMBPressStatus()==2 ) {
       for(i=0;i<16;i++)
	  if(Button_Click(&C_But[i])) {
	       BKColor = C_But[i].Color;
	     if(BKColor!=B_COLOR){
	       _setButtonColor(CB_But,BKColor);
	       _setButtonColor(CF_But,Color);
	       B_COLOR=BKColor;
	       break;}
	}
       }}
	 if(ButtonPress(&But1)) {
		Focus.Bool=FALSE;
		TColor.FColor = Color;
		TColor.BKColor = BKColor;
		CLOSE_FRAME(&f1);
		return TColor;
	 }
	 else
	 if(ButtonChk(&But1))
	   ButtonHlight(&But1);
	 else
	 if(ButtonPress(&But2)) {
		Color = 0;
		Focus.Bool=FALSE;
		CLOSE_FRAME(&f1);
		return TColor;
	 }
	 else
	 if(ButtonChk(&But2))
	   ButtonHlight(&But2);
	 else
	 if(CloseWindow(&f1)) {
		 Color = 0;
		 Focus.Bool=FALSE;
		 CLOSE_FRAME(&f1);
		return TColor;
	 }
	 else
	 if(WinClose(&f1))
	    Close_Hlight(&f1);

       if(getToggle() == FALSE) {
	  Focus.Bool=FALSE;
	  CLOSE_FRAME(&f1);
	 return TColor; }
  }
  return TColor;
}
