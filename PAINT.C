  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  // 		         Paint
#include       <io.h>
#include    <conio.h>
#include      <mem.h>
#include   <string.h>
#include    <alloc.h>
#include    <stdio.h>
#include <graphics.h>
#include     <math.h>
#include     <dos.h>

#include  "WireDefs.h"
#include  "DgnTool.h"
#include    "mouse.h"
#include    "Paint.h"
#include   "Editor.h"

#define  COLOR_BUT   1
#define  FORE_COLOR  BLACK
#define  BK_COLOR    WHITE

  typedef struct{
    int Width;
    int Height;
    int x;
    int y;
    void far*P_Buffer;
 }COPY_PASTE;

 PBUTTON But[9];
 PBUTTON CBut[17];
 PBUTTON CFBut,CBBut;
 COPY_PASTE Copy_Image[2];
 BOOL EDITFlag = FALSE;
 BOOL EDITCut =FALSE;

 BOOL CheckToolBar(TR_PAINT t1);
 void setButtonColor(PBUTTON B1,COLORS Color);
 void XOR_draw(int x,int y,int x1,int y1,int Attrib);
 void Flood_Fill(int x,int y,COLORS C);
 void Draw_Mouse_Cur(void);
 void freeMem(COPY_PASTE *COPY);

 BOOL P_Copy(COPY_PASTE *Copy,int x,int y,int x1,int y1);
 void P_Paste(COPY_PASTE*,int x,int y);
 void Close_Paint_Hlight(TR_PAINT *t);
 void Free(int i);

 int But_Index=-1;
 int Px,Py,Px1,Py1;
 size_t Buff_Size;
 COLORS FCOLOR = FORE_COLOR;;
 COLORS BKCOLOR = BK_COLOR;;

BOOL TRPaint_Action(TR_PAINT *f1,EDIT *Edit)
{
   int i;
   int CStartx;
   int CStarty;
   int CEndx;
   int CEndy;
   int Old_Index = -1;
   int Cx,Cy,Ex,Ey;
   COLORS OLD_COLOR = 0;
   COLORS B_COLOR =0;
   unsigned int CRadius,CRadiusx,CRadiusy;
   BOOL CVisible=TRUE;
   BOOL MFlag=TRUE;
   BOOL CHFlag=FALSE;
   BOOL MSFlag=FALSE;
   BOOL ret=FALSE;
   BOOL Paste=FALSE;
   BOOL Tog=FALSE;
   int OldInd;
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(f1->fx,f1->fy,f1->x1,f1->y1,CLIP_ON);
   Old_Index = But_Index;
   PButton_Push(But[But_Index]);
   B_COLOR = BKCOLOR;
   setButtonColor(CBBut,BKCOLOR);
   setButtonColor(CFBut,FCOLOR);
   if(Edit->Cut == TRUE || Edit->Paste == TRUE)
   if(EDITFlag == TRUE) {
   if(Edit->Cut==TRUE && EDITCut == TRUE)
   {
      hideMouse();
      P_Paste(&Copy_Image[0],Copy_Image[0].x,Copy_Image[0].y);
      setfillstyle(SOLID_FILL,BKCOLOR);
      bar(Copy_Image[0].x,Copy_Image[0].y,(Copy_Image[0].x+Copy_Image[0].Width),(Copy_Image[0].y+Copy_Image[0].Height));
      showMouse();
      Edit->Cut   = FALSE;
      Edit->Paste = TRUE;
      EDITCut =FALSE;
   }else
   if(Edit->Paste==TRUE) {
      hideMouse();
      P_Copy(&Copy_Image[1],10,10,Copy_Image[0].Width+10,Copy_Image[0].Height+10);
      P_Paste(&Copy_Image[1],10,10);
      P_Paste(&Copy_Image[0],10,10);
      showMouse();
      Paste=Edit->Paste;
      Edit->Paste=FALSE;
      OldInd=But_Index;
      But_Index=20;
    }
 }else {Edit->Cut=FALSE; Edit->Paste=FALSE;MsgBox("Select Area to Cut or Copy",0);}
  if(Edit->Text == TRUE)
     But_Index = Edit->TextIndex;
   while(TRUE)
   {
       if(kbhit())
	  if(getkey()==ESC) {
	    break; }
     mousePressStatus(&Mouse);
     getReleaseStatus(&Mouse);
 if(CheckToolBar(*f1) && getMBPressStatus()==0)
  {   MSFlag=TRUE; if(CVisible==FALSE) showMouse(); }
 if(MSFlag==TRUE)
   if(CheckToolBar(*f1))
     if(getMBPressStatus()==1) {
       for(i=0;i<9;i++)
	  if(Button_Click(&But[i]))  {
	    But_Index=But[i].tabIndex;
	      if(But_Index!=Old_Index){
		PButton_Release(But[Old_Index]);
		PButton_Push(But[i]);
		Old_Index=But_Index;
		Tog=TRUE;
		break;}
	  }
       for(i=0;i<16;i++)
	  if(Button_Click(&CBut[i])) {
	       FCOLOR=CBut[i].Color;
	     if(FCOLOR!=OLD_COLOR){
	       setButtonColor(CFBut,FCOLOR);
	       OLD_COLOR=FCOLOR;
	       setcolor(FCOLOR);
	       break;}
	  }
     }else
     if(getMBPressStatus()==2) {
       for(i=0;i<16;i++)
	  if(Button_Click(&CBut[i])) {
	       BKCOLOR = CBut[i].Color;
	     if(BKCOLOR!=B_COLOR){
	       setButtonColor(CBBut,BKCOLOR);
	       setButtonColor(CFBut,FCOLOR);
	       B_COLOR=BKCOLOR;
	       break;}
	  }
     }
  PollMouseStatus(&Cx,&Cy);
  if(Cx < f1->x || Cy < f1->y-25)
    if(getMBPressStatus() == 1){
      if(getMouse()!=TRUE)
	showMouse();
	break;
      }
  if(Mouse.x>f1->x+80 && Mouse.x<f1->x1 && Mouse.y>f1->y && Mouse.y<f1->y1){
      switch(But_Index) {
	//  ************    Rect Angle    ***********************//
	case 0:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       MFlag=FALSE;
	       CHFlag=TRUE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       rectangle(CStartx,CStarty,CEndx,CEndy);
	       showMouse();
	       MFlag=TRUE;
	       CHFlag=FALSE;
	  }
	break;
	//  ************    Line Command    ***********************//
       case 1:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       CHFlag=TRUE;
	       MFlag=FALSE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       line(CStartx,CStarty,CEndx,CEndy);
	       showMouse();
	       CHFlag=FALSE;
	       MFlag=TRUE;
	  }
       break;
	//  ************     Cursor    ***********************//
       case 2:
	 if(Tog==FALSE) {
	    CHFlag=FALSE;
	    MFlag=TRUE;
	 if(Edit->Copy==TRUE || Edit->Paste==TRUE || Edit->Cut==TRUE) {
	    Free(0);
	    Edit->Copy=FALSE;
	    Edit->Cut=FALSE;
	 }
	   Tog=TRUE;
	 }
       break;
	//  *****************   Ellipse    ***********************//
       case 3:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       CHFlag=TRUE;
	       MFlag=FALSE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       CHFlag=FALSE;
	       MFlag=TRUE;
	       if(CEndx > CStartx || CEndy > CStarty){
		  CRadiusx=(CEndx-CStartx);
		  CRadiusy=(CEndy-CStarty);
		  ellipse(CEndx-CRadiusx,CEndy-CRadiusy,0,360,abs(CRadiusx),abs(CRadiusy));
	       }else
	       if(CEndx < CStartx && CEndy < CStarty)
	       {
		  CRadiusx=(CStartx-CEndx);
		  CRadiusy=(CStarty-CEndy);
		  ellipse(CStartx,CStarty,0,360,abs(CRadiusx),abs(CRadiusy));
	       }
		  showMouse();
	  }
       break;
	//  ************    Filled Rect    ***********************//
       case 4:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       CHFlag=TRUE;
	       MFlag=FALSE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       bar(CStartx,CStarty,CEndx,CEndy);
	       showMouse();
	       CHFlag=FALSE;
	       MFlag=TRUE;
	  }
	break;
	//  ************    Eraser    ***********************//
       case 5:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	     hideMouse();
	     MFlag=FALSE;
	     CVisible=FALSE;
	   }
	   if(getMBPressStatus()==1) {
	     PollMouseStatus(&Cx,&Cy);
	     CEndx = Cx-f1->fx;
	     CEndy = Cy-f1->fy;
	     XOR_draw(CEndx,CEndy,CEndx,CEndy,But_Index);
	     delay(20);
	     setfillstyle(SOLID_FILL,BKCOLOR);
	     bar(CEndx,CEndy,CEndx+10,CEndy+10);
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       showMouse();
	       MFlag=TRUE;
	  }
	break;
	//  ************   Drawing Pencil  ***********************//
       case 6:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	     hideMouse();
	     MFlag=FALSE;
	     CVisible=FALSE;
	   }
	   if(getMBPressStatus()==1) {
	     PollMouseStatus(&Cx,&Cy);
	     CEndx = Cx-f1->fx;
	     CEndy = Cy-f1->fy;
	     XOR_draw(CEndx,CEndy,CEndx,CEndy,But_Index);
	     delay(10);
	     XOR_draw(CEndx,CEndy,CEndx,CEndy,But_Index);
	     PollMouseStatus(&Ex,&Ey);
	     CStartx = Ex-f1->fx;
	     CStarty = Ey-f1->fy;
	     line(CStartx,CStarty,CEndx,CEndy);
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       showMouse();
	       MFlag=TRUE;
	  }
       break;
	//  ************   Flood Fill     ***********************//
      case 7:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	       MFlag=FALSE;
	   else
	   if(getMBPressStatus()==2 && MFlag==TRUE)
	       MFlag=FALSE;
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       hideMouse();
	       if(getpixel(CEndx,CEndy)!=BLACK) {
		 setfillstyle(SOLID_FILL,FCOLOR);
		 floodfill(CEndx,CEndy,BLACK);
		}else {
		  setfillstyle(SOLID_FILL,FCOLOR);
		  floodfill(CEndx,CEndy,WHITE);
		 }

	       showMouse();
	       MFlag=TRUE;
	  }
	  else
	  if(getMBReleaseStatus()==2 && MFlag==FALSE)
	  {
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       hideMouse();
	       if(getpixel(CEndx,CEndy)!=BLACK) {
		  setfillstyle(SOLID_FILL,BKCOLOR);
		  floodfill(CEndx,CEndy,BLACK);
		}else {
		  setfillstyle(SOLID_FILL,BKCOLOR);
		  floodfill(CEndx,CEndy,WHITE);
		 }
	       showMouse();
	       MFlag=TRUE;
	  }
       break;
       case 8:
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       CHFlag=TRUE;
	       MFlag=FALSE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       Px = CStartx;
	       Py = CStarty;
	       Px1 = CEndx;
	       Py1 = CEndy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       if(Edit->Copy==TRUE || Edit->Paste==TRUE || Edit->Cut==TRUE) {
		 Free(0);
		}
	       if(P_Copy(&Copy_Image[0],CStartx,CStarty,CEndx,CEndy)) {
		   showMouse();
		   Edit->Copy=TRUE;
		   EDITFlag= TRUE;
		   EDITCut=TRUE;
		   }
		   else { showMouse();
		   MsgBox("ImageSize is too large",0);}
	       CHFlag=FALSE;
	       MFlag=TRUE;
	  }
	  break;
	// ************  Cut Paste  **************//
	case 20:
	  if(Cx > (f1->fx+10) && Cy > (f1->fy+10) && Cx < (f1->fx+Copy_Image[0].Width+10) && Cy < (f1->fy+Copy_Image[0].Height+10) && getMBPressStatus()==1)
	   if(getMBPressStatus()==1 && Paste==TRUE)
	   {
	     CEndx = Cx-f1->fx;
	     CEndy = Cy-f1->fy;
	     MFlag=FALSE;
	   }
	   if(getMBPressStatus()==1 && Paste==TRUE && MFlag==FALSE) {
	     PollMouseStatus(&Cx,&Cy);
	     CEndx = Cx-f1->fx;
	     CEndy = Cy-f1->fy;
	     XOR_draw(CEndx,CEndy,CEndx+Copy_Image[0].Width,CEndy+Copy_Image[0].Height,But_Index);
	     delay(20);
	     XOR_draw(CEndx,CEndy,CEndx+Copy_Image[0].Width,CEndy+Copy_Image[0].Height,But_Index);
	   }
	   if(getMBReleaseStatus()==0 && MFlag==FALSE)
	   {
	       hideMouse();
	       P_Paste(&Copy_Image[0],10,10);
	       P_Paste(&Copy_Image[1],10,10);
	       Free(1);
	       P_Copy(&Copy_Image[1],CEndx,CEndy,Copy_Image[0].Width+CEndx,Copy_Image[0].Height+CEndy);
	       P_Paste(&Copy_Image[1],CEndx,CEndy);
	       P_Paste(&Copy_Image[0],CEndx,CEndy);
	       showMouse();
	       Paste=FALSE;
	       MFlag=TRUE;
	       But_Index=OldInd;
	   }
       break;
       case 9:    // Text
	   if(getMBPressStatus()==1 && MFlag==TRUE)
	   {
	       hideMouse();
	       CStartx = getMousex()-f1->fx;
	       CStarty = getMousey()-f1->fy;
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CVisible=FALSE;
	       CHFlag=TRUE;
	       MFlag=FALSE;
	   }
	  if(getMBReleaseStatus()==0 && MFlag==FALSE)
	  {
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       showMouse();
	       editPData(f1->fx+CStartx+2,f1->fy+CStarty+2,f1->fx+CEndx-2,f1->fy+CEndy-2);
	       Edit->Text = FALSE;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       But_Index = Old_Index;
	       CHFlag=FALSE;
	       MFlag=TRUE;
	  }
	break;
      }
     MSFlag=FALSE;
     if(MFlag==FALSE && CHFlag==TRUE)
      {
	    if(But_Index!=5){
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       CEndx = getMousex()-f1->fx;
	       CEndy = getMousey()-f1->fy;
	       XOR_draw(CStartx,CStarty,CEndx,CEndy,But_Index);
	       delay(30);
	   }
      }
    }
   if(MouseOn1((f1->x1+22)-20,(f1->y-22)+4,(f1->x1+22)-6,(f1->y-22)+17) && objectAction_Click()) {
     ret = TRUE;
     setviewport(f1->x,f1->y,f1->x1,f1->y1,CLIP_OFF);
     setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
    return ret;
   }
 }
   setviewport(f1->x,f1->y,f1->x1,f1->y1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  return ret;
}

//  ***************************************************************//

void XOR_draw(int x,int y,int x1,int y1,int Attrib)
{
  hideMouse();
  setwritemode(XOR_PUT);
  setfillstyle(SOLID_FILL,FCOLOR);
  setcolor(MAXCOLOR-FCOLOR);
  switch(Attrib)
  {
     case 0:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      rectangle(x,y,x1,y1);
     break;
     case 1:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      line(x,y,x1,y1);
     break;
     case 3:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      setlinestyle(DOTTED_LINE,1, 1);
      setcolor(YELLOW);
      line(x,y,x1,y1);
     break;
     case 4:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      setlinestyle(DOTTED_LINE,1, 1);
      setcolor(YELLOW);
      rectangle(x,y,x1,y1);
     break;
     case 5:
      setfillstyle(SOLID_FILL,BKCOLOR);
      bar(x,y,x+10,y+10);
      setcolor(WHITE);
      rectangle(x,y,x+10,y+10);
     break;
     case 6:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line(x+8,y-8,x,y);
      line(x+4,y-11,x,y);
      line(x+6,y-10,x+3,y-5);
      setcolor(MAXCOLOR-FCOLOR);
     break;
     case 8:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      setlinestyle(DOTTED_LINE,1, 1);
      setcolor(YELLOW);
      rectangle(x,y,x1,y1);
     break;
     case 9:
     if(FCOLOR==YELLOW)
	setcolor(BLUE);
      else setcolor(YELLOW);
      line((x1)-8,y1,x1+8,y1);
      line(x1,(y1)-8,x1,y1+8);
      setcolor(MAXCOLOR-FCOLOR);
      setlinestyle(DOTTED_LINE,1, 1);
      setcolor(YELLOW);
      rectangle(x,y,x1,y1);
     break;
     case 20:
      setcolor(MAXCOLOR-FCOLOR);
      setlinestyle(DOTTED_LINE,1, 1);
      setcolor(YELLOW);
      rectangle(x,y,x1,y1);
     break;
  }
  setwritemode(COPY_PUT);
  showMouse();
  setfillstyle(SOLID_FILL,FCOLOR);
  setlinestyle(SOLID_LINE,1, 1);
  setcolor(FCOLOR);
}

BOOL P_Copy(COPY_PASTE *Copy,int x,int y,int x1,int y1)
{
  BOOL ret=TRUE;
  Buff_Size = imagesize(x,y,x1,y1);
  Copy->P_Buffer=(char far*) farcalloc(Buff_Size,sizeof(UCHAR));
  if(Copy->P_Buffer==NULL){
   MsgBox("Memory Full Cannot Copy",0);ret=FALSE;
  }else{
    getimage(x,y,x1,y1,Copy->P_Buffer);
    putimage(x,y,Copy->P_Buffer,COPY_PUT);
    Copy->x=x;
    Copy->y=y;
    Copy->Width  = abs(x1-x);
    Copy->Height = abs(y1-y);
  }
  if(Copy->Width>200 && Copy->Height>200)
   return FALSE;
 return ret;
}

void P_Paste(COPY_PASTE *Paste,int x,int y){
  putimage(x,y,Paste->P_Buffer,XOR_PUT);
}

void freeMem(){
  farfree(Copy_Image[0].P_Buffer);
  farfree(Copy_Image[1].P_Buffer);
}

void Free(int i){
  farfree(Copy_Image[i].P_Buffer);
}

BOOL Button_Click(PBUTTON *B1)
{
  BOOL Flag=FALSE;
  int i;
  Mouse = mouseStatus();
  if(Mouse.x>=B1->fx+B1->x && Mouse.x<=B1->fx+B1->x1 && Mouse.y>=B1->fy+B1->y && Mouse.y<=B1->fy+B1->y1) {
   Flag = TRUE;
  }
  return Flag;
}

BOOL CheckToolBar(TR_PAINT t1)
{
  BOOL Flag=FALSE;
  if(Mouse.x>=t1.x && Mouse.x<=t1.x+80 && Mouse.y>=t1.y && Mouse.y<=t1.y1) {
     Flag = TRUE;
  }
  return Flag;
}

BOOL pButtonAction(PBUTTON But1)
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
      PollMouseStatus(&Cx,&Cy);
       if(Cx < Mouse.x || Cx > Mouse.x || Cy < Mouse.y || Cy > Mouse.y || Mouse.Button==1)
	{But1.Bool=TRUE;  break;}
      if(kbhit())
      {
	 ch=getch();
	 if(ch==ENTER_KEY)
	  { if(But1.Bool==TRUE)
	      {
		PButton_Push(But1);
		 delay(10);
		PButton_Release(But1);
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
  }
 setviewport(But1.x,But1.y,But1.x1,But1.y1,CLIP_OFF);
 setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
 return bool;
}

FRAME Paint_Editor(char *filename)
{
   FRAME Edit;
   IN_FRAME In_Frame;
   In_Frame=getIN();
   Edit=Frame_EDIT_Window(In_Frame.x,In_Frame.y,In_Frame.x1,In_Frame.y1,filename);
  return Edit;
}

TR_PAINT draw_Editor(FRAME *f1)
{
   TR_PAINT E1;
   int i,j,ind=0;
   struct viewporttype viewinfo;
   int x,y,x1,y1;
   hideMouse();
   getviewsettings(&viewinfo);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   x=80;y=0;
   x1=f1->x1-(f1->x+2)-17;
   y1=f1->y1-(f1->y+23)-17;
   setviewport(f1->x+2,f1->y+23,f1->x1-2,f1->y1-2,CLIP_ON);
   setfillstyle(SOLID_FILL, BLUE);
   bar(f1->x,f1->y-40,f1->x+70,f1->y-23);
   setcolor(WHITE);
   rectangle(f1->x,f1->y-40,f1->x+70,f1->y-23);
   settextstyle(TITLE_FONT,HORIZ_DIR,TITLE_FONT_SIZE);
   setusercharsize(7,13, 2, 5);
   outtextxy(10,(textheight("T")/4),"Tool Bar");
   CrossLine(2,23,75);
   But[0] = PButton(f1,10,30,30,50,0,0);
   But[1] = PButton(f1,31,30,50,50,0,0);
   But[2] = PButton(f1,51,30,70,50,0,0);
   But[3] = PButton(f1,10,55,30,75,0,0);
   But[4] = PButton(f1,31,55,50,75,0,0);
   But[5] = PButton(f1,51,55,70,75,0,0);
   But[6] = PButton(f1,10,80,30,100,0,0);
   But[7] = PButton(f1,31,80,50,100,0,0);
   But[8] = PButton(f1,51,80,70,100,0,0);
   CrossLine(2,105,75);
   for(j=115;j<170;j=j+15)
     for(i=10;i<63;i=i+15) {
	CBut[ind] = PButton(f1,i,j,i+13,j+13,COLOR_BUT,ind);
	ind++;
       }
   CBBut = PButton(f1,30,190,60,210,2,15);
   CFBut = PButton(f1,10,180,40,200,2,0);
   CrossLine(2,220,75);

   setcolor(BLACK);
   rectangle(15,35,25,45);
   line(37,35,45,45);
   //   Cursor
   Draw_Mouse_Cur();
   ellipse(20,65,10,0,7,4);
   setfillstyle(SOLID_FILL,RED);
   bar(35,60,46,70);
   setfillstyle(SOLID_FILL,YELLOW);
   bar3d(57,61,63,71,2,5);
   //   Pen
   line(16,84,25,95);
   line(16,85,25,95);
   line(15,86,25,95);
   line(15,87,25,95);
   line(15,88,25,95);
   //  Flood Fill
   setfillstyle(SOLID_FILL,LIGHTGREEN);
   bar(35,87,45,95);
   ellipse(40,87,10,0,5,3);
   //  Select the Picture for CUT PASTE
   setlinestyle(DOTTED_LINE,1, 1);
   rectangle(54,84,66,96);
   setlinestyle(SOLID_LINE,1, 1);

   setcolor(12);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   bar(x,y,x1,y1);
   setfillstyle(SOLID_FILL,WHITE);
   bar(x,y,x1,y1);
   setcolor(DARKGRAY);
   rectangle(x,y,x1,y1);
   rectangle(x+1,y+1,x1-1,y1-1);
   setcolor(WHITE);
   line(x1-1,y+1,x1-1,y1-1);
   line(x+1,y1-1,x1-1,y1-1);
   line(x1,y,x1,y1);
   line(x,y1,x1,y1);
   Scroll(x1,y,x1+20,y1,1);
   Scroll(x,y1,x1+20,y1+20,0);

   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   E1.fx=f1->x+x+4;
   E1.fy=f1->y+25;
   E1.x=f1->x+2;
   E1.y=f1->y+23;
   E1.x1=f1->x1-20;
   E1.y1=f1->y1-20;
   showMouse();
 return E1;
}

PBUTTON PButton(FRAME *f1,int x,int y,int x1,int y1,int Attrib,int Color)
{
  PBUTTON B1;
   hideMouse();
    B1.fx=f1->x+2;
    B1.fy=f1->y+23;
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

void Draw_Mouse_Cur(void)
{
    line(55,35,57,46);
    line(55,35,66,38);

    line(57,46,58,40);
    line(58,40,62,46);

    line(66,38,60,39);
    line(60,39,64,44);
}

void PButton_Push(PBUTTON B1){
  struct viewporttype viewinfo;
  hideMouse();
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_ON);
  Internal_Menu_Frame(B1.x,B1.y,B1.x1,B1.y1);
  setcolor(BLACK);
  if(B1.tabIndex==0)
      rectangle(16,36,26,46);
   else
  if(B1.tabIndex==1)
   line(37,35,46,46);
   else
  if(B1.tabIndex==2)
   Draw_Mouse_Cur();
   else
  if(B1.tabIndex==3)
   ellipse(21,66,10,0,7,4);
   else
  if(B1.tabIndex==4)
   {setfillstyle(SOLID_FILL,RED);
    bar(36,61,47,71);}
  else
  if(B1.tabIndex==5)
  { setfillstyle(SOLID_FILL,YELLOW);
    bar3d(58,62,64,72,2,5);}
  else
  if(B1.tabIndex==6)
  { line(17,85,26,96);
    line(17,86,26,96);
    line(16,87,26,96);
    line(16,88,26,96);
    line(16,89,26,96);}
  else
  if(B1.tabIndex==7)
   {setfillstyle(SOLID_FILL,LIGHTGREEN);
   bar(36,88,46,96);
   ellipse(41,88,10,0,5,3);}
  else
  if(B1.tabIndex==8)
   {setlinestyle(DOTTED_LINE,1, 1);
    rectangle(55,85,67,97);
    setlinestyle(SOLID_LINE,1, 1);}
   setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   showMouse();
}
void PButton_Release(PBUTTON B1){
  struct viewporttype viewinfo;
  hideMouse();
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_ON);
  Hlight_Frame(B1.x,B1.y,B1.x1,B1.y1);
  setcolor(BLACK);
  if(B1.tabIndex==0)
      rectangle(15,35,25,45);
   else
  if(B1.tabIndex==1)
   line(37,35,45,45);
   else
  if(B1.tabIndex==2)
   Draw_Mouse_Cur();
   else
  if(B1.tabIndex==3)
   ellipse(20,65,10,0,7,4);
   else
  if(B1.tabIndex==4)
   {setfillstyle(SOLID_FILL,RED);
    bar(35,60,46,70);}
  else
  if(B1.tabIndex==5)
  { setfillstyle(SOLID_FILL,YELLOW);
    bar3d(57,61,63,71,2,5);}
  else
  if(B1.tabIndex==6)
  { line(16,84,25,95);
    line(16,85,25,95);
    line(15,86,25,95);
    line(15,87,25,95);
    line(15,88,25,95);}
  else
  if(B1.tabIndex==7)
   {setfillstyle(SOLID_FILL,LIGHTGREEN);
   bar(35,87,45,95);
   ellipse(40,87,10,0,5,3);}
  else
  if(B1.tabIndex==8)
   {setlinestyle(DOTTED_LINE,1, 1);
    rectangle(54,84,66,96);
    setlinestyle(SOLID_LINE,1, 1);}
   setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   showMouse();
}

void setButtonColor(PBUTTON B1,COLORS Color)
{
  struct viewporttype viewinfo;
  hideMouse();
  getviewsettings(&viewinfo);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
  setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_ON);
   Hlight_Frame(B1.x,B1.y,B1.x1,B1.y1);
   setfillstyle(SOLID_FILL,Color);
   bar(B1.x+2,B1.y+2,B1.x1-2,B1.y1-2);
  setviewport(B1.fx,B1.fy,B1.fx1,B1.fy1,CLIP_OFF);
  setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
  showMouse();
}
