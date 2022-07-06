  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 			  Login Screen
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <graphics.h>

#include "DgnTool.h"
#include "mouse.h"

#define  REQCOUNT   10

struct Admin{
    char UserName[20];
    char UPassword[20];
    char CPassword[20];
    char FirstName[20];
    char LastName[20];
    char DOB[20];
}Adm,Admread[10];

void NewUserFileRead(void);
void NewUserFileWrite(void);
  int PIndex;
  int OIndex;
  int PCount;
  char str[5];
  int Sx,Sy=72,SPy=74;
  BOOL Bool=FALSE;
  BOOL TFlag=FALSE;
BOOL Login(int x,int y)
{
  BOOL Bool;
  FRAME f1;
  TEXTBOX Text1,Text2;
  BUTTON  But1,But2,But3;
  int Indx=-1,BF1,i,ch;

  NewUserFileRead();

  hideMouse();
  f1=Frame_Window(x,y,x+280,y+120,"Login");

  Label(5,30,"Username:");
  Label(5,60,"Password:");

  Text1=TextBox(105,30,"",165);
  Text2=TextBox(105,60,"",165);

  But1=Button(70,90,130,110,"Newuser");
  But2=Button(140,90,200,110,"Cancel");
  But3=Button(210,90,270,110,"Login");
  Bool=FALSE;
  showMouse();
  while(getToggle()==TRUE)
  {
      if(kbhit())
	 ch = getch();
	 if(getToggle()==TRUE && (ch ==TAB_KEY || ch == ESC_KEY))
	 {
	   Indx++; ch=0;
	   if(Indx>=5) Indx=0;
	   if(Text1.tabIndex==Indx) {
	       Text1.Bool=FALSE;
	       ActionText(&Text1);
	    }
	    else
	    if(Text2.tabIndex==Indx)  {
	       Text2.Bool=FALSE;
	       Text2=ActionPWText(Text2);
	    }
	    else
	    if(But1.tabIndex==Indx)
	    {
	      But1.Bool=ShowFocus(f1,But1.fx+2,But1.fy+5,55);
	      BF1=Button_Action(But1);
	      if(BF1==TRUE)
	       {
		    if(strcmp(Admread[0].UserName,Text1.getText)==0 &&
		      strcmp(Admread[0].UPassword,Text2.getText)==0)
		     { Focus.Bool=FALSE;
		       NewUser(160,100);
		       Tab_Toggle=TRUE;
		     }else
		  MsgBox("Invalied Login Name",0);
		  ShowFocus(f1,But1.fx+2,But1.fy+5,55);
		  Focus.Bool=FALSE;
	       }
	    }
	   else
	   if(But2.tabIndex==Indx) {
	    But2.Bool=ShowFocus(f1,But2.fx+2,But2.fy+5,55);
	    BF1=Button_Action(But2);
	    if(BF1==TRUE)
		Tab_Toggle = FALSE;
	   }
	   else
	   if(But3.tabIndex==Indx)
	   {
	    But3.Bool=ShowFocus(f1,But3.fx+2,But3.fy+5,55);
	    BF1=Button_Action(But3);
	      if(BF1==TRUE)
	      {
		for(i=0;i<10;i++)
		  if(strcmp(Admread[i].UserName,Text1.getText)==0 &&
		      strcmp(Admread[i].UPassword,Text2.getText)==0)
		    { Bool=TRUE;
		      Tab_Toggle = FALSE; }
		if(Tab_Toggle != FALSE)
		     MsgBox("Invalied Login Name",0);
		ShowFocus(f1,But3.fx+2,But3.fy+5,55);
		Focus.Bool=FALSE;
	      }
	    }
      }
	 else
       if(getToggle()==FALSE)
	   Tab_Toggle = FALSE;

    if(TextBox_Click(&Text1)) {
       Text1.Bool=FALSE;
       ActionText(&Text1);
    }else
    if(TextBox_Click(&Text2)) {
       Text2.Bool=FALSE;
       Text2=ActionPWText(Text2);
    }else
    if(ButtonPress(&But1)) {
	if(strcmp(Admread[0].UserName,Text1.getText)==0 &&
	  strcmp(Admread[0].UPassword,Text2.getText)==0)
	{ Focus.Bool=FALSE; NewUser(160,100); Tab_Toggle=TRUE;
	}else
	  MsgBox("Invalied Login Name",0);
    }else
    if(ButtonPress(&But2)) {
       Tab_Toggle = FALSE;
    }else
    if(ButtonPress(&But3)) {
	for(i=0;i<10;i++)
	  if(strcmp(Admread[i].UserName,Text1.getText)==0 &&
	   strcmp(Admread[i].UPassword,Text2.getText)==0)
	  { Bool=TRUE;
	    Tab_Toggle = FALSE; }
	if(Tab_Toggle != FALSE)
	 MsgBox("Invalied Login Name",0);
    }else
   if(CloseWindow(&f1)) {
     Tab_Toggle=FALSE;
   }
   else
   if(WinClose(&f1))
      Close_Hlight(&f1);
  }
  Focus.Bool=FALSE;
  CLOSE_FRAME(&f1);
  return Bool;
}

void NewUser(int x,int y)
{
  BOOL Bool;
  FRAME f1;
  TEXTBOX Text1,Text2,Text3,Text4,Text5,Text6;
  BUTTON  But1,But2;
  int Indx=-1,BF1,i;
  BOOL Thread = TRUE;
  struct Admin A1;
  char ch;
  struct viewporttype viewinfo;
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  hideMouse();
  f1=Frame_Window(x,y,x+278,y+243,"New User");
  Label(5,30,"Username:");
  Label(5,60,"Password:");
  Label(5,90,"CPassword:");
  Label(5,120,"First Name:");
  Label(5,150,"Last Name:");
  Label(5,180,"DOB:");

  Text1=TextBox(105,30,"",165);
  Text2=TextBox(105,60,"",165);
  Text3=TextBox(105,90,"",165);
  Text4=TextBox(105,120,"",165);
  Text5=TextBox(105,150,"",165);
  Text6=TextBox(105,180,"",165);
  CrossLine(6,210,265);

  But1=Button(140,216,200,236,"Ok");
  But2=Button(210,216,270,236,"Cancel");
  showMouse();
  while(Thread)
  {
       if(kbhit())
	 ch = getch();
	 if(getToggle()==TRUE && (ch ==TAB_KEY || ch == ESC_KEY))
	 {
	   Indx++; ch=0;
	   if(Indx>=8) Indx=0;
	  if(Text1.tabIndex==Indx) {
	     Text1.Bool=FALSE;
	     ActionText(&Text1);
	   }
	    else
	    if(Text2.tabIndex==Indx) {
	      Text2.Bool=FALSE;
	      Text2=ActionPWText(Text2);
	    }
	  else
	  if(Text3.tabIndex==Indx) {
	      Text3.Bool=FALSE;
	      Text3=ActionPWText(Text3);
	   }
	  else
	  if(Text4.tabIndex==Indx) {
	      Text4.Bool=FALSE;
	      ActionText(&Text4);
	   }
	  else
	  if(Text5.tabIndex==Indx) {
	      Text5.Bool=FALSE;
	      ActionText(&Text5);
	   }
	  else
	  if(Text6.tabIndex==Indx) {
	      Text6.Bool=FALSE;
	      ActionText(&Text6);
	   }
	   else
	    if(But1.tabIndex==Indx)
	    {
	      But1.Bool=ShowFocus(f1,But1.fx+2,But1.fy+5,55);
	      BF1=Button_Action(But1);
	      if(BF1==TRUE)
	      {
		strcpy(Adm.UserName,Text1.getText);
		strcpy(Adm.UPassword,Text2.getText);
		strcpy(Adm.CPassword,Text3.getText);
		for(i=0;i<10;i++)
		  if(strcmp(Admread[i].UserName,Adm.UserName)==0)
		    {  MsgBox("UserName already Exists",0);
		       goto sk;
		    }
		  if(strcmp(Adm.UPassword,Adm.CPassword)==0 &&
		   strcmp(Adm.UserName,"")!=0)
		  {
		    strcpy(Adm.FirstName,Text4.getText);
		    strcpy(Adm.LastName,Text5.getText);
		    strcpy(Adm.DOB,Text6.getText);
		    NewUserFileWrite();
		    NewUserFileRead();
		    Thread = FALSE;
		  }
		  else
		    MsgBox("Retype the Password",0);
		 sk:
		 Focus.Bool=FALSE;
		 ShowFocus(f1,But1.fx+2,But1.fy+5,55);
	      }
	    }
	   else
	   if(But2.tabIndex==Indx)
	   {
	    But2.Bool=ShowFocus(f1,But2.fx+2,But2.fy+5,55);
	    BF1=Button_Action(But2);
	    if(BF1==TRUE)
	      { Thread = FALSE;}
	   }
	}
	else
       if(getToggle()==FALSE)
	 Thread = FALSE;
    if(TextBox_Click(&Text1)) {
	Text1.Bool=FALSE;
	ActionText(&Text1);
    }else
    if(TextBox_Click(&Text2)) {
	Text2.Bool=FALSE;
	Text2=ActionPWText(Text2);
    }else
    if(TextBox_Click(&Text3)) {
	Text3.Bool=FALSE;
	Text3=ActionPWText(Text3);
    }else
    if(TextBox_Click(&Text4)) {
	Text4.Bool=FALSE;
	ActionText(&Text4);
    }else
    if(TextBox_Click(&Text5)) {
	Text5.Bool=FALSE;
	ActionText(&Text5);
    }else
    if(TextBox_Click(&Text6)) {
	Text6.Bool=FALSE;
	ActionText(&Text6);
    }else
   if(ButtonPress(&But1)) {
	 strcpy(Adm.UserName,Text1.getText);
	 strcpy(Adm.UPassword,Text2.getText);
	 strcpy(Adm.CPassword,Text3.getText);
	 for(i=0;i<10;i++)
	  if(strcmp(Admread[i].UserName,Adm.UserName)==0) {
	       MsgBox("UserName already Exists",0);
	       break;
	   }
	 if(strcmp(Adm.UPassword,Adm.CPassword)==0 &&
	  strcmp(Adm.UserName,"")!=0)
	 {
	     strcpy(Adm.FirstName,Text4.getText);
	     strcpy(Adm.LastName,Text5.getText);
	     strcpy(Adm.DOB,Text6.getText);
	     NewUserFileWrite();
	     NewUserFileRead();
	     Thread = FALSE;
	 }
	 else
	 MsgBox("Retype the Password",0);
   }else
   if(ButtonPress(&But2))
       Thread = FALSE;
   else
   if(CloseWindow(&f1))
     Thread = FALSE;
   else
   if(WinClose(&f1))
      Close_Hlight(&f1);
  }
  Focus.Bool=FALSE;
  CLOSE_FRAME(&f1);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
}

void NewUserFileWrite()
{
  FILE *stream;
  if ((stream = fopen("Admin.dat", "a+b")) == NULL)
  {
    MsgBox("File not Found",0);
    goto xxx;
  }
  fwrite(&Adm, sizeof(Adm), 1, stream);
  fclose(stream);
xxx:
}

void NewUserFileRead()
{
  FILE *stream;
  int i=0;
  if ((stream = fopen("Admin.dat", "a+b")) == NULL)
  {
    MsgBox("File not Found",0);
    goto xxx;
  }
 do
 {
   if(i<10)
    {  fread(&Adm, sizeof(Adm), 1, stream);
      strcpy(Admread[i].UserName,Adm.UserName);
      strcpy(Admread[i].UPassword,Adm.UPassword);
      strcpy(Admread[i].CPassword,Adm.CPassword);
      strcpy(Admread[i].FirstName,Adm.FirstName);
      strcpy(Admread[i].LastName,Adm.LastName);
      strcpy(Admread[i].DOB,Adm.DOB);}
  i++;
 }while(!feof(stream));
xxx:
fclose(stream);
}

void ProgressBar(int x,int y,char* txt)
{
  BOOL Bool;
  FRAME f1;
  TEXTBOX Text1;
  char str[5];
  int i,Sx=12,Sy=72;
  hideMouse();
  f1=Frame_Window(x,y,x+280,y+120,"Loading...");
  Label(80,30,PROJECT_TITLE);
  outtextxy(5,100,txt);
  Text1=TextBox(10,70,"",260);
  settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
  outtextxy(157,75,"%");
  while(!kbhit())
  {
     Xorbar(Sx,Sy,Sx+1,(Sy+16),YELLOW);
     itoa(Sx/2.7,str,10);
     if((Sx/2.7)<45)
       setcolor(BLUE);
     else
       setcolor(WHITE);
     outtextxy(128,75,str);
     outtextxy(157,75,"%");
     delay(40);
     if((Sx/2.7)<45)
       setcolor(WHITE);
     else
       setcolor(BLUE);
     outtextxy(128,75,str);
     outtextxy(157,75,"%");
     Sx=Sx+2;
     if(Sx>=266)
       break;
  }
  setcolor(WHITE);
  itoa(100,str,10);
  outtextxy(128,75,str);
  outtextxy(157,75,"%");
  CLOSE_FRAME(&f1);
  showMouse();
}

void Port_Progress_Bar(FRAME *f1,int x,int y,char* txt)
{
  TEXTBOX Text1;
  PIndex=12;
  hideMouse();
  Bool=FALSE;
  *f1=Frame_Window(x,y,x+280,y+120,"Loading...");
  Label(80,30,PROJECT_TITLE);
  outtextxy(5,100,txt);
  Text1=TextBox(10,70,"",260);
}

BOOL setProgress()
{
  settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
  if(PIndex<=245)
  {
     Sx=PIndex;
     Xorbar(Sx,Sy,Sx+1,(Sy+16),YELLOW);
     itoa(Sx/2.7,str,10);
     if((Sx/2.7)<45)
       setcolor(BLUE);
     else
       setcolor(WHITE);
     outtextxy(128,75,str);
     outtextxy(157,75,"%");
     delay(40);
     if((Sx/2.7)<45)
       setcolor(WHITE);
     else
       setcolor(BLUE);
     outtextxy(128,75,str);
     outtextxy(157,75,"%");
     PIndex=PIndex+2;
   }
   else
 { setcolor(WHITE);
   itoa(90,str,10);
   outtextxy(128,75,str);
   outtextxy(157,75,"%");
   Bool = TRUE;
   }
  return Bool;
}

void hideProgress(FRAME *f1)
{ CLOSE_FRAME(f1);showMouse();}

// Request Progress Bar

void Port_Req_Progress_Bar(FRAME *f1,int x,int y,char* txt)
{
  TEXTBOX Text1;
  PCount=0;
  PIndex=OIndex=12;
  hideMouse();
  TFlag=FALSE;
  *f1=Frame_Window(x,y,x+280,y+120,"Searching Text...");
  Label(80,30,PROJECT_TITLE);
  outtextxy(5,100,txt);
  Text1=TextBox(10,70,"",260);
  settextstyle(TEXTBOX_FONT,HORIZ_DIR,TEXTBOX_FONT_SIZE);
}

void Req_setProgress()
{
 if(PCount >= 1024)
 {   PCount=0;
  if(PIndex<=230)
  {
     Sx=PIndex;
     if(TFlag == FALSE) {
       Xorbar(Sx,SPy,Sx+45,(Sy+15),YELLOW);
       Xorbar(Sx+14,SPy,Sx+16,(Sy+15),YELLOW);
       Xorbar(Sx+29,SPy,Sx+31,(Sy+15),YELLOW);
       OIndex=Sx;
       TFlag=TRUE;
      }else {
       Sx=OIndex;
       Xorbar(Sx,SPy,Sx+45,(Sy+15),YELLOW);
       Xorbar(Sx+14,SPy,Sx+16,(Sy+15),YELLOW);
       Xorbar(Sx+29,SPy,Sx+31,(Sy+15),YELLOW);
       TFlag=FALSE;
     }
       PIndex=PIndex+20;
   }
   else
     PIndex=12;
 }else PCount++;
}

void hide_Req_Progress(FRAME *f1)
{ CLOSE_FRAME(f1);showMouse();}
