#ifndef   _PAINT_H
#include  "Wiredefs.h"
#include  "DgnTool.h"

#define  MAXCOLOR    15

typedef int COLORS;
typedef struct{
     int x;
     int y;
     int x1;
     int y1;
     int Sx;
     int Ex;
     int fx;
     int fy;
     int fx1;
     int fy1;
     UCHAR Edit_Array[40][EDITLEN];
     BOOL Bool;
}TR_PAINT;

FRAME Paint_Editor(char *filename);
TR_PAINT draw_Editor(FRAME *f1);

typedef struct{
     int x;
     int y;
     int x1;
     int y1;
     int fx;
     int fy;
     int fx1;
     int fy1;
     int tabIndex;
     int Color;
     BOOL But_Bool;
     UCHAR getText[30];
     BOOL Bool;
}PBUTTON;

typedef struct{
   BOOL Undo;
   BOOL Redo;
   BOOL Cut;
   BOOL Copy;
   BOOL Paste;
   BOOL Text;
   int TextIndex;
}EDIT;

FRAME Paint_Editor(char *filename);
PBUTTON PButton(FRAME *f1,int x,int y,int x1,int y1,int Attrib,int Color);
BOOL TRPaint_Action(TR_PAINT *f1,EDIT *Edit);
BOOL pButtonAction(PBUTTON b1);
void PButton_Release(PBUTTON B1);
void PButton_Push(PBUTTON B1);
PBUTTON _PButton(FRAME *f1,int x,int y,int x1,int y1,int Attrib,int Color);
void _setButtonColor(PBUTTON B1,COLOR Color);
BOOL CButton_Action(PBUTTON *But1);
int Button_Click(PBUTTON *B1);
void freeMem();

BOOL Save_BMP(TR_PAINT *p1,const char *DFileName);
BOOL Open_BMP(TR_PAINT *p1,const char *SFileName);

#define   _PAINT_H
#endif
