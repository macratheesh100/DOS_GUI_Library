  /*****************************************************************/
  //		    Steganography :-         Version 2.0
  //	      Developed By
  //			 N.C.C.T
  //			 #109, 2nd Floor
  //			 N.H- ROAD
  //			 CHENNAI - 600034
  //        Programmed By
  //			 T.R.Ratheesh
  //                     tr.ratheesh@gmail.com
  /*****************************************************************/
  //                      Mouse Program File

#include  "Wiredefs.h"
#define   MOUSE_INT                 0x33
#define   FC_Set_Mouse_Position   0x0004
#define   FC_Poll                 0x0003
#define   MOUSE_RELEALSE          0x0006
#define   FC_SET_GRAPHICS_CURSOR  0x0009
typedef struct{
  int x;
  int y;
  int x1;
  int y1;
  int Counter;
  int Button_Release;
  int Button;
}MOUSE;
extern MOUSE Mouse;

int PollMouseStatus(int *x,int *y);
void setMouseCursorPosition(int x,int y);
void showMouse(void);
void hideMouse(void);
MOUSE mouseStatus(void);
UINT16  getMouseButtonRelease(UINT16 Button,UINT16 *Counter,UINT16 *x,UINT16 *y);
void setMouseGraphicsCursor(int HotSpotx, int HotSpoty,void far* Bitmapptr);
void  getReleaseStatus(MOUSE *m1);
void mousePressStatus(MOUSE *m1);

//  Paint Mouse Event
BOOL getMBPressStatus(void);
BOOL getMBReleaseStatus(void);
int  getMousex(void);
int getMousey(void);
BOOL getMouse(void);
BOOL objectAction_Click(void);

void ScrollWindowUp(int x,int y,int x1,int y1,int color);
void ScrollWindowDown(int x,int y,int x1,int y1,int color);
int getkey(void);


