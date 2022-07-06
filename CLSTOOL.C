  /******************************************************************/
  //		   Dospaint :-         Version 2.0
  //	      Developed By
  //		         Ratheesh.TR
  //			 macratheesh@yahoo.com
  //			 macratheesh@gmail.com
  //	      WebSite:   www.picksourcecode.com
  //	      Mobile No: +91-9894555037
  //*****************************************************************/

#include <graphics.h>
#include "Wiredefs.h"
#include "DgnTool.h"
#include "Mouse.h"

void clearEditor(int x,int y,int x1,int y1)
{
   struct viewporttype viewinfo;
   getviewsettings(&viewinfo);
   hideMouse();
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_OFF);
   setviewport(x,y,x1,y1,CLIP_ON);
   setfillstyle(SOLID_FILL,WHITE);
   setcolor(WHITE);
   bar(0,0,(x1-x),(y1-y));
   setcolor(BLACK);
   setviewport(x,y,x1,y1,CLIP_OFF);
   setviewport(viewinfo.left,viewinfo.top,viewinfo.right,viewinfo.bottom,CLIP_ON);
   showMouse();
}
