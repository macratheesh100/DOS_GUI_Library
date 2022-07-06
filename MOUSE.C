  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/
  //			 Mouse Program
#include  <bios.h>
#include  <dos.h>
#include  <stdio.h>
#include  <assert.h>

#include  "Wiredefs.h"
#include  "mouse.h"

void showMouse(void)
{
   union REGS i;
   i.x.ax=1;
   int86(MOUSE_INT,&i,&i);
}

BOOL getMouse(void)
{
   BOOL ret;
   union REGS i;
   int86(MOUSE_INT,&i,&i);
   ret=i.x.ax;
  return ret;
}
void hideMouse(void)
{
   union REGS i;
	 i.x.ax=2;
	 int86(MOUSE_INT,&i,&i);
}

BOOL getMBPressStatus(void)
{
   union REGS i,o;
	 i.x.ax=0x0003;
	 int86(MOUSE_INT,&i,&o);
 return  o.x.bx;
}

BOOL getMBReleaseStatus(void)
{
  union REGS regs;
  regs.x.ax=MOUSE_RELEALSE;
  regs.x.bx=3;
  int86(MOUSE_INT,&regs,&regs);
  return regs.x.ax;
}

int  getMousex(void)
{
   union REGS i,o;
	 i.x.ax=3;
	 int86(MOUSE_INT,&i,&o);
  return o.x.cx;
}

int getMousey(void)
{
   union REGS i,o;
	 i.x.ax=3;
	 int86(MOUSE_INT,&i,&o);
 return o.x.dx;
}

MOUSE mouseStatus(void)
{
   MOUSE m1;
   union REGS i,o;
	 i.x.ax=3;
	 int86(MOUSE_INT,&i,&o);
	 m1.Button=o.x.bx;
	 m1.x=o.x.cx;
	 m1.y=o.x.dx;
 return m1;
}

void mousePressStatus(MOUSE *m1)
{
  union REGS i,o;
	 i.x.ax=3;
	 int86(MOUSE_INT,&i,&o);
	 m1->Button=o.x.bx;
	 m1->x=o.x.cx;
	 m1->y=o.x.dx;
}

void  getReleaseStatus(MOUSE *m1)
{
  union REGS regs;
  regs.x.ax=MOUSE_RELEALSE;
  regs.x.bx=m1->Button;
  int86(MOUSE_INT,&regs,&regs);
  m1->Counter=regs.x.bx;
  m1->x1=regs.x.cx;
  m1->y1=regs.x.dx;
  m1->Button_Release = regs.x.ax;
}

int PollMouseStatus(int *x,int *y)
{
 union REGS regs;
 regs.x.ax=FC_Poll;
 int86(MOUSE_INT,&regs,&regs);
 if(x!=NULL)
 {*x=regs.x.cx;}
 if(y!=NULL)
 {*y=regs.x.dx;}
 return regs.x.bx;
}

void setMouseCursorPosition(int x,int y)
{
  union REGS regs;
  regs.x.ax=FC_Set_Mouse_Position;
  regs.x.cx=x;
  regs.x.dx=y;
  int86(MOUSE_INT,&regs,&regs);
}

int getkey(void)
{
 int key, lo, hi;
 key = bioskey(0);
 lo = key & 0X00FF;
 hi = (key & 0XFF00) >> 8;
 return((lo == 0) ? hi + 256 : lo);
}

void setMouseGraphicsCursor(int HotSpotx, int HotSpoty,void far* Bitmapptr)
{
  union REGS regs;
  struct SREGS sregs;
  assert ((-16<=HotSpotx) && (HotSpotx<=16));
  assert((-16<=HotSpoty) && (HotSpoty<=16));

  regs.x.ax = FC_SET_GRAPHICS_CURSOR;
  regs.x.bx = HotSpotx;
  regs.x.cx = HotSpoty;
  regs.x.dx = FP_OFF(Bitmapptr);
  sregs.es  = FP_SEG(Bitmapptr);
  int86x(MOUSE_INT,&regs,&regs,&sregs);
}

UINT16  getMouseButtonRelease(UINT16 Button,UINT16 *Counter,UINT16 *x,UINT16 *y)
{
  union REGS regs;
  regs.x.ax=MOUSE_RELEALSE;
  regs.x.bx=Button;
  int86(MOUSE_INT,&regs,&regs);
  if(Counter!=NULL){
     *Counter=regs.x.bx;
  }
  if(x != NULL) {
     *x=regs.x.cx;
  }
  if(y != NULL){
     *y=regs.x.dx;
  }
  return regs.x.ax;
}

BOOL objectAction_Click(void)
{
  if(getMBPressStatus() == 1)
  {  delay(100);
     if(getMBReleaseStatus() == 0)
      return 1;
  }
return 0;
}
